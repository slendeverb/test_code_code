<template>
    <div class="news">
        <!-- 导航区 -->
        <ul>
            <li v-for="news in newsList" :key="news.id">
                <button @click="showNewsDetail(news)">查看新闻</button>
                <RouterLink :to="{
                    name:'detail',
                    query:news
                }">
                    {{ news.title }}
                </RouterLink>
            </li>
        </ul>
        <!-- 展示区 -->
         <div class="news-content">
            <RouterView></RouterView>
         </div>
    </div>
</template>

<script lang="js">
    export default {
        name:'News',
    }
</script>

<script setup lang="js">
import { ref } from 'vue';
import { RouterView, useRouter } from 'vue-router';

    const router=useRouter()
    const newsList=ref([
        {id:'01',title:'很好的抗癌食物',content:'西兰花'},
        {id:'02',title:'如何一夜暴富',content:'学IT'},
        {id:'03',title:'震惊，万万没想到',content:'明天是周一'},
        {id:'04',title:'好消息！好消息！',content:'快过年了'}
    ])
    function showNewsDetail(news){
        router.push({
            name:'detail',
            query:news
        })
    }
</script>

<style scoped>
    .news{
        padding: 0 20px;
        display: flex;
        justify-content: space-between;
        height: 100%;
    }
    .news ul{
        margin-top: 30px;
        /* list-style: none; */
        padding-left: 10px;
    }
    .news li::marker{
        color: #64767E;
    }
    .news li>a{
        font-size: 18px;
        line-height: 40px;
        text-decoration: none;
        color: #64767E;
        text-shadow: 0 0 1px rgb(0, 84, 0);
    }
    .news li>a:hover{
        width: 70%;
        height: 90%;
        border: 1px solid;
        margin-top: 20px;
        border-radius: 5px;
    }
    .news-content{
        width: 70%;
        height: 90%;
        border: 1px solid;
        margin-top: 20px;
        border-radius: 5px;
    }
</style>