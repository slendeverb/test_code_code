import { createRouter, createWebHistory } from "vue-router";
import Home from "@/pages/Home.vue";
import News from "@/pages/News.vue";
import About from "@/pages/About.vue";
import Detail from "@/pages/Detail.vue";

const router=createRouter({
    history:createWebHistory(),
    routes:[
        {
            name:'home',
            path:'/home',
            component:Home
        },
        {
            name:'news',
            path:'/news',
            component:News,
            children:[
                {
                    name:'detail',
                    path:'detail',
                    component:Detail,
                    props(route){
                        return route.query
                    }
                }
            ]
        },
        {
            name:'about',
            path:'/about',
            component:About
        },
        {
            path:'/',
            redirect:'/home'
        }
    ]
})

export default router