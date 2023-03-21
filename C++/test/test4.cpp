#include <cstdio>
#include <cstring>

const int MAX_SIZE = 2187; // 最大分形图大小

char grid[MAX_SIZE][MAX_SIZE];

void fill(int x, int y, int size, bool space)
{
	if (space)
	{
		memset(&grid[x][y], ' ', size * size * sizeof(char));
	}
	else
	{
		if (size == 1)
		{
			grid[x][y] = 'X';
			return;
		}
		int sub_size = size / 3;
		fill(x, y, sub_size, false);
		fill(x, y + sub_size, sub_size, true);
		fill(x, y + 2 * sub_size, sub_size, false);
		fill(x + sub_size, y, sub_size, true);
		fill(x + sub_size, y + sub_size, sub_size, false);
		fill(x + sub_size, y + 2 * sub_size, sub_size, true);
		fill(x + 2 * sub_size, y, sub_size, false);
		fill(x + 2 * sub_size, y + sub_size, sub_size, true);
		fill(x + 2 * sub_size, y + 2 * sub_size, sub_size, false);
	}
}

int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		memset(grid, ' ', sizeof(grid));
		fill(0, 0, 3 * (1 << (n - 1)), false);
		for (int i = 0; i < 3 * (1 << (n - 1)); i++)
		{
			printf("%.*s\n", 3 * (1 << (n - 1)), grid[i]);
		}
		printf("-\n");
	}
	return 0;
}