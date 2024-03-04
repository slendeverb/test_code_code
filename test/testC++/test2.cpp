#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <bit>
#include <windows.h>
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <compare>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <format>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <numbers>
#include <optional>
#include <set>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//
using namespace std;

template <typename T, size_t WIDTH = 10, size_t HEIGHT = 10>
class Grid
{
public:
    Grid() = default;
    virtual ~Grid() = default;

    Grid(const Grid &src) = default;
    Grid &operator=(const Grid &rhs) = default;

    template <typename E, size_t WIDTH2, size_t HEIGHT2>
    Grid(const Grid<E, WIDTH2, HEIGHT2> &src);

    template <typename E, size_t WIDTH2, size_t HEIGHT2>
    Grid &operator=(const Grid<E, WIDTH2, HEIGHT2> &rhs);

    void swap(Grid &other) noexcept;

    std::optional<T> &at(size_t x, size_t y);
    const std::optional<T> &at(size_t x, size_t y) const;

    size_t getWidth() const { return WIDTH; }
    size_t getHeight() const { return HEIGHT; }

private:
    void verifyCoordinate(size_t x, size_t y) const;

    std::optional<T> m_cells[WIDTH][HEIGHT];
};
template <typename T, size_t WIDTH, size_t HEIGHT>
template <typename E, size_t WIDTH2, size_t HEIGHT2>
Grid<T, WIDTH, HEIGHT>::Grid(const Grid<E, WIDTH2, HEIGHT2> &src)
{
    for (size_t i = 0; i < WIDTH; i++)
    {
        for (size_t j = 0; j < HEIGHT; j++)
        {
            if (i < WIDTH2 && j < HEIGHT2)
            {
                m_cells[i][j] = src.at(i, j);
            }
            else
            {
                m_cells[i][j].reset();
            }
        }
    }
}
template <typename T, size_t WIDTH, size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::swap(Grid &other) noexcept
{
    std::swap(m_cells, other.m_cells);
}
template <typename T, size_t WIDTH, size_t HEIGHT>
std::optional<T> &Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y)
{
    return const_cast<std::optional<T> &>(std::as_const(*this).at(x, y));
}
template <typename T, size_t WIDTH, size_t HEIGHT>
const std::optional<T> &Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y) const
{
    this->verifyCoordinate(x, y);
    return m_cells[x][y];
}
template <typename T, size_t WIDTH, size_t HEIGHT>
template <typename E, size_t WIDTH2, size_t HEIGHT2>
Grid<T, WIDTH, HEIGHT> &Grid<T, WIDTH, HEIGHT>::operator=(const Grid<E, WIDTH2, HEIGHT2> &rhs)
{
    Grid<T, WIDTH, HEIGHT> temp{rhs};
    this->swap(temp);
    return *this;
}
template <typename T, size_t WIDTH, size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::verifyCoordinate(size_t x, size_t y) const
{
    if (x >= WIDTH)
    {
        throw std::out_of_range{std::format("{} must be less than {}.", x, WIDTH)};
    }
    if (y >= HEIGHT)
    {
        throw std::out_of_range{std::format("{} must be less than {}.", y, HEIGHT)};
    }
}

template <>
class Grid<const char *>
{
public:
    explicit Grid(size_t width = DefaultWidth, size_t height = DefaultHeight);
    virtual ~Grid() = default;

    Grid(const Grid &src) = default;
    Grid &operator=(const Grid &rhs) = default;

    Grid(Grid &&src) = default;
    Grid &operator=(Grid &&rhs) = default;

    std::optional<std::string> &at(size_t x, size_t y);
    const std::optional<std::string> &at(size_t x, size_t y) const;

    size_t getHeight() const { return m_height; }
    size_t getWidth() const { return m_width; }

    static const size_t DefaultWidth{10}, DefaultHeight{10};

private:
    void verifyCoordinate(size_t x, size_t y) const;

    std::vector<std::vector<std::optional<std::string>>> m_cells;
    size_t m_width{0}, m_height{0};
};
Grid<const char *>::Grid(size_t width, size_t height)
    : m_width{width}, m_height{height}
{
    m_cells.resize(m_width);
    for (auto &column : m_cells)
    {
        column.resize(m_height);
    }
}
void Grid<const char *>::verifyCoordinate(size_t x, size_t y) const
{
    if (x >= m_width)
    {
        throw std::out_of_range{std::format("{} must be less than {}.", x, m_width)};
    }
    if (y >= m_height)
    {
        throw std::out_of_range{std::format("{} must be less than {}.", y, m_height)};
    }
}
const std::optional<std::string> &Grid<const char *>::at(size_t x, size_t y) const
{
    this->verifyCoordinate(x, y);
    return m_cells[x][y];
}
std::optional<std::string> &Grid<const char *>::at(size_t x, size_t y)
{
    return const_cast<std::optional<std::string> &>(std::as_const(*this).at(x, y));
}

template <typename T>
class GameBoard : public Grid<T>
{
public:
    explicit GameBoard(size_t width = Grid<T>::DefaultWidth, size_t height = Grid<T>::DefaultHeight);
    void move(size_t xSrc, size_t ySrc, size_t xDest, size_t yDest);
};
template <typename T>
GameBoard<T>::GameBoard(size_t width, size_t height)
    : Grid<T>{width, height} {}
template <typename T>
void GameBoard<T>::move(size_t xSrc, size_t ySrc, size_t xDest, size_t yDest)
{
    Grid<T>::at(xDest, yDest) = std::move(Grid<T>::at(xSrc, ySrc));
    Grid<T>::at(xSrc, ySrc).reset();
}

template <typename T>
class SpreadsheetCell
{
public:
    SpreadsheetCell(T t) : m_content{std::move(t)} {}
    const T &getContent() const { return m_content; }

private:
    T m_content;
};
SpreadsheetCell(const char *) -> SpreadsheetCell<std::string>;

void solve()
{
    Grid<int> myIntGrid;
    Grid<const char *> stringGrid1{2, 2};
    const char *dummy{"dummy"};
    stringGrid1.at(0, 0) = "hello";
    stringGrid1.at(0, 1) = dummy;
    stringGrid1.at(1, 0) = dummy;
    stringGrid1.at(1, 1) = "there";

    Grid<const char *> stringGrid2{stringGrid1};
}

int main()
{
    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "\n运行时间: " << endTime - startTime << std::endl;
    return 0;
}
