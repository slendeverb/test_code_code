#include <bitset>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int m = floor.size();
        std::vector f(numCarpets + 1, std::vector<int>(m));
        f[0][0] = floor[0] - '0';
        for (int j = 1; j < m; j++) {
            f[0][j] = f[0][j - 1] + (floor[j] - '0');
        }
        for (int i = 1; i <= numCarpets; i++) {
            for (int j = carpetLen * i; j < m; j++) {
                f[i][j] = std::min(f[i][j - 1] + (floor[j] - '0'), f[i - 1][j - carpetLen]);
            }
        }
        return f[numCarpets][m - 1];
    }
};

int main() {
    std::cout << Solution{}.minimumWhiteTiles("10110101", 2, 2);
}