<template>
    <div class="home">
        <img src="https://www.atguigu.com/images/index_new/logo.png" alt="">
    </div>
</template>

<script lang="js">
    export default {
        name:'Home',
    }
</script>

<script setup lang="js">
import { onMounted } from 'vue';
import { useRouter } from 'vue-router';

    const router=useRouter()
    onMounted(() => {
        setTimeout(() => {
            router.push({
                name:'news'
            })            
        },3000)
    })
</script>

<style scoped>
    .home{
        display: flex;
        justify-content: center;
        align-items: center;
        height: 100%;
    }
</style>