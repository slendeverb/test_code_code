import random


def create_board(rows, cols, mines):
    board = [["." for _ in range(cols)] for _ in range(rows)]
    mine_coords = set()

    while len(mine_coords) < mines:
        row = random.randint(0, rows - 1)
        col = random.randint(0, cols - 1)
        if (row, col) not in mine_coords:
            mine_coords.add((row, col))
            board[row][col] = "*"

    return board


def create_display_board(rows, cols):
    return [["-" for _ in range(cols)] for _ in range(rows)]


def count_adjacent_mines(board, row, col):
    rows, cols = len(board), len(board[0])
    count = 0
    for r in range(row - 1, row + 2):
        for c in range(col - 1, col + 2):
            if 0 <= r < rows and 0 <= c < cols and board[r][c] == "*":
                count += 1
    return count


def reveal(board, display_board, row, col, visited):
    if (
        not (0 <= row < len(board))
        or not (0 <= col < len(board[0]))
        or visited[row][col]
    ):
        return

    visited[row][col] = True
    adjacent_mines = count_adjacent_mines(board, row, col)
    display_board[row][col] = str(adjacent_mines) if adjacent_mines else " "

    if adjacent_mines == 0:
        for r in range(row - 1, row + 2):
            for c in range(col - 1, col + 2):
                reveal(board, display_board, r, c, visited)


def print_board(board):
    column_width = len(str(len(board[0])))
    row_width = len(str(len(board)))

    print(" " * (row_width + 1), end="")
    for col in range(1, len(board[0]) + 1):
        print(f"{col:{column_width}}", end=" ")
    print()

    for row in range(len(board)):
        print(f"{row + 1:{row_width}}", end=" ")
        for cell in board[row]:
            print(f"{cell:>{column_width}}", end=" ")
        print()


def play_game(rows, cols, mines):
    board = create_board(rows, cols, mines)
    display_board = create_display_board(rows, cols)
    visited = [[False for _ in range(cols)] for _ in range(rows)]
    remaining_cells = rows * cols - mines

    while True:
        print_board(display_board)
        action = input(
            "Enter action (reveal/flag) and row and column (e.g. 'reveal 1 2'): "
        ).split()

        if len(action) != 3:
            print("Invalid input. Please follow the format 'reveal 1 2' or 'flag 1 2'.")
            continue

        command, row, col = action[0].lower(), int(action[1]) - 1, int(action[2]) - 1

        if command not in ("reveal", "flag"):
            print("Invalid command. Please use 'reveal' or 'flag'.")
            continue

        if not (0 <= row < rows) or not (0 <= col < cols):
            print(
                f"Invalid row or column. Please use values between 1 and {rows} for rows and 1 and {cols} for columns."
            )
            continue

        if command == "reveal":
            if board[row][col] == "*":
                print("You hit a mine! Game over.")
                return
            if not visited[row][col]:
                reveal(board, display_board, row, col, visited)
                remaining_cells -= 1
        elif command == "flag":
            display_board[row][col] = "F" if display_board[row][col] != "F" else "-"

        if remaining_cells == 0:
            print("Congratulations! You've cleared all non-mine cells!")
            return


play_game(10, 10, 10)
