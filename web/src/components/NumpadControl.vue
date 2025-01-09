<script setup lang="ts">
import GamepadButton from "./GamepadButton.vue";

defineEmits<{
  click: [number];
}>();
</script>

<template>
  <div class="space-x-3">
    <template v-for="i in 9">
      <GamepadButton @pointerdown="() => $emit('click', i)">
        {{ i }}
      </GamepadButton>
    </template>
  </div>
</template>
