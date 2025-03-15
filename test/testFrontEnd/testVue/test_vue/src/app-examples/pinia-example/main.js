import { createApp } from 'vue'
import './style.css'
import App from './App.vue'
import { createPinia } from 'pinia'

let app=createApp(App)
let pinia=createPinia()
app.use(pinia)
app.mount('#app')