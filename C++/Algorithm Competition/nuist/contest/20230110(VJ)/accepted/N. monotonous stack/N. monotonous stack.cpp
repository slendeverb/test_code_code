#include <iostream>
#include <stack>
#include <utility>
using namespace std;

const int N = 3e6 + 10;
int n, a[N], ans[N];
stack<pair<int, int>> st;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = n; i >= 1; i--)
    {
        while (!st.empty() && a[i] >= st.top().first)
        {
            st.pop();
        }
        if (!st.empty())
        {
            ans[i] = st.top().second;
        }
        st.push({a[i], i});
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}