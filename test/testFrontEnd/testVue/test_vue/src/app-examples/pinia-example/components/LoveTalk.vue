<template>
    <div class="lovetalk">
        <button @click="getLoveTalk">获取一句土味情话</button>
        <ul>
            <li v-for="talk in talkStore.talkList" :key="talk.id">
                {{ talk.content }}
            </li>
        </ul>
    </div>
</template>

<script lang="js">
    export default {
        name:'LoveTalk',
    }
</script>

<script setup lang="js">
import { useTalk } from '@/store/talk';

    const talkStore=useTalk()

    function getLoveTalk(){
        talkStore.getLoveTalk()
    }

    talkStore.$subscribe(() => {
        localStorage.setItem('talkList',JSON.stringify(talkStore.talkList))
    })
</script>

<style scoped>
    .lovetalk{
        background-color: orange;
        padding: 10px;
        border-radius: 10px;
        box-shadow: 0 0 10px;
    }
    select,button{
        margin: 0 5px;
        height: 25px;
    }
</style>