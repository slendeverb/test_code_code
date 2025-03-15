import TodoItem from "./TodoItem"

function TodoList({todos,deleteTodo,toggleTodo}){
    return (
        <ul>
            {todos.map(todo=>(
                <TodoItem key={todo.id} todo={todo} deleteTodo={deleteTodo} toggleTodo={toggleTodo}></TodoItem>
            ))}
        </ul>
    )
}

export default TodoList