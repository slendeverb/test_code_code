#include <iostream>
using namespace std;

int main()
{
    int A, B, M;
    cin >> A >> B >> M;
    int *a = new int[A + 1];
    int min_a = 2e5 + 10;
    for (int i = 1; i <= A; i++)
    {
        cin >> a[i];
        min_a = min(min_a, a[i]);
    }
    int *b = new int[B + 1];
    int min_b = 2e5 + 10;
    for (int i = 1; i <= B; i++)
    {
        cin >> b[i];
        min_b = min(min_b, b[i]);
    }
    int ans = min_a + min_b;
    for (int i = 0; i < M; i++)
    {
        int x = 0, y = 0, c = 0;
        cin >> x >> y >> c;
        ans = min(ans, a[x] + b[y] - c);
    }
    cout << ans << "\n";
    return 0;
}