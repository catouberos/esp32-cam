<script setup lang="ts">
import GamepadButton from "./GamepadButton.vue";

const a = defineModel("a", { default: false });
const b = defineModel("b", { default: false });
const x = defineModel("x", { default: false });
const y = defineModel("y", { default: false });
</script>

<template>
  <div class="flex items-center flex-wrap justify-center">
    <div class="text-center basis-full">
      <GamepadButton
        class="text-yellow-600 dark:text-yellow-400"
        @pointerdown="() => (y = true)"
        @pointerup="() => (y = false)"
      >
        Y
      </GamepadButton>
    </div>

    <div class="basis-full flex">
      <div class="text-center flex-1">
        <GamepadButton
          class="text-blue-600 dark:text-blue-400"
          @pointerdown="() => (x = true)"
          @pointerup="() => (x = false)"
        >
          X
        </GamepadButton>
      </div>
      <div class="text-center flex-1">
        <GamepadButton
          class="text-red-600 dark:text-red-400"
          @pointerdown="() => (b = true)"
          @pointerup="() => (b = false)"
        >
          B
        </GamepadButton>
      </div>
    </div>

    <div class="text-center basis-full">
      <GamepadButton
        class="text-green-600 dark:text-green-400"
        @pointerdown="() => (a = true)"
        @pointerup="() => (a = false)"
      >
        A
      </GamepadButton>
    </div>
  </div>
</template>
