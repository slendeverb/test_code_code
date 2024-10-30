<template>
    <div class="lovetalk">
        <button @click="getLoveTalk">获取一句土味情话</button>
        <ul>
            <li v-for="talk in talkList" :key="talk.id">
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
import axios from 'axios';
import { ref } from 'vue';
import {nanoid} from 'nanoid';

    let talkList=ref([
        {id:'01',content:'今天你有点怪？哪里怪？怪好看的！'},
        {id:'02',content:'蓝莓，草莓，蔓越莓，今天想我了没？'},
        {id:'03',content:'心里给你留了一块地，我的死心塌地'}
    ])

    async function getLoveTalk(){
        try {
            let result=await axios.get('https://api.uomg.com/api/rand.qinghua?format=json')
            talkList.value.unshift({id:nanoid(),content:result.data.content})
        } catch (error) {
            alert(error)
        }
    }
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