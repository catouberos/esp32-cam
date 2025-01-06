<script setup lang="tsx">
import { defineModel } from "vue";

const enabled = defineModel<boolean>({ required: true });
</script>

<template>
  <button
    class="inline-flex items-center font-medium rounded-md text-xs px-2 py-1 gap-1"
    :class="{
      'bg-neutral-50 text-neutral-700': enabled,
      'bg-neutral-700 text-neutral-50': !enabled,
    }"
    @click="
      () => {
        enabled = !enabled;
      }
    "
  >
    <svg
      v-if="enabled"
      xmlns="http://www.w3.org/2000/svg"
      width="16"
      height="16"
      fill="currentColor"
      class="bi bi-lightbulb-fill"
      viewBox="0 0 16 16"
    >
      <path
        d="M2 6a6 6 0 1 1 10.174 4.31c-.203.196-.359.4-.453.619l-.762 1.769A.5.5 0 0 1 10.5 13h-5a.5.5 0 0 1-.46-.302l-.761-1.77a2 2 0 0 0-.453-.618A5.98 5.98 0 0 1 2 6m3 8.5a.5.5 0 0 1 .5-.5h5a.5.5 0 0 1 0 1l-.224.447a1 1 0 0 1-.894.553H6.618a1 1 0 0 1-.894-.553L5.5 15a.5.5 0 0 1-.5-.5"
      />
    </svg>
    <svg
      v-else
      xmlns="http://www.w3.org/2000/svg"
      width="16"
      height="16"
      fill="currentColor"
      class="bi bi-lightbulb"
      viewBox="0 0 16 16"
    >
      <path
        d="M2 6a6 6 0 1 1 10.174 4.31c-.203.196-.359.4-.453.619l-.762 1.769A.5.5 0 0 1 10.5 13a.5.5 0 0 1 0 1 .5.5 0 0 1 0 1l-.224.447a1 1 0 0 1-.894.553H6.618a1 1 0 0 1-.894-.553L5.5 15a.5.5 0 0 1 0-1 .5.5 0 0 1 0-1 .5.5 0 0 1-.46-.302l-.761-1.77a2 2 0 0 0-.453-.618A5.98 5.98 0 0 1 2 6m6-5a5 5 0 0 0-3.479 8.592c.263.254.514.564.676.941L5.83 12h4.342l.632-1.467c.162-.377.413-.687.676-.941A5 5 0 0 0 8 1"
      />
    </svg>
    <span>Flashlight</span>
    <strong v-if="enabled">ON</strong>
  </button>
</template>
