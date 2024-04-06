#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <charconv>
#include <chrono>
#include <cmath>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cxxabi.h>
#include <deque>
#include <exception>
#include <filesystem>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <latch>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <ranges>
#include <ratio>
#include <regex>
#include <semaphore>
#include <set>
#include <source_location>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>
#include <windows.h>
//
using namespace std;

double arithmeticMean(std::span<const int> values)
{
    double sum{std::accumulate(std::cbegin(values), std::cend(values), 0.0)};
    return sum / values.size();
}

double geometricMean(std::span<const int> values)
{
    // int mult{std::accumulate(std::cbegin(values),std::cend(values),1,[](int value1,int value2){return value1*value2;})};
    int mult{std::accumulate(std::cbegin(values), std::cend(values), 1, std::multiplies<>{})};
    return pow(mult, 1.0 / values.size());
}

void solve()
{
    std::string text{"This is the haystack to search a needle in."};
    std::string toSearchFor{"needle"};
    std::boyer_moore_searcher searcher{std::cbegin(toSearchFor), std::cend(toSearchFor)};
    auto result{std::search(std::cbegin(text), std::cend(text), searcher)};
    if (result != cend(text))
    {
        cout << "Found the needle." << endl;
    }
    else
    {
        cout << "Needle not found." << endl;
    }
}

int main()
{
    std::ifstream in{"../../in.txt"};
    std::streambuf *oldIn{std::cin.rdbuf(in.rdbuf())};
    std::ofstream out{"../../out.txt"};
    std::streambuf *oldOut{std::cout.rdbuf(out.rdbuf())};
    std::ofstream err{"../../err.txt"};
    std::streambuf *oldErr{std::cerr.rdbuf(err.rdbuf())};
    std::streambuf *oldLog{std::clog.rdbuf(err.rdbuf())};

    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "\ntime cost: " << endTime - startTime << std::endl;

    in.close();
    std::cin.rdbuf(oldIn);
    out.close();
    std::cout.rdbuf(oldOut);
    err.close();
    std::cerr.rdbuf(oldErr);
    std::clog.rdbuf(oldLog);
    return 0;
}
