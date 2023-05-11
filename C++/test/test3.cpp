#include <iostream>
#include <string>
using namespace std;

// 快速幂算法
int fast_pow(int base, int power, int mod) {
    int result = 1;
    base %= mod;
    while (power) {
        if (power & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        power >>= 1;
    }
    return result;
}

int main() {
    int a;
    string b;
    cin >> a >> b;

    int power = 0;
    for (char digit : b) {
        power = (power * 10 + (digit - '0')) % (1337 * 1337); // 不使用费马小定理，直接计算 b
    }

    cout << fast_pow(a, power, 1337) << endl;
    return 0;
}
