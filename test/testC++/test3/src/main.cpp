#include <header.h>

auto algo(const auto& v, auto&& s, auto&& t, auto& cnt) -> decltype(auto) {
    cnt++;
    if (t - s == 0) {
        return v[t];
    } else if (t - s == 1) {
        return std::max(v[s], v[t]);
    }
    auto mid = ((t - s) >> 1) + s;
    auto l = algo(v, s, mid, cnt);
    auto r = algo(v, mid + 1, t, cnt);
    return std::max(l, r);
}

auto solve() -> void {
    int n = 1 << 4;
    std::vector<int> v(n);
    std::iota(std::begin(v), std::end(v), 1);
    auto cnt = 0;
    auto ret{algo(v, 0, std::size(v) - 1, cnt)};
    std::print("{} {}", ret, cnt);
}

auto main() -> int {
    solve();
}