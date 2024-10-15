// #include "header.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int maxHeightOfTriangle(int red, int blue) {
        int ans = 0;
        int layer = 1;
        auto helper = [&layer, &ans](int x, int y) mutable {
            while (true) {
                if (layer & 1) {
                    x -= layer;
                    if (x < 0) {
                        ans = std::max(ans, layer - 1);
                        break;
                    }
                } else {
                    y -= layer;
                    if (y < 0) {
                        ans = std::max(ans, layer - 1);
                        break;
                    }
                }
                layer++;
            }
        };
        helper(red, blue);

        layer = 1;
        helper(blue, red);
        return ans;
    }
};

int main(int argc, char** argv) {
    auto start = std::chrono::system_clock::now();
    int red{10};
    int blue{20};
    std::cout << std::format("{}\n", Solution{}.maxHeightOfTriangle(red, blue));
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::format("{}\n", duration);
}