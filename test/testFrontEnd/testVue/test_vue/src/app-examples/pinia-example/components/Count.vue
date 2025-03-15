<template>
    <div class="count">
        <h2>当前求和为: {{ countStore.sum }}</h2>
        <h2>学校：{{ countStore.school }}，坐落于：{{ countStore.address }}</h2>
        <select v-model.number="n">
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
        </select>
        <button @click="add">加</button>
        <button @click="sub">减</button>
    </div>
</template>

<script lang="js">
    export default {
        name:'Count',
    }
</script>

<script setup lang="js">
import { ref } from 'vue';
import {useCountStore} from '@/store/count'

    const countStore=useCountStore()
    let n=ref(1)

    function add(){
        countStore.add()
    }
    function sub(){
        countStore.sub()
    }
</script>

<style scoped>
    .count{
        background-color: skyblue;
        padding: 10px;
        border-radius: 10px;
        box-shadow: 0 0 10px;
    }
    select,button{
        margin: 0 5px;
        height: 25px;
    }
</style>