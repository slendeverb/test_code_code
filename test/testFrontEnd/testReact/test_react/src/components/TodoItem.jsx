function TodoItem({todo,deleteTodo,toggleTodo}){
    return (
        <li style={{textDecoration:todo.completed?'line-through':'none'}}>
            {todo.text}
            <button onClick={()=>toggleTodo(todo.id)}>切换</button>
            <button onClick={()=>deleteTodo(todo.id)}>删除</button>
        </li>
    )
}

export default TodoItem