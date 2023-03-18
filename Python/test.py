import pygame
import random

# Initialize pygame
pygame.init()

# Set up the game window
window_width = 600
window_height = 400
game_window = pygame.display.set_mode((window_width, window_height))
pygame.display.set_caption("Snake Game")

# Set up the colors
black = (0, 0, 0)
white = (255, 255, 255)
red = (255, 0, 0)
green = (0, 255, 0)

# Set up the font
font = pygame.font.SysFont(None, 25)

# Set up the clock
clock = pygame.time.Clock()

# Set up the game variables
snake_size = 10
snake_speed = 15
food_size = 10

# Define the Snake class
class Snake:
    def __init__(self):
        self.snake_list = [[100, 50], [90, 50], [80, 50]]
        self.direction = "RIGHT"
        
    def draw_snake(self):
        for i in self.snake_list:
            pygame.draw.rect(game_window, green, [i[0], i[1], snake_size, snake_size])
        
    def move_snake(self):
        if self.direction == "RIGHT":
            head = [self.snake_list[0][0] + snake_size, self.snake_list[0][1]]
        elif self.direction == "LEFT":
            head = [self.snake_list[0][0] - snake_size, self.snake_list[0][1]]
        elif self.direction == "UP":
            head = [self.snake_list[0][0], self.snake_list[0][1] - snake_size]
        elif self.direction == "DOWN":
            head = [self.snake_list[0][0], self.snake_list[0][1] + snake_size]
            
        self.snake_list.insert(0, head)
        
    def check_collision(self):
        if self.snake_list[0][0] >= window_width or self.snake_list[0][0] < 0:
            return True
        elif self.snake_list[0][1] >= window_height or self.snake_list[0][1] < 0:
            return True
        for i in self.snake_list[1:]:
            if self.snake_list[0] == i:
                return True
        return False
        
    def check_food_collision(self, food_pos):
        if self.snake_list[0][0] == food_pos[0] and self.snake_list[0][1] == food_pos[1]:
            return True
        return False

# Define the Food class
class Food:
    def __init__(self):
        self.food_pos = [random.randrange(0, window_width - food_size, 10), random.randrange(0, window_height - food_size, 10)]
    
    def draw_food(self):
        pygame.draw.rect(game_window, red, [self.food_pos[0], self.food_pos[1], food_size, food_size])
    
    def update_food(self):
        self.food_pos = [random.randrange(0, window_width - food_size, 10), random.randrange(0, window_height - food_size, 10)]

# Set up the game loop
def game_loop():
    snake = Snake()
    food = Food()
    
    score = 0
    
    game_over = False
    
    while not game_over:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_RIGHT:
                    snake.direction = "RIGHT"
                elif event.key == pygame.K_LEFT:
                    snake.direction = "LEFT"
                elif event.key == pygame.K_UP:
                    snake.direction = "UP"
                elif event.key == pygame.K_DOWN:
                    snake.direction = "DOWN"
        
        snake.move_snake()
        
        if snake.check_collision():
            game_over = True
            
        if snake.check_food_collision(food.food_pos):
            food.update_food()
            score += 1
        else:
            snake.snake_list.pop()
            
        game_window.fill(black)
        
        snake.draw_snake()
        
        food.draw_food()
        
        text = font.render("Score: " + str(score), True, white)
        game_window.blit(text, [0, 0])
        
        pygame.display.update()
        
        clock.tick(snake_speed)
        
    pygame.quit()
    quit()

# Start the game loop
game_loop()