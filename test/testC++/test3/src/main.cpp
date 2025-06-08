#include "header.h"
using namespace std;

int main() {
    indicators::ProgressBar bar{
        indicators::option::BarWidth{100},
        indicators::option::Start{"["},
        indicators::option::Fill{"="},
        indicators::option::Lead{">"},
        indicators::option::Remainder{" "},
        indicators::option::End{"]"},
        indicators::option::ShowPercentage{true},
        indicators::option::ShowElapsedTime{true},
        indicators::option::ShowRemainingTime{true},
        indicators::option::ForegroundColor{indicators::Color::cyan}
    };

    size_t total=100;
    for(size_t i=0;i<=total;i++){
        bar.set_progress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds{50});
    }
    std::cout<<"完成!\n";
}