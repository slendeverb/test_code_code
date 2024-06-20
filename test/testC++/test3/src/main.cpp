#include <header.h>

std::optional<size_t> find_different_letters(std::string_view s, auto& length) {
    for (size_t idx = 0; s.size() - idx >= static_cast<size_t>(length);) {
        unsigned int state = 0;
        auto slice{s.substr(idx, length)};
        auto rposition{[&state, &slice]() -> decltype(auto) {
            auto found{[&state](auto& x) -> decltype(auto) {
                const unsigned int bit_idx = x % 32;
                bool ret = (state & (1 << bit_idx)) != 0;
                state |= (1 << bit_idx);
                return ret;
            }};
            for (int pos = static_cast<int>(std::size(slice)) - 1; pos >= 0; --pos) {
                if (found(slice[pos])) {
                    return std::optional<size_t>(pos + 1);
                }
            }
            return std::optional<size_t>(std::nullopt);
        }};
        if (auto pos = rposition().value_or(false)) {
            idx += pos;
        } else {
            return std::optional<size_t>{idx};
        }
    }
    return std::optional<size_t>{std::nullopt};
}

std::string get_random_string(const size_t length) {
    std::random_device rd;
    std::default_random_engine rand{rd()};
    std::string ret;
    for (size_t idx = 0; idx < length; idx++) {
        char c = 'a' + rand() % 26;
        ret.push_back(c);
    }
    return ret;
}

void solve() {
    const auto start{std::chrono::system_clock::now()};
    constexpr int length = 14;
    const std::string s{get_random_string(100000000)};
    const auto result_pos{find_different_letters(s, length).value_or(s.size())};
    const auto end{std::chrono::system_clock::now()};
    const auto duration{std::chrono::duration_cast<std::chrono::seconds>(end - start)};
    auto time_cost{duration.count()};
    std::println("answer string: {}, time cost: {}", s.substr(result_pos, length), time_cost);
}

int main() {
    solve();
}