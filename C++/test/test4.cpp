#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

struct Button
{
    int taken;

    Button(int taken) : taken(taken) {}
};

class Game
{
private:
    const int NUMS = 19;
    std::map<std::pair<int, int>, Button> buttons;
    std::vector<std::pair<int, int>> nearpos{{1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    std::vector<char> trans{'.', 'c', 'p'};

public:
    Game(std::vector<std::vector<int>> board)
    {
        for (int i = 0; i < NUMS; i++)
        {
            for (int j = 0; j < NUMS; j++)
            {
                buttons[std::make_pair(i, j)] = Button(board[i][j]);
            }
        }
    }

    void display()
    {
        std::cout << ' ';
        for (int j = 0; j < NUMS; j++)
        {
            std::cout << j % 10;
        }
        std::cout << std::endl;
        for (int i = 0; i < NUMS; i++)
        {
            std::cout << i % 10;
            for (int j = 0; j < NUMS; j++)
            {
                std::cout << trans[buttons[std::make_pair(i, j)].taken + 1];
            }
            std::cout << std::endl;
        }
    }

    std::pair<int, std::pair<int, int>> compute(int player)
    {
        std::vector<std::pair<std::pair<int, int>, int>> bsites_values;

        int choice_num = 0;
        for (const auto &button : buttons)
        {
            if (button.second.taken == -1)
            {
                choice_num++;
            }
        }

        if (choice_num == 0)
        {
            std::cout << "no one wins...game over" << std::endl;
            return std::make_pair(-1, std::make_pair(-1, -1));
        }

        for (const auto &bpos_button : buttons)
        {
            auto bpos = bpos_button.first;
            int value = 0;
            for (const auto &step_pos : nearpos)
            {
                int _space = 0;
                for (int i = 1; i < 5; i++)
                {
                    auto npos = _add(bpos, _mul(step_pos, i));
                    if (npos == nullptr || buttons[npos].taken == 1 - player)
                    {
                        break;
                    }
                    else
                    {
                        _space++;
                    }
                }
                for (int i = 1; i < 5; i++)
                {
                    auto npos = _add(bpos, _mul(step_pos, -i));
                    if (npos == nullptr || buttons[npos].taken == 1 - player)
                    {
                        break;
                    }
                    else
                    {
                        _space++;
                    }
                }
                if (_space < 4)
                {
                    continue;
                }

                int max_step = 1;
                for (int i = -1; i > -5; i--)
                {
                    int _t = 1;
                    auto npos = _add(bpos, _mul(step_pos, i));
                    if (npos == nullptr || buttons[npos].taken == 1 - player)
                    {
                        break;
                    }
                    for (int j = 0; j < 5; j++)
                    {
                        npos = _add(npos, step_pos);
                        if (npos == nullptr || buttons[npos].taken == 1 - player)
                        {
                            break;
                        }
                        if (buttons[npos].taken == player)
                        {
                            _t++;
                        }
                    }
                    if (_t > max_step)
                    {
                        max_step = _t;
                    }
                }
                value += pow(10, max_step - 1);

                auto npos = _add(bpos, step_pos);
                if (npos != nullptr && buttons[npos].taken == player)
                {
                    value += 1;
                }
                npos = _add(bpos, _mul(step_pos, -1));
                if (npos != nullptr && buttons[npos].taken == player)
                {
                    value += 1;
                }
            }
            if (value > 0)
            {
                bsites_values.push_back(std::make_pair(bpos, value));
            }
        }

        int _maxvalue = 0;
        std::pair<int, int> _maxp = std::make_pair(-1, -1);
        for (const auto &bpos_value : bsites_values)
        {
            int v = bpos_value.second;
            if (v > _maxvalue)
            {
                _maxvalue = v;
                _maxp = bpos_value.first;
            }
        }

        if (_maxp == std::make_pair(-1, -1))
        {
            std::vector<std::pair<int, int>> bsites;
            for (const auto &bpos_button : buttons)
            {
                auto bpos = bpos_button.first;
                if (bpos_button.second.taken == -1)
                {
                    bsites.push_back(bpos);
                }
            }
            _maxp = bsites[rand() % bsites.size()];
        }

        return std::make_pair(_maxvalue, _maxp);
    }

    std::pair<int, int> _mul(std::pair<int, int> pos1, int n)
    {
        return std::make_pair(pos1.first * n, pos1.second * n);
    }

    std::pair<int, int> *_add(std::pair<int, int> pos1, std::pair<int, int> pos2)
    {
        std::pair<int, int> npos(pos1.first + pos2.first, pos1.second + pos2.second);
        if (npos.first >= NUMS || npos.second >= NUMS || npos.first < 0 || npos.second < 0)
        {
            return nullptr;
        }
        return new std::pair<int, int>(npos);
    }

    bool check_over()
    {
        for (int rows = 0; rows < NUMS; rows++)
        {
            int step_compute = 0, step_person = 0;
            for (int cols = 0; cols < NUMS; cols++)
            {
                auto npos = std::make_pair(rows, cols);
                if (buttons[npos].taken == 0)
                {
                    step_compute++;
                    step_person = 0;
                    if (step_compute >= 5)
                    {
                        std::cout << "c win" << std::endl;
                        return true;
                    }
                }
                else if (buttons[npos].taken == 1)
                {
                    step_compute = 0;
                    step_person++;
                    if (step_person >= 5)
                    {
                        std::cout << "p win" << std::endl;
                        return true;
                    }
                }
                else
                {
                    step_compute = 0;
                    step_person = 0;
                }
            }
        }

        for (int cols = 0; cols < NUMS; cols++)
        {
            int step_compute = 0, step_person = 0;
            for (int rows = 0; rows < NUMS; rows++)
            {
                auto npos = std::make_pair(rows, cols);
                if (buttons[npos].taken == 0)
                {
                    step_compute++;
                    step_person = 0;
                    if (step_compute >= 5)
                    {
                        std::cout << "c win" << std::endl;
                        return true;
                    }
                }
                else if (buttons[npos].taken == 1)
                {
                    step_compute = 0;
                    step_person++;
                    if (step_person >= 5)
                    {
                        std::cout << "p win" << std::endl;
                        return true;
                    }
                }
                else
                {
                    step_compute = 0;
                    step_person = 0;
                }
            }
        }

        for (const auto &pos : std::vector<std::pair<int, int>>{{0, 0}, {0, NUMS - 1}})
        {
            std::pair<int, int> _step = (pos.first == 0) ? std::make_pair(-1, 1) : std::make_pair(1, 1);
            int n = 0;
            int step_compute = 0, step_person = 0;
            while (true)
            {
                auto npos = _add(pos, _mul(_step, n));
                if (npos == nullptr)
                {
                    break;
                }
                if (buttons[npos].taken == 0)
                {
                    step_compute++;
                    step_person = 0;
                    if (step_compute >= 5)
                    {
                        std::cout << "c win" << std::endl;
                        return true;
                    }
                }
                else if (buttons[npos].taken == 1)
                {
                    step_compute = 0;
                    step_person++;
                    if (step_person >= 5)
                    {
                        std::cout << "p win" << std::endl;
                        return true;
                    }
                }
                else
                {
                    step_compute = 0;
                    step_person = 0;
                }
                n++;
            }
        }

        return false;
    }

    std::pair<int, int> next(int player)
    {
        auto cv = compute(player);
        auto pv = compute(1 - player);
        if (cv.first > pv.first)
        {
            return cv.second;
        }
        else
        {
            return pv.second;
        }
    }
};

int main()
{
    std::srand(static_cast<unsigned>(std::time(0)));

    int a;
    std::cout << "先手请输入1，后手请输入2：";
    std::cin >> a;

    std::vector<std::vector<int>> board(19, std::vector<int>(19, -1));

    if (a == 1)
    {
        board[9][9] = 0;
        Game game(board);
        game.display();
    }

    while (true)
    {
        int x, y;
        std::cout << "input x: ";
        std::cin >> x;
        std::cout << "input y: ";
        std::cin >> y;

        board[x][y] = 1;
        Game game(board);
        auto pos = game.next(0);
        board[pos.first][pos.second] = 0;
        game = Game(board);
        game.display();

        if (game.check_over())
        {
            break;
        }
    }

    return 0;
}
