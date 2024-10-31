import { defineStore } from "pinia";
import { ref } from "vue";
import axios from "axios";
import {nanoid} from 'nanoid';

export const useTalk=defineStore('talk',() => {
    let talkList= ref(
        JSON.parse(localStorage.getItem('talkList')) || []
    )

    async function getLoveTalk(){
        try {
            let result=await axios.get('https://api.uomg.com/api/rand.qinghua?format=json')
            talkList.value.unshift({id:nanoid(),content:result.data.content})
        } catch (error) {
            alert(error)
        }
    }

    return {talkList,
        getLoveTalk
    }
})