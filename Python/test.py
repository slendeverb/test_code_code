import random
import tkinter as tk
from tkinter import messagebox


class MinesweeperGame(tk.Tk):
    def __init__(self, rows, cols, mines):
        super().__init__()
        self.title("Minesweeper")

        self.rows = rows
        self.cols = cols
        self.mines = mines

        self.board = self.create_board(rows, cols, mines)
        self.display_board = self.create_display_board(rows, cols)
        self.visited = [[False for _ in range(cols)] for _ in range(rows)]
        self.revealed_cells = 0

        self.mine_counter = tk.StringVar()
        self.mine_counter.set(str(mines))

        mine_label = tk.Label(self, text="Mines left: ")
        mine_label.grid(row=0, column=0, columnspan=cols//2, sticky="w")

        mine_count_label = tk.Label(self, textvariable=self.mine_counter)
        mine_count_label.grid(row=0, column=cols//2,
                              columnspan=cols//2, sticky="e")

        self.buttons = [[tk.Button(self, text=" ", width=3, height=1, bg=("white" if (row + col) % 2 == 0 else "light gray"))
                         for col in range(cols)] for row in range(rows)]

        for row in range(rows):
            for col in range(cols):
                self.buttons[row][col].grid(row=row + 1, column=col)
                self.buttons[row][col].bind(
                    '<Button-1>', lambda e, r=row, c=col: self.reveal(r, c))
                self.buttons[row][col].bind(
                    '<Button-3>', lambda e, r=row, c=col: self.toggle_flag(r, c))

    def create_board(self, rows, cols, mines):
        board = [['.' for _ in range(cols)] for _ in range(rows)]
        mine_coords = set()

        while len(mine_coords) < mines:
            row = random.randint(0, rows - 1)
            col = random.randint(0, cols - 1)
            if (row, col) not in mine_coords:
                mine_coords.add((row, col))
                board[row][col] = '*'

        return board

    def create_display_board(self, rows, cols):
        return [['-' for _ in range(cols)] for _ in range(rows)]

    def count_adjacent_mines(self, row, col):
        count = 0
        for r in range(row - 1, row + 2):
            for c in range(col - 1, col + 2):
                if 0 <= r < self.rows and 0 <= c < self.cols and self.board[r][c] == '*':
                    count += 1
        return count

    def toggle_flag(self, row, col):
        if self.display_board[row][col] == 'F':
            self.display_board[row][col] = '-'
            self.buttons[row][col].config(text=" ", state="normal")
            self.mines += 1
        elif self.display_board[row][col] == '-':
            self.display_board[row][col] = 'F'
            self.buttons[row][col].config(text="F", state="disabled")
            self.mines -= 1

        self.mine_counter.set(str(self.mines))
        self.check_win()

    def reveal(self, row, col):
        if not (0 <= row < self.rows) or not (0 <= col < self.cols) or self.visited[row][col]:
            return
        self.visited[row][col] = True

        if self.board[row][col] == '*':
            self.game_over()
            return

        adjacent_mines = self.count_adjacent_mines(row, col)
        self.buttons[row][col].config(text=str(adjacent_mines), state="disabled", relief="sunken",
                                      bg=("white" if (row + col) % 2 == 0 else "light gray"))

        if adjacent_mines == 0:
            for r in range(row - 1, row + 2):
                for c in range(col - 1, col + 2):
                    self.reveal(r, c)
        else:
            self.revealed_cells += 1
            self.check_win()

    def game_over(self):
        for row in range(self.rows):
            for col in range(self.cols):
                if self.board[row][col] == '*':
                    self.buttons[row][col].config(text="*", state="disabled")
        messagebox.showinfo("Game Over", "You hit a mine! Game over.")

    def check_win(self):
        if self.revealed_cells == self.rows * self.cols - self.mines:
            messagebox.showinfo("Congratulations!", "You've successfully revealed all non-mine cells! You win!")


if __name__ == "__main__":
    game = MinesweeperGame(10, 10, 10)
    game.mainloop()
