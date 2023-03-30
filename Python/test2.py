import random

# Generate the board
n = 8
m = 8
num_mines = 10
board = [[0] * m for _ in range(n)]
mines = random.sample(range(n*m), num_mines)
for mine in mines:
    x = mine // m
    y = mine % m
    board[x][y] = -1
    for i in range(-1, 2):
        for j in range(-1, 2):
            if x+i < 0 or x+i >= n or y+j < 0 or y+j >= m:
                continue
            if board[x+i][y+j] == -1:
                continue
            board[x+i][y+j] += 1

# Hide the board
hidden_board = [['x' for _ in range(m)] for _ in range(n)]

# Show the surrounding information when a coordinate is inputted
while True:
    x, y = input("Please input the coordinates (x y): ").split()
    x, y = int(x), int(y)
    if board[x][y] == -1:
        print("Oops! You hit a mine. Game over.")
        break
    hidden_board[x][y] = str(board[x][y])
    for i in range(-1, 2):
        for j in range(-1, 2):
            if x+i < 0 or x+i >= n or y+j < 0 or y+j >= m:
                continue
            if hidden_board[x+i][y+j] != 'x':
                continue
            hidden_board[x+i][y+j] = str(board[x+i][y+j])
    for row in hidden_board:
        print(" ".join(row))
