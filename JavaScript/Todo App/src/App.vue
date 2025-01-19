<script setup>
import { ref } from 'vue'

const input = ref('')
const list = ref([])

function add() {
  if (input.value === '') {
    return
  }

  list.value.push({
    value: input.value,
    isCompleted: false,
  })

  input.value = ''
}

function del(index) {
  list.value.splice(index, 1)
}
</script>

<template>
  <h1 class="title">Todo App</h1>
  <div class="input-form">
    <input class="inpput-str" v-model="input" type="text" placeholder="请输入待办事项..." />
    <button class="input-btn" @click="add">添加</button>
  </div>
  <div
    v-for="(item, index) in list"
    :key="index"
    :class="['items', item.isCompleted ? 'completed' : 'uncompleted']"
  >
    <div>
      <input v-model="item.isCompleted" type="checkbox" />
      <span class="item-str">{{ item.value }}</span>
    </div>
    <div><button @click="del(index)">删除</button></div>
  </div>
</template>

<style scoped>
.title {
  text-align: center;
}

.input-form {
  display: flex;
  margin: 30px auto 30px auto;
  width: 60%;
}

.input-btn {
  width: 20%;
  height: 54px;
  border-radius: 0 10px 10px 0;
}

.inpput-str {
  width: 80%;
  height: 50px;
  padding: 0 15px;
  border-radius: 10px 0 0 10px;
}

.items {
  display: flex;
  align-items: center;
  justify-content: space-between;
  width: 60%;
  height: 50px;
  margin: 8px auto;
  padding: 16px;
  box-sizing: border-box;
  border-radius: 10px;
  box-shadow: 0 4px 10px gray;
}

.item-str {
  margin-left: 10px;
}

.completed {
  text-decoration: line-through;
  opacity: 0.4;
}
</style>
