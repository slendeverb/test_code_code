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
template <typename T>
class Grid
{
public:
    explicit Grid(size_t width = DefaultWidth, size_t height = DefaultHeight);
    virtual ~Grid() = default;

    Grid(const Grid &src) = default;
    Grid &operator=(const Grid &rhs) = default;

    template <typename E>
    Grid(const Grid<E> &src);
    template <typename E>
    Grid &operator=(const Grid<E> &rhs);

    Grid(Grid &&src) = default;
    Grid &operator=(Grid &&rhs) = default;

    std::optional<T> &at(size_t x, size_t y);
    const std::optional<T> &at(size_t x, size_t y) const;

    size_t getHeight() const { return m_height; }
    size_t getWidth() const { return m_width; }

    void swap(Grid& other) noexcept;

    static const size_t DefaultWidth{10}, DefaultHeight{10};

private:
    void verifyCoornidate(size_t x, size_t y) const;

    std::vector<std::vector<std::optional<T>>> m_cells;
    size_t m_width{0}, m_height{0};
};
template <typename T>
Grid<T>::Grid(size_t width, size_t height)
    : m_width{width}, m_height{height}
{
    m_cells.resize(m_width);
    for (auto &column : m_cells)
    {
        column.resize(m_height);
    }
}
template <typename T>
void Grid<T>::verifyCoornidate(size_t x, size_t y) const
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
template <typename T>
const std::optional<T> &Grid<T>::at(size_t x, size_t y) const
{
    this->verifyCoornidate(x, y);
    return m_cells[x][y];
}
template <typename T>
std::optional<T> &Grid<T>::at(size_t x, size_t y)
{
    return const_cast<std::optional<T> &>(std::as_const(*this).at(x, y));
}
template <typename T>
template <typename E>
Grid<T>::Grid(const Grid<E> &src)
    : Grid{src.getWidth(), src.getHeight()}
{
    for (size_t i = 0; i < m_width; i++)
    {
        for (size_t j = 0; j < m_height; j++)
        {
            m_cells[i][j] = src.at(i, j);
        }
    }
}
template <typename T>
void Grid<T>::swap(Grid& other) noexcept
{
    std::swap(m_width,other.m_width);
    std::swap(m_height,other.m_height);
    std::swap(m_cells,other.m_cells);
}
template <typename T>
template <typename E>
Grid<T>& Grid<T>::operator=(const Grid<E>& rhs)
{
    Grid<T> temp{rhs};
    this->swap(temp);
    return *this;
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
    std::string myString{"Hello World!"};
    SpreadsheetCell myCell{myString};
    SpreadsheetCell myCell2{"Hello World!"};
}

int main()
{
    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "\n运行时间: " << endTime - startTime << std::endl;
    return 0;
}
