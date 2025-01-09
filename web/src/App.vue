<script setup lang="ts">
import { computed, ref } from "vue";
import AppCamera from "./AppCamera.vue";
import AppController from "./AppController.vue";
import {
  mapGamepadToXbox360Controller,
  useGamepad,
  watchDebounced,
} from "@vueuse/core";
import GamepadBadge from "./components/GamepadBadge.vue";
import AppChart from "./AppChart.vue";
import { PIDData } from "./type";
import { VisBulletLegend } from "@unovis/vue";

const x = ref(0);
const y = ref(0);
const omega = ref(0);
const flash = ref(false);
const moveMultiplier = ref([20]);
const rotateMultiplier = ref([50]);

const { isActive, isSupported, gamepads } = useGamepad();
const gamepad = computed(() =>
  gamepads.value.find((g) => g.mapping === "standard"),
);
const controller = gamepad ? mapGamepadToXbox360Controller(gamepad) : undefined;

const motor = ref<{
  topLeft: PIDData[];
  topRight: PIDData[];
  bottomLeft: PIDData[];
  bottomRight: PIDData[];
}>({
  topLeft: [],
  topRight: [],
  bottomLeft: [],
  bottomRight: [],
});

watchDebounced(
  [controller],
  () => {
    if (controller?.value) {
      // map stick to x/y/omega value
      x.value = controller.value.stick.right.horizontal;
      y.value = -1 * controller.value.stick.right.vertical;
      omega.value = controller.value.stick.left.horizontal;

      // map bumper to movement multiplier
      if (controller.value.bumper.left.pressed && moveMultiplier.value[0] > 0) {
        moveMultiplier.value[0] -= 10;
      }
      if (
        controller.value.bumper.right.pressed &&
        moveMultiplier.value[0] < 100
      ) {
        moveMultiplier.value[0] += 10;
      }

      // map dpad up down to increate rotate multiplier
      if (controller.value.dpad.down.pressed && rotateMultiplier.value[0] > 0) {
        rotateMultiplier.value[0] -= 10;
      }
      if (controller.value.dpad.up.pressed && rotateMultiplier.value[0] < 200) {
        rotateMultiplier.value[0] += 10;
      }

      // map button to x/y/omega value
      if (
        controller.value.buttons.x.pressed ||
        controller.value.buttons.b.pressed
      )
        x.value =
          controller.value.buttons.b.value - controller.value.buttons.x.value;
      if (
        controller.value.buttons.a.pressed ||
        controller.value.buttons.y.pressed
      )
        y.value =
          controller.value.buttons.y.value - controller.value.buttons.a.value;

      if (
        controller.value.dpad.right.pressed ||
        controller.value.dpad.left.pressed
      )
        omega.value =
          controller.value.dpad.right.value - controller.value.dpad.left.value;

      // map start button to flash
      if (controller.value.start.pressed) {
        flash.value = !flash.value;
      }
    }
  },
  { debounce: 50, maxWait: 50 },
);

const items = [
  { name: "Input", color: "red" },
  { name: "Output", color: "green" },
  { name: "Reference", color: "blue" },
];
</script>

<template>
  <main class="mx-auto p-3 space-y-6">
    <div class="flex flex-wrap justify-between min-h-screen items-center">
      <AppCamera v-model:flash="flash" />
      <AppController
        v-model:x="x"
        v-model:y="y"
        v-model:omega="omega"
        v-model:move-multiplier="moveMultiplier"
        v-model:rotate-multiplier="rotateMultiplier"
        v-model:motor="motor"
      />

      <GamepadBadge
        v-if="isSupported"
        :enabled="isActive"
        class="fixed z-10 bottom-6 right-6"
      />
    </div>

    <div class="grid grid-cols-1 lg:grid-cols-2 gap-6 p-6">
      <div class="space-y-3">
        <h4 class="text-center">Top Left Motor</h4>
        <AppChart :data="motor.topLeft" />
      </div>
      <div class="space-y-3">
        <h4 class="text-center">Top Right Motor</h4>
        <AppChart :data="motor.topRight" />
      </div>
      <div class="space-y-3">
        <h4 class="text-center">Bottom Left Motor</h4>
        <AppChart :data="motor.bottomLeft" />
      </div>
      <div class="space-y-3">
        <h4 class="text-center">Bottom Right Motor</h4>
        <AppChart :data="motor.bottomRight" />
      </div>
      <VisBulletLegend :items />
    </div>
  </main>
</template>
