// Set up the canvas and context
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

// Set up the game variables
const snakeSize = 10;
let snake = [{x: 50, y: 50}];
let food = {x: 0, y: 0};
let direction = "right";
let score = 0;

// Set up the game loop
setInterval(gameLoop, 100);

// Generate a random position for the food
function generateFood() {
  food.x = Math.floor(Math.random() * (canvas.width / snakeSize)) * snakeSize;
  food.y = Math.floor(Math.random() * (canvas.height / snakeSize)) * snakeSize;
}

// Handle keyboard input
document.addEventListener("keydown", function(event) {
  if (event.keyCode === 37 && direction !== "right") {
    direction = "left";
  }
  if (event.keyCode === 38 && direction !== "down") {
    direction = "up";
  }
  if (event.keyCode === 39 && direction !== "left") {
    direction = "right";
  }
  if (event.keyCode === 40 && direction !== "up") {
    direction = "down";
  }
});

// Main game loop
function gameLoop() {
  // Move the snake
  let head = {x: snake[0].x, y: snake[0].y};
  if (direction === "right") {
    head.x += snakeSize;
  }
  if (direction === "left") {
    head.x -= snakeSize;
  }
  if (direction === "up") {
    head.y -= snakeSize;
  }
  if (direction === "down") {
    head.y += snakeSize;
  }
  snake.unshift(head);

  // Check for collision with the walls
  if (snake[0].x < 0 || snake[0].x >= canvas.width || snake[0].y < 0 || snake[0].y >= canvas.height) {
    alert("Game over! Your score was " + score);
    location.reload();
  }

  // Check for collision with the food
  if (snake[0].x === food.x && snake[0].y === food.y) {
    generateFood();
    score += 10;
  } else {
    snake.pop();
  }

  // Draw the game
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.fillStyle = "green";
  for (let i = 0; i < snake.length; i++) {
    ctx.fillRect(snake[i].x, snake[i].y, snakeSize, snakeSize);
  }
  ctx.fillStyle = "red";
  ctx.fillRect(food.x, food.y, snakeSize, snakeSize);
  ctx.fillStyle = "white";
  ctx.font = "20px Arial";
  ctx.fillText("Score: " + score, 10, 30);
}