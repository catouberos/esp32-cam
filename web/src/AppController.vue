<script setup lang="ts">
import { useWebSocket, watchDebounced } from "@vueuse/core";
import { Joystick, JoystickComponent } from "vue-joystick-component";
import { SliderRange, SliderRoot, SliderThumb, SliderTrack } from "reka-ui";
import DpadControl from "./components/DpadControl.vue";
import ButtonControl from "./components/ButtonControl.vue";
import { ref, watch } from "vue";
import { PIDData } from "./type";
import NumpadControl from "./components/NumpadControl.vue";

const x = defineModel("x", { default: 0 });
const y = defineModel("y", { default: 0 });
const omega = defineModel("omega", { default: 0 });
const moveMultiplier = defineModel("moveMultiplier", { default: [20] });
const rotateMultiplier = defineModel("rotateMultiplier", { default: [50] });

const _x = ref(false);
const _y = ref(false);
const _a = ref(false);
const _b = ref(false);

const _left = ref(false);
const _right = ref(false);

const counter = ref(0);
const motor = defineModel<{
  topLeft: PIDData[];
  topRight: PIDData[];
  bottomLeft: PIDData[];
  bottomRight: PIDData[];
}>("motor", {
  default: {
    topLeft: [],
    topRight: [],
    bottomLeft: [],
    bottomRight: [],
  },
});

const { send, data } = useWebSocket<string>(`ws://192.168.4.250/websocket`, {
  autoReconnect: true,
  autoClose: false,
});

function rotateReset() {
  omega.value = 0;
}

function moveReset() {
  x.value = 0;
  y.value = 0;
}

function rotate(event: JoystickComponent.UpdateEvent) {
  omega.value = event.x ?? 0;
}

function move(event: JoystickComponent.UpdateEvent) {
  x.value = event.x ?? 0;
  y.value = event.y ?? 0;
}

function preset(i: number) {
  const command = (i + 9).toString(36);
  console.info("preset", command);
  send(command);
}

watch([_x, _y, _a, _b, _left, _right], () => {
  x.value = (_b.value ? 1 : 0) - (_x.value ? 1 : 0);
  y.value = (_y.value ? 1 : 0) - (_a.value ? 1 : 0);
  omega.value = (_right.value ? 1 : 0) - (_left.value ? 1 : 0);
});

watchDebounced(
  [data],
  () => {
    const values = data.value
      ?.replace("\n", "")
      .split(",")
      .map((v) => parseInt(v));

    if (values) {
      motor.value.topLeft.push({
        x: counter.value,
        kp: values[0],
        ki: values[1],
        kd: values[2],
      });
      motor.value.topRight.push({
        x: counter.value,
        kp: values[3],
        ki: values[4],
        kd: values[5],
      });
      motor.value.bottomLeft.push({
        x: counter.value,
        kp: values[6],
        ki: values[7],
        kd: values[8],
      });
      motor.value.bottomRight.push({
        x: counter.value,
        kp: values[9],
        ki: values[10],
        kd: values[11],
      });

      if (motor.value.topLeft.length > 300) {
        motor.value.topLeft.shift();
      }

      if (motor.value.topRight.length > 300) {
        motor.value.topRight.shift();
      }

      if (motor.value.bottomLeft.length > 300) {
        motor.value.bottomLeft.shift();
      }

      if (motor.value.bottomRight.length > 300) {
        motor.value.bottomRight.shift();
      }
    }

    counter.value++;
  },
  { debounce: 100, maxWait: 100 },
);

watchDebounced(
  [x, y, omega, moveMultiplier, rotateMultiplier],
  () => {
    console.info("send", {
      x: x.value,
      y: y.value,
      omega: omega.value,
      moveMultiplier: moveMultiplier.value,
      rotateMultiplier: rotateMultiplier.value,
    });
    send(
      `${x.value},${y.value},${omega.value},${moveMultiplier.value},${rotateMultiplier.value}`,
    );
  },
  { debounce: 50, maxWait: 50 },
);
</script>

<template>
  <div
    class="flex items-center justify-center flex-col gap-6 sm:order-first z-10 p-6 basis-[50%] sm:basis-auto"
  >
    <DpadControl v-model:left="_left" v-model:right="_right" />

    <Joystick
      :size="100"
      base-color="#6ee7b7"
      stick-color="#0f766e"
      :throttle="100"
      @start="rotateReset"
      @stop="rotateReset"
      @move="rotate"
    />

    <SliderRoot
      v-model="rotateMultiplier"
      class="relative flex items-center select-none touch-none w-full h-5"
      :max="200"
      :step="10"
    >
      <SliderTrack class="bg-neutral-500/30 relative grow rounded-full h-2">
        <SliderRange class="absolute bg-emerald-400 rounded-full h-full" />
      </SliderTrack>
      <SliderThumb
        class="block w-6 h-6 bg-white rounded-full hover:bg-neutral-50 shadow-sm focus:outline-none focus:shadow-[0_0_0_2px] focus:shadow-emerald-400"
        aria-label="Rotate multiplier"
      />
    </SliderRoot>
  </div>

  <div
    class="flex items-center justify-center flex-col gap-6 sm:order-3 z-10 p-6 basis-[50%] sm:basis-auto"
  >
    <ButtonControl
      v-model:x="_x"
      v-model:y="_y"
      v-model:a="_a"
      v-model:b="_b"
    />

    <Joystick
      :size="100"
      base-color="#7dd3fc"
      stick-color="#0369a1"
      :throttle="100"
      @start="moveReset"
      @stop="moveReset"
      @move="move"
    />

    <SliderRoot
      v-model="moveMultiplier"
      class="relative flex items-center select-none touch-none w-full h-5"
      :max="250"
      :step="10"
    >
      <SliderTrack class="bg-neutral-500/30 relative grow rounded-full h-2">
        <SliderRange class="absolute bg-sky-400 rounded-full h-full" />
      </SliderTrack>
      <SliderThumb
        class="block w-6 h-6 bg-white rounded-full hover:bg-neutral-50 shadow-sm focus:outline-none focus:shadow-[0_0_0_2px] focus:shadow-sky-400"
        aria-label="Speed multiplier"
      />
    </SliderRoot>
  </div>

  <div class="order-last basis-full items-center text-center space-y-3">
    <h4 class="font-bold text-lg">Presets</h4>
    <NumpadControl @click="preset" />
  </div>
</template>
