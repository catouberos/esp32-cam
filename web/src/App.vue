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

const x = ref(0);
const y = ref(0);
const omega = ref(0);
const flash = ref(false);

const { isActive, isSupported, gamepads } = useGamepad();
const gamepad = computed(() =>
  gamepads.value.find((g) => g.mapping === "standard"),
);
const controller = gamepad ? mapGamepadToXbox360Controller(gamepad) : undefined;

watchDebounced(
  [controller],
  () => {
    if (controller?.value) {
      x.value = controller.value.stick.right.horizontal;
      y.value = controller.value.stick.right.vertical;
      omega.value = controller.value.stick.left.horizontal;
      if (controller.value.buttons.a.pressed) {
        flash.value = !flash.value;
      }
    }
  },
  { debounce: 100, maxWait: 100 },
);
</script>

<template>
  <main class="container mx-auto px-6 py-3">
    <div class="flex flex-wrap justify-between">
      <AppCamera v-model:flash="flash" />
      <AppController v-model:x="x" v-model:y="y" v-model:omega="omega" />
    </div>

    <div class="flex items-center justify-center mt-6">
      <GamepadBadge v-if="isSupported" :enabled="isActive" class="mx-auto" />
    </div>
  </main>
</template>
