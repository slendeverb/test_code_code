#include "header.h"

auto random_string(size_t length) -> std::string {
    auto randchar = []() -> char
    {
        const char charset[] =
        // "0123456789"
        // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

auto simple(std::string& input) -> std::optional<size_t> {
    auto idx = 0;
    while (idx <= input.size() - 14) {
        auto state = 0;
        auto flag=false;
        for (auto pos = idx + 13; pos >= idx; pos--) {
            auto iter = [&state](const auto& byte) mutable -> bool {
                auto bit_idx = byte % 32;
                auto ret = (state & (1 << bit_idx)) != 0;
                state |= (1 << bit_idx);
                return ret;
            };
            if (iter(input[pos])) {
                idx += (pos - idx + 1);
                flag=true;
            }
        }
        if(flag==false){
            return idx;
        }
    }
    return std::nullopt;
}

int main(int argc, char** argv) {
    srand(time(0));
    auto start = std::chrono::steady_clock::now();
    auto input = random_string(1'0000'0000);
    auto result_pos = simple(input).value_or(input.size());
    auto result = input.substr(result_pos, 14);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration<double, std::milli>(end - start);
    std::println("string length: {}",input.size());
    std::println("answer string: {}, time cost: {}", result, elapsed_time);
}