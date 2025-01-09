<script setup lang="ts">
import { ref } from "vue";
import GamepadButton from "./GamepadButton.vue";

const selected = ref(10);

defineEmits<{
  click: [number];
}>();
</script>

<template>
  <div class="space-x-3">
    <template v-for="i in 9">
      <GamepadButton
        :class="{ 'font-bold': selected === i }"
        @pointerdown="
          () => {
            selected = i;
            $emit('click', i);
          }
        "
      >
        {{ i }}
      </GamepadButton>
    </template>
    <GamepadButton
      :class="{ 'font-bold': selected === 10 }"
      @pointerdown="
        () => {
          selected = 10;
          $emit('click', 10);
        }
      "
    >
      M
    </GamepadButton>
  </div>
</template>
