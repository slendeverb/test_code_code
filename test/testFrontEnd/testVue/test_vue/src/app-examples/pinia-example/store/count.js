import { defineStore } from "pinia";
import { ref } from "vue";

export const useCountStore=defineStore('count',() => {
    let sum=ref(666)
    let school=ref('atguigu')
    let address=ref('Beijing')

    function add(){
        sum.value=888
        school.value='尚硅谷'
        address.value='北京'
    }
    function sub(){
        sum.value=666
        school.value='atguigu'
        address.value='Beijing'
    }

    return {sum,school,address,
        add,sub
    }
})