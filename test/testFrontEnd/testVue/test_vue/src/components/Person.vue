<template>
    <div class="person">
        <h2>一辆{{car.brand}}车，价值 {{ car.price }} 万</h2>
        <button @click="changePrice">修改汽车的价格</button>
        <hr>
        <h2>当前求和为: {{ sum }}</h2>
        <button @click="sumPlusOne">点我sum+1</button>
    </div>
</template>

<script lang="js">
    export default {
        name:'Person',
    }
</script>

<script setup lang="js">
    import { ref } from 'vue';

    let car=ref({
        brand:'奔驰',
        price:100
    })
    let sum=ref(0)

    function changePrice(){
        car.value.price+=10
    }
    function sumPlusOne(){
        sum.value+=1
    }
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
        font-size: 150%;
    }
</style>