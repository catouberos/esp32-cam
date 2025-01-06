<script setup lang="ts">
import { useWebSocket, watchDebounced } from "@vueuse/core";
import StatusBadge from "./components/StatusBadge.vue";
import { Joystick, JoystickComponent } from "vue-joystick-component";

const x = defineModel("x", { default: 0 });
const y = defineModel("y", { default: 0 });
const omega = defineModel("omega", { default: 0 });

const { status, send } = useWebSocket(`ws://192.168.4.250/websocket`, {
  autoReconnect: true,
  autoClose: false,
});

function reset() {
  x.value = 0;
  y.value = 0;
  omega.value = 0;
  send(`0,0,0`);
}

function rotate(event: JoystickComponent.UpdateEvent) {
  console.info("rotate", event);
  omega.value = event.x ?? 0;
}

function move(event: JoystickComponent.UpdateEvent) {
  console.info("move", event);
  x.value = event.x ?? 0;
  y.value = event.y ?? 0;
}

watchDebounced(
  [x, y, omega],
  () => {
    console.info("send", { x: x.value, y: y.value, omega: omega.value });
    send(`${x.value},${y.value},${omega.value}`);
  },
  { debounce: 100, maxWait: 100 },
);
</script>

<template>
  <div
    class="flex items-center justify-center flex-col gap-6 sm:order-first z-10 p-6"
  >
    <Joystick
      :size="100"
      base-color="#6ee7b7"
      stick-color="#0f766e"
      :throttle="100"
      @start="reset"
      @stop="reset"
      @move="rotate"
    />
  </div>

  <div
    class="flex items-center justify-center flex-col gap-6 order-last z-10 p-6"
  >
    <Joystick
      :size="100"
      base-color="#7dd3fc"
      stick-color="#0369a1"
      :throttle="100"
      @start="reset"
      @stop="reset"
      @move="move"
    />

    <StatusBadge :status />
  </div>
</template>
