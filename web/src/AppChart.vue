<script setup lang="ts">
import { VisXYContainer, VisLine, VisAxis } from "@unovis/vue";
import { PIDData } from "./type";

defineProps<{ data: PIDData[] }>();
const x = (d: PIDData) => d.x;
const y = [(d: PIDData) => d.kp, (d: PIDData) => d.ki, (d: PIDData) => d.kd];

const color = (_: PIDData, i: number) => ["red", "green", "blue"][i];
</script>

<template>
  <VisXYContainer :data>
    <VisLine :x :y :color :duration="0" />
    <VisAxis type="x" />
    <VisAxis type="y" />
  </VisXYContainer>
</template>
