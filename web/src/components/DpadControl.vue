<script setup lang="ts">
import GamepadButton from "./GamepadButton.vue";

const up = defineModel("up", { default: false });
const down = defineModel("down", { default: false });
const left = defineModel("left", { default: false });
const right = defineModel("right", { default: false });
</script>

<template>
  <div class="flex items-center flex-wrap justify-center">
    <div class="text-center basis-full">
      <GamepadButton
        @pointerdown="() => (up = true)"
        @pointerup="() => (up = false)"
      >
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width="16"
          height="16"
          fill="currentColor"
          class="bi bi-chevron-up"
          viewBox="0 0 16 16"
        >
          <path
            fill-rule="evenodd"
            d="M7.646 4.646a.5.5 0 0 1 .708 0l6 6a.5.5 0 0 1-.708.708L8 5.707l-5.646 5.647a.5.5 0 0 1-.708-.708z"
          />
        </svg>
      </GamepadButton>
    </div>

    <div class="basis-full flex">
      <div class="text-center flex-1">
        <GamepadButton
          @pointerdown="() => (left = true)"
          @pointerup="() => (left = false)"
        >
          <svg
            xmlns="http://www.w3.org/2000/svg"
            width="16"
            height="16"
            fill="currentColor"
            class="bi bi-chevron-left"
            viewBox="0 0 16 16"
          >
            <path
              fill-rule="evenodd"
              d="M11.354 1.646a.5.5 0 0 1 0 .708L5.707 8l5.647 5.646a.5.5 0 0 1-.708.708l-6-6a.5.5 0 0 1 0-.708l6-6a.5.5 0 0 1 .708 0"
            />
          </svg>
        </GamepadButton>
      </div>
      <div class="text-center flex-1">
        <GamepadButton
          @pointerdown="() => (right = true)"
          @pointerup="() => (right = false)"
        >
          <svg
            xmlns="http://www.w3.org/2000/svg"
            width="16"
            height="16"
            fill="currentColor"
            class="bi bi-chevron-right"
            viewBox="0 0 16 16"
          >
            <path
              fill-rule="evenodd"
              d="M4.646 1.646a.5.5 0 0 1 .708 0l6 6a.5.5 0 0 1 0 .708l-6 6a.5.5 0 0 1-.708-.708L10.293 8 4.646 2.354a.5.5 0 0 1 0-.708"
            />
          </svg>
        </GamepadButton>
      </div>
    </div>

    <div class="text-center basis-full">
      <GamepadButton
        @pointerdown="() => (down = true)"
        @pointerup="() => (down = false)"
      >
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width="16"
          height="16"
          fill="currentColor"
          class="bi bi-chevron-down"
          viewBox="0 0 16 16"
        >
          <path
            fill-rule="evenodd"
            d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708"
          />
        </svg>
      </GamepadButton>
    </div>
  </div>
</template>
