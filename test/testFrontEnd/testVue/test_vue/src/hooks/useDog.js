import axios from 'axios';
import { ref } from 'vue';

export default function (){
    let dogList=ref([

    ])

    async function oneMoreDog(){
        try {
            let result=await axios.get('https://dog123.ceo/api/breeds/image/random')
            dogList.value.push(result.data.message)
        } catch (error) {
            alert(error)
        }
    }

    return {dogList,oneMoreDog}
}