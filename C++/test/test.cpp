#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<long long> find_latest_time(int n, vector<long long> &a, int q, vector<int> &queries)
{
    vector<long long> left_time(n + 1, 0);
    vector<long long> right_time(n + 1, 0);

    for (int i = 0; i < n; i++)
    {
        left_time[i + 1] = left_time[i] + a[i];
        right_time[i + 1] = right_time[i] + a[n - i - 1];
    }

    vector<long long> results;
    for (int x : queries)
    {
        int left = 0;
        int right = n - x + 1;
        long long latest_time = LLONG_MAX;

        while (left <= right)
        {
            int mid = (left + right) / 2;
            long long alice_time = left_time[mid] - mid;
            long long bob_time = right_time[n - x - mid] - (n - x - mid);

            if (alice_time <= bob_time)
            {
                latest_time = min(latest_time, bob_time);
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        results.push_back(latest_time);
    }

    return results;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        int q;
        cin >> q;
        vector<int> queries(q);
        for (int i = 0; i < q; i++)
        {
            cin >> queries[i];
        }

        vector<long long> results = find_latest_time(n, a, q, queries);
        for (long long result : results)
        {
            cout << result << endl;
        }
    }

    return 0;
}
