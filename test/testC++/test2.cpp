#include <stdexcept>
#include <new>
#include <source_location>
#include <cstdarg>
#include <filesystem>
#include <iomanip>
#include <concepts>
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
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//
using namespace std;
using namespace std::filesystem;

template<typename T>
class Matrix{
public:
    Matrix(size_t width,size_t height);
    virtual ~Matrix();
private:
    void cleanup();
    size_t m_width{0};
    size_t m_height{0};
    T** m_matrix{nullptr};
};

void solve()
{
    
}

int main()
{
    std::ifstream in{"../in.txt"};
    std::streambuf *oldIn{std::cin.rdbuf(in.rdbuf())};
    std::ofstream out{"../out.txt"};
    std::streambuf *oldOut{std::cout.rdbuf(out.rdbuf())};
    std::ofstream err{"../err.txt"};
    std::streambuf *oldErr{std::cerr.rdbuf(err.rdbuf())};
    std::streambuf *oldLog{std::clog.rdbuf(err.rdbuf())};

    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "time cost: " << endTime - startTime << std::endl;
    return 0;
}

template <typename T>
Matrix<T>::Matrix(size_t width, size_t height)
{
}

template <typename T>
Matrix<T>::~Matrix()
{
}

template <typename T>
void Matrix<T>::cleanup()
{
}
