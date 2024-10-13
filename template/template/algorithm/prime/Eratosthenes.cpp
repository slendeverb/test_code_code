#include <bitset>
#include <vector>

const int N{};

std::vector<int> prime;
std::bitset<N> is_prime;

void Eratosthenes(int n) {
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                // for(int j=i;j<=N/i+1;j++) 枚举倍数,避免溢出
                // is_prime[(size_t)j*i]=false;
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime.push_back(i);
        }
    }
}