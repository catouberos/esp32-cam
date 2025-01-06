<script setup lang="ts">
import { useWebSocket } from "@vueuse/core";
import CameraScreen from "./components/CameraScreen.vue";
import { ref, watch } from "vue";
import StatusBadge from "./components/StatusBadge.vue";
import FlashlightToggle from "./components/FlashlightToggle.vue";

const url = ref(`ws://${window.location.hostname}/websocket`);
const flash = defineModel("flash", { default: false });

const { open, status, data, send } = useWebSocket<Blob>(url, {
  autoReconnect: true,
  autoClose: false,
});

watch([flash], () => {
  send("f");
});
</script>

<template>
  <div class="relative sm:flex-1 grow shrink-0 basis-full">
    <StatusBadge :status class="absolute right-0 top-0 m-3" />
    <FlashlightToggle v-model="flash" class="absolute left-0 bottom-0 m-3" />
    <CameraScreen
      v-if="status == 'OPEN' && data"
      class="w-full h-auto aspect-[4/3] rounded"
      :data
    />
    <div
      v-else
      class="w-full h-auto aspect-[4/3] bg-neutral-500 dark:bg-neutral-400 rounded"
    >
      <input class="w-full" v-model="url" />
      <button @click="open">Open</button>
    </div>
  </div>
</template>
