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

double arithmeticMean(std::span<const int> values) {
    double sum{std::accumulate(std::cbegin(values), std::cend(values), 0.0)};
    return sum / values.size();
}

double geometricMean(std::span<const int> values) {
    // int mult{std::accumulate(std::cbegin(values),std::cend(values),1,[](int
    // value1,int value2){return value1*value2;})};
    int mult{std::accumulate(std::cbegin(values), std::cend(values), 1,
                             std::multiplies<>{})};
    return pow(mult, 1.0 / values.size());
}

template <typename Container>
void populateContainer(Container& cont) {
    while (true) {
        cout << "Enter a number (0 to quit): \n";
        int value;
        cin >> value;
        if (value == 0) {
            break;
        }
        cont.push_back(value);
    }
}

class MyClass {
   public:
    MyClass() = default;
    MyClass(const MyClass& src) = default;
    MyClass(string str) : m_str{move(str)} {}
    virtual ~MyClass() = default;
    // Move assignment operator
    MyClass& operator=(MyClass&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        m_str = move(rhs.m_str);
        cout << format("Move operator= (m_str={})", m_str) << endl;
        return *this;
    }
    void setString(string str) { m_str = move(str); }
    const string& getString() const { return m_str; }

   private:
    string m_str;
};

void removeEmptyStrings(std::vector<std::string>& strings) {
    std::erase_if(strings, [](const std::string& str) { return str.empty(); });
}

void removeEmptyStringsWithoutAlgorithms(std::vector<std::string>& strings) {
    for (auto it{std::begin(strings)}; it != std::end(strings);) {
        if (it->empty()) {
            it = strings.erase(it);
        } else {
            ++it;
        }
    }
}

void removeEmptyStringsWithRemoveEraseIdiom(std::vector<std::string>& strings) {
    auto itToBeErased{
        std::remove_if(std::begin(strings), std::end(strings),
                       [](const std::string& str) { return str.empty(); })};
    strings.erase(itToBeErased, std::end(strings));
}

void printContainer(const auto& container) {
    for (auto& x : container) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

class SumAndProduct {
   public:
    void operator()(int value) {
        m_sum += value;
        m_product *= value;
    }
    int getSum() const { return m_sum; }
    int getProduct() const { return m_product; }

   private:
    int m_sum{0};
    int m_product{1};
};

void solve() {
    vector<int> values;
    populateContainer(values);
    // Sort the container
    sort(begin(values), end(values));
    cout << "Sorted vector: ";
    for (const auto& i : values) {
        cout << i << " ";
    }
    cout << endl;
    while (true) {
        int number;
        cout << "Enter a number to insert (0 to quit): ";
        cin >> number;
        if (number == 0) {
            break;
        }
        auto iter{lower_bound(begin(values), end(values), number)};
        values.insert(iter, number);
        cout << "New vector: ";
        for (const auto& i : values) {
            cout << i << " ";
        }
        cout << endl;
    }
}

int main() {
    std::ifstream in{"../../in.txt"};
    std::streambuf* oldIn{std::cin.rdbuf(in.rdbuf())};
    std::ofstream out{"../../out.txt"};
    std::streambuf* oldOut{std::cout.rdbuf(out.rdbuf())};
    std::ofstream err{"../../err.txt"};
    std::streambuf* oldErr{std::cerr.rdbuf(err.rdbuf())};
    std::streambuf* oldLog{std::clog.rdbuf(err.rdbuf())};

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
