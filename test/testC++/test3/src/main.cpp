#include "header.h"

auto maximumWealth(const auto& accounts)->int{
    return std::ranges::max(accounts
        |std::views::transform([](const auto& account){
            return std::reduce(account.begin(),account.end());
        }));
}

int main(int argc, char** argv) {
    
}