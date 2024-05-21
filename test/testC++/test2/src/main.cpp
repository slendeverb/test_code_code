#include <bitset>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

decltype(auto) simple(std::string_view s)
{
    size_t idx = 0;
    const int length = 14;
    for (size_t i = 0; i < s.size(); i++) {
        __int32 state = 0;
        auto slice { s.substr(i, length) };
        bool ret = 0;
        size_t pos = 0;
        for (pos = 0; pos < slice.size(); pos++) {
            auto x = slice[pos];
            auto bit_idx = x % 32;
            ret = (state & (1 << bit_idx)) != 0;
            state |= (1 << bit_idx);
        }
        if (ret) {
            idx += pos + 1;
        } else {
            return std::optional<size_t>(idx);
        }
    }
    return std::optional<size_t>(std::nullopt);
}

void solve()
{
    std::string s { "qwertyuiopasdfghjklzxcvbnm" };
    auto result_pos { simple(s).value_or(std::string::npos) };
    const int length = 14;
    std::cout << s.substr(result_pos, length) << std::endl;
}

int main()
{
    solve();
    return 0;
}