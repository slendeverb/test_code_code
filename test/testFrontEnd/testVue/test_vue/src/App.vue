<template>
    <div class="app">
        <h1>诗歌: </h1>
        <p> 相见时难别亦难,东风无力百花残</p>
        <Person v-if="isShow" />
    </div>
</template>

<script lang="js">
    export default {
        name:'App',
    }
</script>

<script setup lang="js">
import { ref } from 'vue';
import Person from './components/Person.vue';

    let isShow=ref(true)
</script>

<style scoped>
    .app {
        background-color: #fff;
        box-shadow: 0 0 10px;
        border-radius: 10px;
        padding: 20px;
    }
</style>