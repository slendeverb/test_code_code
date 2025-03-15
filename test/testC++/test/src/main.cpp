#include <cxxabi.h>
#include <windows.h>
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
#include <deque>
#include <exception>
#include <execution>
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
//
using namespace std;



void solve() {
    
}

int main() {
    // std::ifstream in{"../../in.txt"};
    // std::streambuf* oldIn{std::cin.rdbuf(in.rdbuf())};
    // std::ofstream out{"../../out.txt"};
    // std::streambuf* oldOut{std::cout.rdbuf(out.rdbuf())};
    // std::ofstream err{"../../err.txt"};
    // std::streambuf* oldErr{std::cerr.rdbuf(err.rdbuf())};
    // std::streambuf* oldLog{std::clog.rdbuf(err.rdbuf())};

    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "\ntime cost: " << endTime - startTime << std::endl;

    // in.close();
    // std::cin.rdbuf(oldIn);
    // out.close();
    // std::cout.rdbuf(oldOut);
    // err.close();
    // std::cerr.rdbuf(oldErr);
    // std::clog.rdbuf(oldLog);
    return 0;
}
