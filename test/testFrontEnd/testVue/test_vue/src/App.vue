<template>
    <div class="app">
        <h1>诗歌: </h1>
        <p> 相见时难别亦难,东风无力百花残</p>
        <Person/>
    </div>
</template>

<script lang="js">
    import Person from './components/Person.vue';
    export default {
        name:'App',
        components:{
            Person,
        },
    }
</script>

<script setup lang="js">

</script>

<style scoped>
    .app {
        background-color: #fff;
        box-shadow: 0 0 10px;
        border-radius: 10px;
        padding: 20px;
    }
</style>