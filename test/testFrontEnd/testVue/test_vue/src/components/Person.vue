<template>
    <div class="person">
        <h2>当前值为: {{ sum }}</h2>
        <button @click="add">点我sum+1</button>
        <hr>
        <img v-for="(dog,index) in dogList" :key="index" :src="dog" alt=""><br>
        <button @click="oneMoreDog">再来一只狗</button>
    </div>
</template>

<script lang="js">
    export default {
        name:'Person',
    }
</script>

<script setup lang="js">
import useDog from '../hooks/useDog';
import useSum from '../hooks/useSum';

    const {sum,add}=useSum()
    const {dogList,oneMoreDog}=useDog()
</script>

<style scoped>
    .person {
        background-color: skyblue;
        box-shadow: 0 0 10px;
        border-radius: 10px;
        padding: 20px;
    }
    button {
        margin: 0 5px;
    }
    li {
        font-size: 20px;
    }
    img {
        height: 100px;
        margin-right: 10px;
    }
</style>