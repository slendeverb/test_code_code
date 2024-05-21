#include <chrono>
#include <format>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <string_view>

std::optional<size_t> find_different_letters(std::string_view s, auto& length)
{
    size_t idx = 0;
    for (idx = 0; s.size() - idx >= static_cast<size_t>(length);) {
        unsigned int state = 0;
        auto slice { s.substr(idx, length) };
        bool ret = 0;
        auto rposition { [&ret, &state](auto& slice) -> decltype(auto) {
            auto found {
                [&ret, &state](auto& x) -> decltype(auto) {
                    unsigned int bit_idx = x % 32;
                    bool ret = (state & (1 << bit_idx)) != 0;
                    state |= (1 << bit_idx);
                    return ret;
                }
            };
            for (int pos = slice.size() - 1; pos >= 0; pos--) {
                if (found(slice[pos])) {
                    return std::optional<size_t>(pos + 1);
                }
            }
            return std::optional<size_t>(std::nullopt);
        } };
        if (auto pos = rposition(slice).value_or(false)) {
            idx += pos;
        } else {
            return idx;
        }
    }
    return std::nullopt;
}

std::string get_random_string(const size_t length)
{
    std::random_device rd;
    std::default_random_engine rand { rd() };
    std::string ret;
    char c;
    for (size_t idx = 0; idx < length; idx++) {
        c = 'a' + rand() % 26;
        ret.push_back(c);
    }
    return ret;
}

void solve()
{
    auto start { std::chrono::system_clock::now() };
    const int length = 14;
    std::string s { get_random_string(100000000) };
    auto result_pos { find_different_letters(s, length).value_or(s.size()) };
    auto end { std::chrono::system_clock::now() };
    auto duration { std::chrono::duration_cast<std::chrono::nanoseconds>(end - start) };
    auto time_cost { duration.count() };
    std::cout << std::format("answer string: {}, time cost: {}\n", s.substr(result_pos, length), time_cost);
}

int main()
{
    solve();
    return 0;
}