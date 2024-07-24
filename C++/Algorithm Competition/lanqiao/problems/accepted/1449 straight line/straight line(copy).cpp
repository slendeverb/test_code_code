// 解法一
// 两点式直线方程：
// (y1-y2) * x +(x2-x1) * y +( x1 * y2 - x2 * y1)=0

// 思路：先存储所有的坐标
// ，遍历所有的坐标组获得直线Ax+By+C=0的A,B,C并使用gcd约分最后再利用set去重

#include <cmath>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> PII;
typedef pair<PII, int> PIII;
set<PIII> s;
vector<PII> vec;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    int x, y;
    cin >> x >> y;

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            vec.push_back({i, j});

    for (int i = 0; i < vec.size(); i++) {
        for (int j = i + 1; j < vec.size(); j++) {
            int x1 = vec[i].first, y1 = vec[i].second;
            int x2 = vec[j].first, y2 = vec[j].second;
            int A = x2 - x1, B = y1 - y2, C = x1 * y2 - x2 * y1;
            int gcdd = gcd(gcd(A, B), C);
            s.insert({{B / gcdd, A / gcdd}, C / gcdd});
        }
    }

    cout << s.size();
    return 0;
}

// 解法二
// 通过以其中一点为源点，每两点间的向量来区分直线，例如以A(x1,y1)为源点，那么与B(x2,y2)点向量就是（x1-x2,y1-y2），
// 同时向量要取gcd避免相同直线取值不同。

#include <iostream>
#include <set>
#include <vector>
#define x first
#define y second
using namespace std;
typedef pair<int, int> PII;
vector<PII> a;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int n = 20, m = 21;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            a.push_back({i, j});

    int ans = 0;
    int sz = a.size();
    vector<set<PII>> s(a.size());

    for (int i = 0; i < sz; i++) {
        for (int j = i + 1; j < sz; j++) {
            int xx = a[i].x - a[j].x;
            int yy = a[i].y - a[j].y;
            int d = gcd(xx, yy);
            PII n1 = {xx / d, yy / d};
            // 忽略与x轴或y轴平行的直线
            if (n1.x == 0 || n1.y == 0)
                continue;

            s[i].insert(n1);
            // 如果该点不存在这方向就插入该方向，
            // 同时要减去相同的直线（i点与j点重复插入相同方向）
            if (s[j].count(n1) == 0) {
                s[j].insert(n1);
                ans--;
            }
        }
    }

    for (int i = 0; i < s.size(); i++) {
        ans += s[i].size();
    }

    cout << ans + n + m;  // n 和 m 表示所有与x轴或y轴平行的直线

    return 0;
}
