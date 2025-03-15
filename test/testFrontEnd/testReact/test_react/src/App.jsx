import { useState } from "react"
import AddTodo from "./components/AddTodo"
import TodoFilter from "./components/TodoFilter"
import TodoList from "./components/TodoList"

function App(){
    const [todos,setTodos]=useState([])
    const [filter,setFilter]=useState('all')

    const addTodo=(text)=>{
        const newTodo={
            id:Date.now(),
            text,
            completed:false
        }
        setTodos([...todos,newTodo])
    }

    const deleteTodo=(id)=>{
        setTodos(todos.filter(todo=>todo.id!==id))
    }

    const toggleTodo=(id)=>{
        setTodos(todos.map(todo=>{
            if(todo.id===id){
                todo.completed=!todo.completed
            }
            return todo
        }))
    }

    const getFilteredTodos=()=>{
        switch (filter) {
            case 'completed':
                return todos.filter(todo=>todo.completed)
            case 'active':
                return todos.filter(todo=>!todo.completed)
            default:
                return todos
        }
    }
    
    return (
        <div>
            <h1>TodoList</h1>
            <AddTodo addTodo={addTodo}></AddTodo>
            <TodoList todos={getFilteredTodos()} deleteTodo={deleteTodo} toggleTodo={toggleTodo}></TodoList>
            <TodoFilter setFilter={setFilter}></TodoFilter>
        </div>
    )
}

export default App