#include <algorithm>
#include <queue>
#include <cxxabi.h>
#include <iterator>
#include <deque>
#include <forward_list>
#include <list>
#include <bitset>
#include <version>
#include <ranges>
#include <cstdint>
#include <type_traits>
#include <future>
#include <barrier>
#include <latch>
#include <semaphore>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <any>
#include <variant>
#include <tuple>
#include <random>
#include <valarray>
#include <ratio>
#include <numeric>
#include <regex>
#include <array>
#include <bit>
#include <charconv>
#include <chrono>
#include <cmath>
#include <compare>
#include <complex>
#include <concepts>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numbers>
#include <optional>
#include <set>
#include <source_location>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <windows.h>
//
using namespace std;



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
