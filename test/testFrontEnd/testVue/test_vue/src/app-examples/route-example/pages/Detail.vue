<template>
    <div>
        <ul class="news-list">
            <li>{{ id }}</li>
            <li>{{ title }}</li>
            <li>{{ content }}</li>
        </ul>
    </div>
</template>

<script lang="js">
    export default {
        name:'Detail',
    }
</script>

<script setup lang="js">
    defineProps(['id','title','content'])
</script>

<style scoped>

</style>