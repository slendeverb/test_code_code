import pygame
import random

# 定义一些常量
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
CELL_SIZE = 20

# 定义颜色常量
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)

# 初始化 Pygame 引擎
pygame.init()

# 创建屏幕对象
screen = pygame.display.set_mode([SCREEN_WIDTH, SCREEN_HEIGHT])

# 设置窗口标题
pygame.display.set_caption('Snake Game')

# 设置时钟对象，控制游戏帧率
clock = pygame.time.Clock()

# 初始化贪吃蛇的位置和长度
snake = [(2, 0), (1, 0), (0, 0)]
direction = 'right'

# 初始化食物的位置
food = (random.randint(0, SCREEN_WIDTH // CELL_SIZE - 1), random.randint(0, SCREEN_HEIGHT // CELL_SIZE - 1))

# 游戏循环
while True:
    # 处理事件
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            # 如果是关闭窗口事件，则退出游戏循环
            pygame.quit()
            quit()

    # 处理键盘事件
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        direction = 'left'
    elif keys[pygame.K_RIGHT]:
        direction = 'right'
    elif keys[pygame.K_UP]:
        direction = 'up'
    elif keys[pygame.K_DOWN]:
        direction = 'down'

    # 更新贪吃蛇的位置
    head = snake[0]
    if direction == 'left':
        new_head = (head[0] - 1, head[1])
    elif direction == 'right':
        new_head = (head[0] + 1, head[1])
    elif direction == 'up':
        new_head = (head[0], head[1] - 1)
    elif direction == 'down':
        new_head = (head[0], head[1] + 1)
    snake.insert(0, new_head)

    # 检查是否吃到食物
    if snake[0] == food:
        food = (random.randint(0, SCREEN_WIDTH // CELL_SIZE - 1), random.randint(0, SCREEN_HEIGHT // CELL_SIZE - 1))
    else:
        snake.pop()

    # 清屏
    screen.fill(WHITE)

    # 画贪吃蛇和食物
    for cell in snake:
        pygame.draw.rect(screen, GREEN, [cell[0] * CELL_SIZE, cell[1] * CELL_SIZE, CELL_SIZE, CELL_SIZE])
    pygame.draw.rect(screen, RED, [food[0] * CELL_SIZE, food[1] * CELL_SIZE, CELL_SIZE, CELL_SIZE])

    # 刷新屏幕
    pygame.display.flip()

    # 控制游戏帧率
    clock.tick(10)
