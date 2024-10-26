#### 数据结构

##### DSU
```C++
#include<numeric>
struct DSU{
    vector<int>fa, sz;
    DSU(int n) : fa(n + 1),sz(n+1, 1) {iota(fa.begin(), fa.end(), 0);}
    int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
    bool same(int x,int y) {return find(x) == find(y);}
    bool merge(int x,int y){
        x = find(x),y = find(y);
        if(x == y) return false;
        if(sz[x] <  sz[y]) swap(x, y);
        sz[x] += sz[y]; fa[y] = x;
        return true;
    }
    int size(int x) {return sz[find(x)];}
};
```

##### 带权DSU
+ 强制在线
+ `1 l r x` 代表 $a_{l}-a_{r}=x$, 若矛盾则忽略
+ `2 l r` 代表回答 $a_{l}-a_{r}$, 如果推不出则忽略
  我们记向量 $vec_{x}=a_{x}-a_{f[x]}$
  当已知 $vec_{x}=a_{x}-a_{y}$ 和 $vec_{y}=a_{y}-a_{z}$ 时,
  我们求 `x` 到 `z` 的向量时, 可以通过 $vec_{x}+vec_{y}$ 来计算
  递归压缩了父节点, 得到已知信息 $vec_{par[x]}$ 为 $a_{par[x]}-a_{root}$
  那么节点 `x` 到 `root` 的关系就可以使用向量加法法则 $vec_{x}+vec_{par[x]}$ 得到
  而合并的时候, 只需要更新一组各自根节点 $root$ 的差值即可.
```C++
int find(int x){
    if(f[x] == x) return x; 
    int p = f[x]; 
    find(p);
    w[x] = w[x] + w[p];
    return f[x] = find(f[x]);
}
void solve(){
    int n,q;
    cin >> n >> q;
    for(int i = 1;i <= n;i ++) {f[i] = i; w[i] = 0;}
    int t = 0;
    for(int i = 0;i < q;i ++){
        int ty, l, r;
        cin >> ty >> l >> r;
        l = (l + t) % n + 1;
        r = (r + t) % n + 1;
        if(ty == 2){
            if(find(l) != find(r)) continue;
            cout << w[l] - w[r] << endl;
            t = abs(w[l] - w[r]);
        }else if(ty == 1){
            int x; cin >> x;
            if(find(l) == find(r)) continue;
             w[f[l]] = x - w[l] + w[r];
             f[f[l]] = f[r];
        }
    }
}
```

##### 单调队列
```C++
#define maxn 1000100
int q[maxn], a[maxn], n, k;
void getmin()
{ // 得到这个队列里的最小值，直接找到最后的就行了
    int head = 0, tail = 0;
    for (int i = 1; i < k; i++)
    {
        while (head <= tail && a[q[tail]] >= a[i]) tail--;
        q[++tail] = i;
    }
    for (int i = k; i <= n; i++)
    {
        while (head <= tail && a[q[tail]] >= a[i]) tail--;
        q[++tail] = i;
        while (q[head] <= i - k) head++;
        printf("%d ", a[q[head]]);
    }
}
void getmax()
{ // 和上面同理
    int head = 0, tail = 0;
    for (int i = 1; i < k; i++)
    {
        while (head <= tail && a[q[tail]] <= a[i]) tail--;
        q[++tail] = i;
    }
    for (int i = k; i <= n; i++)
    {
        while (head <= tail && a[q[tail]] <= a[i]) tail--;
        q[++tail] = i;
        while (q[head] <= i - k) head++;
        printf("%d ", a[q[head]]);
    }
}
```

##### 倍增
> 我们设 $to[x][i]$ 代表从起点 $x$ 跳 $2^{i}$ 步后到达的小块编号，$carrot[x][i]$ 表示从起点 $x$ 跳 $2^{i}$ 步后能拿到的胡萝卜总数。
> 则有式子 $to[x][i] = to[to[x][i-1]][i-1]$ 。即跳 $2^{i}$ 步相当于先跳 $2^{i-1}$ 步再跳 $2^{i-1}$ 步
> $carrot[x][i] = carrot[x][i - 1] + carrot[to[x][i-1]][i-1]$
```C++
const int MAXN = 1e6 + 5;
long long to[MAXN][65], carrot[MAXN][65], num[MAXN], n, m, k;
int main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> num[i];
    for (int x = 1; x <= n; x++) 
    to[x][0] = (x + k) % n + 1, carrot[x][0] = num[x];
    for (int i = 1; i <= 64; i++)
        for (int x = 1; x <= n; x++)
        {
            to[x][i] = to[to[x][i - 1]][i - 1];
            carrot[x][i] = carrot[x][i - 1] + 
            carrot[to[x][i - 1]][i - 1];
        }
    int p = 0, now = 1, ans = 0;
    while (m)
    { // 若m的二进制第p-1位为1，则答案加上去
        if (m & (1ll << p)) ans += carrot[now][p], now = to[now][p];
        m ^= (1 << p); // 第p-1位清空
        p++;
    }
    return 0;
}
```

##### 树状数组
```C++
template <typename T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int n = 0) {init(n);}
    void init(int n) {this->n = n; a.assign(n, T());}
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {a[i - 1] += v;}}
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {ans += a[i - 1];}
        return ans;
    }
    T rangeSum(int l, int r) {return sum(r) - sum(l);}
    int kth(T k) {
        int x = 0;
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i; k -= a[x - 1];
            }
        }
        return x;
    }
};
struct Info {
    int x = -1E9;
    Info &operator+=(Info b) & {x = std::max(x, b.x); return *this;}
};
```

###### 树状数组区间加和
```C++
const int N = 1e6 + 100;
template<class T>
struct BIT {
    T c[N]; int size;
    void resize(int s) {size = s;}
    T query(int x) {
        assert(x <= size);
        T res = 0;
        for (; x; x -= x & -x) {res += c[x];}
        return res;
    }
    void modify(int x, T val) {assert(x != 0); 
    for (; x <= size; x += x & -x) c[x] += val;}
};
BIT<int> c1, c2;
int n, q;
void add(int l, int r, int d) {
    c1.modify(l, d); c1.modify(r + 1, -d);
    c2.modify(l, l * d); c2.modify(r + 1, (r + 1) * (-d));
}
void solve() {
    cin >> n >> q;
    c1.resize(n); c2.resize(n);
    for (int i = 1; i <= n; i ++) {int x; cin >> x; add(i, i, x);}
    for (int i = 0; i < q; i ++) {
        int ty; cin >> ty;
        if (ty == 1) {int l, r, d; cin >> l >> r >> d; add(l, r, d);} 
        else {
            int l, r; cin >> l >> r;
            //int res = (x + 1) * c1.query(x) - c2.query(x);
            //printf("%llu\n",res);
            int res = 0ll;
            res += (r + 1ll) * c1.query(r);
            res -= 1ll * l * c1.query(l - 1);
            res -= (c2.query(r) - c2.query(l - 1));
            cout << res << endl;
        }
    }
}
```

###### 高维树状数组
```C++
int n,m;
struct BIT{
    int tree[N][N];
    void init(){
        for(int i = 0;i <= 2049;i ++)
            for(int j = 0;j <= 2049;j ++)
                tree[i][j] = 0;
    }
    int query(int x,int y){
        int res = 0;
        for(int p = x;p >= 1; p -= p & (-p))
            for(int q = y;q >= 1; q -= q & (-q))
                res += tree[p][q];
        return res;
    }
    void modify(int x,int y,int s){
        for(int p = x;p <= n;p += (p & -p))
            for(int q = y;q <= m; q += (q & -q))
                tree[p][q] += s;
    }
};
char op[5];
BIT A,Ai,Aj,Aij;
void add(int x,int y,int val)
{
   A.modify(x,y,val);
   Ai.modify(x,y,val * x);
   Aj.modify(x,y,val * y);
   Aij.modify(x,y,val * x * y);
}
int cacl(int x,int y)
{
    int res = 0;
    res += A.query(x,y) * (x * y + x + y + 1);
    res -= Ai.query(x,y) * (y + 1);
    res -= Aj.query(x,y) * (x + 1);
    res += Aij.query(x,y);
    return res;
}
void solve()
{
  scanf("X %d %d",&n,&m);
  A.init(); Ai.init();
  Aj.init(); Aij.init();
  while(scanf("%s",&op) != EOF)
  {
    int x1,y1,x2,y2;
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    if(op[0] == 'L')
    {
        int val;
        scanf("%d",&val);
        add(x1,y1 ,val);
        add(x1,y2 + 1,-val);
        add(x2+1,y1,-val);
        add(x2+1,y2+1,val);
    }
    else{
        int res = 0;
        res += cacl(x2,y2);
        res -= cacl(x1 - 1,y2);
        res -= cacl(x2,y1 - 1);
        res += cacl(x1 - 1,y1 - 1);
        printf("%d\n",res);
    }
  }
}
```

##### 二维数点
$n$ 个点 $(x_{i},y_{i})$. 回答 $q$ 个询问, 回答 $[x_{i},y_{i}] \times [x_{j},y_{j}]$ 里面有几个点.
```C++
const int N = 2e5 + 100;
vector<int> vx; vector<array<int, 4>> event;
int n,q,m,c[N],res[N];
int query(int x){ int s = 0;
    for(; x; x -= x & (-x)) {s += c[x];}
    return s;
}
void modify(int x,int s) {for(; x <= m; x += x & (-x)) {c[x] += s;}}
void solve(){
    cin >> n >> q;
    rep(i,1,n){
        int x,y; cin >> x >> y; vx.pb(x);
        event.pb({y, 0, x});
    }
    rep(i,1,q){
        int x1, x2, y1, y2; cin >> x1 >> x2 >> y1 >> y2;
        event.pb({y2, 2,x2, i});
        event.pb({y1 - 1, 2, x1 - 1, i});
        event.pb({y2, 1, x1 - 1, i});
        event.pb({y1 - 1, 1, x2, i});
    }
    sort(event.begin(), event.end());
    sort(vx.begin(), vx.end());
    vx.erase(unique(vx.begin(), vx.end()), vx.end());
    m = vx.size();
    for(auto evt : event){
        if(evt[1] == 0){
            int y = lower_bound(vx.begin(), vx.end(), evt[2]) 
            - vx.begin() + 1; // 0 base
            modify(y,1);}
        else{ int y = upper_bound(vx.begin(), vx.end(), evt[2]) 
            - vx.begin() + 1 - 1; // 0 base
            int tmp = query(y);
            if(evt[1] == 1) res[evt[3]] -= tmp;
            else res[evt[3]] += tmp;}
    }
    rep(i,1,q) cout << res[i] << endl;
}
```

##### cdq

###### cdq 二维偏序
```C++
int cdq(int A[], int n)
{
    if(n == 1) return 0;
    int mid = n/2; int i = 0; int j = mid;
    int res = cdq(A,mid) + cdq(A + mid,n - mid);
    sort(A, A + mid, greater<int>());
    sort(A + mid, A + n, greater<int>());
    for(;j < n;j ++)
    {
        while(i < mid && A[i] > A[j]) i ++;
        res += i;
    }
    return res;
}
```

###### cdq 三维偏序
```C++
const int N = 1e5 + 100;
struct node{
    int x,y,z,ans,w;
}a[N], b[N];
int n,m,idx,res[N];
bool operator != (node &a, node &b) {
    return a.x != b.x | a.y != b.y | a.z != b.z;}
bool cmpx(node &a, node &b)
{
    if(a.x != b.x) return a.x < b.x;
    if(a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}
bool cmpy(node &a, node &b)
{
    if(a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}
struct BIT{
    int c[N * 2];
    int query(int x){
        int res = 0;
        for(; x; x -= (x & -x)) res += c[x];
        return res;
    }
    void add(int x,int v) {for(; x <= m; x += (x & -x)) c[x] += v;}
}bit;
void cdq(int l,int r)
{
    if(l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid); cdq(mid + 1, r);
    sort(a + l,a + mid + 1, cmpy);
    sort(a + mid + 1,a + r + 1, cmpy);
    int i = l; int j = mid + 1;
    for(;j <= r;j ++){
        while(a[i].y <= a[j].y && i <= mid) {
           bit.add(a[i].z, a[i].w); i++;
        }
        a[j].ans += bit.query(a[j].z);
    }
    for(j = l;j < i;j ++) bit.add(a[j].z , -a[j].w);
}
void solve()
{
    cin >> n >> m;
    rep(i,1,n) cin >> b[i].x >> b[i].y >> b[i].z;
    sort(b + 1,b + 1 + n,cmpx);
    idx = 0; int cnt = 0;
    for(int i = 1;i <= n;i ++){
        cnt ++;
        if(b[i] != b[i + 1]){
            a[ ++idx ] = b[i];
            a[ idx ].w = cnt;
            cnt = 0; 
        }
    }
    cdq(1, idx);
    rep(i,1,idx) res[a[i].ans + a[i].w - 1] += a[i].w;
    rep(i,0,n - 1) cout << res[i] << endl;
}
```

##### 线段树

###### 线段树 单点修改 区间查询
单点修改，区间查询。维护区间最小值和最小值个数。
```C++
const int N = 2e5 + 100;
int n,q,a[N];
struct info {int minv, mincnt;};
info operator + (const info &l, const info &r){
    info a;
    a.minv = min(l.minv, r.minv);
    if(l.minv == r.minv){
        a.mincnt = l.mincnt + r.mincnt;
        return a;
    }
    a.mincnt = (l.minv < r.minv ? l.mincnt : r.mincnt);
    return a;
}
struct node {info val;}seg[N * 4];
// son -> fa
void update(int u){seg[u].val = seg[u << 1].val + seg[u << 1 | 1].val;}
void build(int u,int l,int r)
{
    if(l == r) seg[u].val = {a[l], 1};
    else{
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1,mid + 1, r);
        update(u);
        // 自下而上建树
    }
}
//  [u , l, r]
//  当前查询的区间编号为 u 他的管辖的位置参数为 l <= i <= r  
//  需要修改的位置编号为 pos 改为 val 单点修改
//  a[pos] -> v
//  自上而下搜索 pos 位置 自下而上 更新信息
void change(int u, int l, int r, int pos, int v)
{
    if(l == r) seg[u].val = (info){v,1};
    else{
        int mid = (l + r)>>1;
        if(pos <= mid) change(u << 1, l, mid, pos, v);
        else change(u << 1 | 1, mid + 1, r, pos, v);
        update(u);
    }
}
// [u ,l ,r] 
// [ql ,qr]  quite 参数 目标参数
// 核心 u ql qr
info query(int u,int l,int r,int ql,int qr)
{
    if(l == ql && r == qr) return seg[u].val;
    int mid = (l + r) >> 1;
    // [l , mid]  [mid + 1, r]
    if(qr <= mid) return query(u << 1, l, mid, ql, qr);
    else if(ql >= mid + 1) return query(u << 1 | 1,mid + 1, r, ql, qr);
    else{// target  [ql, mid] [mid + 1, qr]
        return query(u << 1, l, mid, ql, mid) 
        + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
    }
}
```

###### 线段树 求最大连续子段和
```C++
const int N = 2e5 + 100;
int n,q,a[N];
struct info {
    int mss, mpre, msuf, s;
    info () {}
    info(int a) : mss(a), mpre(a), msuf(a), s(a) {}
};
info operator + (const info &l, const info &r){
    info a;
    a.mss = max({l.mss, r.mss, l.msuf + r.mpre});
    a.mpre = max(l.mpre, l.s + r.mpre);
    a.msuf = max(r.msuf, r.s + l.msuf);
    a.s = l.s + r.s;
    return a;
}
struct node {info val;}seg[N * 4];
void build(int u,int l,int r)
{
    if(l == r) seg[u].val = info(a[l]);
    else{
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1,mid + 1, r);
        update(u);
        // 自下而上建树
    }
}
```

###### 线段树 区间修改 区间查询
```C++
const int N = 2e5 + 100;
int n,q,a[N];
struct info {int maxv;};
struct tag {int add;};
info operator + (const info &l, const info &r){
    info a;
    a.maxv = max(l.maxv, r.maxv);
    return a;
}
info operator + (const info &v, const tag &t)
{
    info a;
    a.maxv = v.maxv + t.add;
    return a;
}
tag operator + (const tag &t1, const tag &t2)
{
    tag a;
    a.add = t1.add + t2.add;
    return a;
}
struct node {tag t; info val;}seg[N * 4];
// son -> fa
void update(int u){seg[u].val = seg[u << 1].val + seg[u << 1 | 1].val;}
void settag(int u,tag t){
    seg[u].val = seg[u].val + t;
    seg[u].t = seg[u].t + t;
}
void pushdown(int u)
{
    if(seg[u].t.add != 0){
        settag(u << 1,seg[u].t);
        settag(u << 1 | 1,seg[u].t);
        seg[u].t.add = 0;
    }
}
void build(int u,int l,int r)
{
    if(l == r) seg[u].val = {a[l]};
    else{
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1,mid + 1, r);
        update(u);
        // 自下而上建树
    }
}
void modify(int u,int l,int r,int ql,int qr, tag t)
{
    if(l == ql && r == qr)
    {
        settag(u, t);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(u);
    // [l , mid]  [mid + 1, r]
    if(qr <= mid) modify(u << 1, l, mid, ql, qr, t);
    else if(ql >= mid + 1) modify(u << 1 | 1,mid + 1, r, ql, qr, t);
    else{
        // target  [ql, mid] [mid + 1, qr]
        modify(u << 1, l, mid, ql, mid, t);
        modify(u << 1 | 1, mid + 1, r, mid + 1, qr, t);
    }
    update(u);
}
// [u ,l ,r] 
// [ql ,qr]  quite 参数 目标参数
// 核心 u ql qr
info query(int u,int l,int r,int ql,int qr)
{
    if(l == ql && r == qr) return seg[u].val;
    int mid = (l + r) >> 1;
    // [l , mid]  [mid + 1, r]
    pushdown(u);
    if(qr <= mid) return query(u << 1, l, mid, ql, qr);
    else if(ql >= mid + 1) return query(u << 1 | 1,mid + 1, r, ql, qr);
    else{// target  [ql, mid] [mid + 1, qr]
        return query(u << 1, l, mid, ql, mid) 
        + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
    }
}
void solve()
{
    cin >> n >> q;
    for(int i = 1;i <= n;i ++) cin >> a[i];
    build(1, 1, n);
    for(int i = 0;i < q;i ++){
        int op; cin >> op;
        if(op == 1){
            int l, r, d;
            cin >> l >> r >> d;
            modify(1, 1, n, l, r, (tag){d});
        }
        else{
            int l, r; cin >> l >> r;
            auto ans = query(1, 1, n, l, r);
            cout << ans.maxv << endl;
        }
    }
}
```

###### 线段树上二分
查询 $a_{l}$ $a_{r}$ 中第一个大于等于 $d$ 的下标
```C++
const int N = 2e5 + 100;
int n,q,a[N];
struct info {int maxv;};
info operator + (const info &l, const info &r){
    info a;
    a.maxv = max(l.maxv, r.maxv);
    return a;
}
bool operator < (const info &v, const int &t) {return v.maxv < t;}
bool operator >= (const info &v, const int &t) {return v.maxv >= t;}
struct node {info val;}seg[N * 4];
// son -> fa
void update(int u){seg[u].val = seg[u << 1].val + seg[u << 1 | 1].val;}
void build(int u,int l,int r)
{
    if(l == r) seg[u].val = (info){a[l]};
    else{
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1,mid + 1, r);
        update(u);
        // 自下而上建树
    }
}
//  [u , l, r]
//  当前查询的区间编号为 u 他的管辖的位置参数为 l <= i <= r  
//  需要修改的位置编号为 pos 改为 val 单点修改
//  a[pos] -> v
//  自上而下搜索 pos 位置 自下而上 更新信息
void change(int u, int l, int r, int pos, int v)
{
    if(l == r) seg[u].val = (info){v};
    else{
        int mid = (l + r)>>1;
        if(pos <= mid) change(u << 1, l, mid, pos, v);
        else change(u << 1 | 1, mid + 1, r, pos, v);
        update(u);
    }
}
// [u ,l ,r] 
// [ql ,qr]  quite 参数 目标参数
// 核心 u ql qr
int search(int u,int l,int r,int ql,int qr,int d)
{
    if(l == ql && r == qr){
        if(seg[u].val < d) return -1;
        else
        {
            if(l == r) return l;
            int mid = (l + r) >> 1;
            if(seg[u << 1].val >= d) 
                return search(u << 1,l ,mid,ql ,mid, d);
            else return search(u << 1 | 1, mid + 1,r ,mid + 1, qr, d);
        }
    }
    int mid = (l + r) >> 1;
    // [l , mid]  [mid + 1, r]
    if(qr <= mid) return search(u << 1, l, mid, ql, qr, d);
    else if(ql >= mid + 1) 
        return search(u << 1 | 1,mid + 1, r, ql, qr, d);
    else{
        // target  [ql, mid] [mid + 1, qr]
        int pos = search(u << 1,l ,mid, ql, mid, d);
        if(pos == -1) 
            return search(u << 1 | 1,mid + 1, r,mid + 1, qr ,d);
        else return pos;
    }
}
void solve()
{
    cin >> n >> q;
    for(int i = 1;i <= n;i ++) cin >> a[i];
    build(1, 1, n);
    for(int i = 0;i < q;i ++){
        int op; cin >> op;
        if(op == 1){
            int x, d; cin >> x >> d;
            change(1, 1, n, x, d);
        }else{
            int l, r, d; cin >> l >> r >> d;
            auto ans = search(1, 1, n, l, r, d);
            cout << ans << endl;
        }
    }
}
```

###### 权值线段树
给定数集 $a_{n}$ 和 $m$ 个询问。每次询问两个数 $x_{i}$ $k_{i}$。问 $a_{n}$ 中 $a_{j}$ $xor$ $x_{i}$ 中排序第 $k_{i}$ 小的元素。
```C++
const int N = 2e5 + 100, Bit = 32;
int n,m,x,k;
struct Trie{
    int id; int root; int tr[N * 32][2]; int sz[N * 32];
    //long long val[N * 32];
    void init(){ id = 1; root = 1;
        memset(tr[0], 0,sizeof(tr)); memset(sz, 0,sizeof sz);}
    int getid() {id ++; return id;}
    void insert(long long x){
    int go = root;
    for(int i = Bit;i >= 0;i --){
        sz[go] ++;
        int u = (x >> i) & 1;
        if(tr[go][u] == 0){
            memset(tr[id], 0, sizeof(tr[id]));
            tr[go][u] = getid();  
        }
        go = tr[go][u];
    } 
    sz[go]++;}
   long long query(long long x){
       int go = root; int ans = 0;
       for(int i = Bit;i >= 0;i --){
        int u = (x >> i) & 1;
        if(sz[tr[go][u]] >= k){ go = tr[go][u];}
        else{ k -= sz[tr[go][u]];
            ans ^= 1ll << i;
            go = tr[go][u ^ 1];}} 
       return ans;}
}f;
void solve(){
    cin >> n >> m; f.init();
    for(int i = 0;i < n;i ++) {cin >> x; f.insert(x);}
    for(int i = 0;i < m;i ++) {cin >> x >> k; 
    cout << f.query(x) << endl;}
}
```

##### 基础 01trie 模版
`01Trie` 是解决区间连续异或和和最大异或和的有利工具。[HDU 4825](http://acm.hdu.edu.cn/showproblem.php?pid=4825)
给一个数集集合，给 $M$ 个询问。每个询问 $ask_{i}$，给出集合中与他异或值最大的数。
```C++
const int N = 1e5 + 100, Bit = 32; int n,m;
struct Trie{
    int id; int root; int tr[N * 32][2]; long long val[N * 32];
    void init(){
        id = 1; root = 0; memset(tr[0], 0,sizeof(tr));
    }
    void insert(long long x){
    int go = root;
    for(int i = Bit;i >= 0;i --){
        int u = (x >> i) & 1;
        if(tr[go][u] == 0){
            memset(tr[id], 0, sizeof(tr[id]));
            tr[go][u] = id;
            val[id ++] = 0;
        }
        go = tr[go][u];
    }
    val[go] = x;
   }
   long long query(long long x){
        int go = root;
        for(int i = Bit;i >= 0;i --){
            int u = (x >> i) & 1;
            if(tr[go][u ^ 1]) go = tr[go][u ^ 1];
            else go = tr[go][u];
        }
        return val[go];
   }
}f;
void solve()
{
    f.init();
    cin >> n >> m;
    for(int i = 0;i < n;i ++) {long long x; cin >> x; f.insert(x);}
    while(m --) {long long v; cin >> v; cout << f.query(v) << endl;}
}
```

##### 基础莫队
> 给一个长度为 `n` 的序列。`q` 个询问。 问区间 `(l,r)` 中选两个数，选到相同数字的概率是多少。 n,q范围到 `5e4`。
```C++
const int N = 5e4 + 100;
int c[N],n,q,ans[N],ans2[N],cnt[N],tmp;
array<int,3> que[N];
void solve()
{
   cin >> n >> q;
   for(int i = 1;i <= n;i ++) cin >> c[i];
   for(int i = 0;i < q; i ++){
    int l,r; cin >> l >> r;
    que[i] = {l,r,i};
    ans2[i] = (r - l) * (r - l + 1) / 2;
   }
   int B = 500;
   sort(que, que + q, [&](array<int,3> a, array<int,3> b){
    if(a[0]/B != b[0]/B ) return a[0]/B < b[0]/B;
    return a[1]< b[1];});
   int l = 1; int r = 0;
   auto add = [&](int x) {tmp += cnt[c[x]]; cnt[c[x]] ++;};
   auto del = [&](int x) {cnt[c[x]] --; tmp -= cnt[c[x]];};
   for(int i = 0;i < q;i ++){
    while(r < que[i][1]) r ++, add(r);
    while(l > que[i][0]) l --, add(l);
    while(r > que[i][1]) del(r), r --;
    while(l < que[i][0]) del(l), l ++;
    ans[que[i][2]] = tmp;}
   for(int i = 0;i < q;i ++) {
    int d = gcd(ans[i],ans2[i]); 
    cout << ans[i]/d << '/' << ans2[i]/d << endl;}
}
```

###### 回滚莫队
> 给定一个长度为 `n` 的序列，离线询问 `m` 个问题 每次回答区间内元素`val * cnt[val]`的最大值。 `n m` 范围都到 `1E5`
```C++
const int N = 1e5 + 100;
int n,m,len,w[N],cnt[N],ans[N];
struct Query {int id, l, r;} q[N];
vector<int> nums;
int get(int x) {return x/len;}
bool cmp(const Query& a,const Query& b){
    if(get(a.l) == get(b.l)) return a.r < b.r;
    return get(a.l) < get(b.l);
}
void add(int x,int& res){
    cnt[x] ++;
    res = max(res,cnt[x] * nums[x]);
}
void solve()
{
    cin >> n >> m;
    len = sqrt(n);
    rep(i,1,n) cin >> w[i],nums.pb(w[i]);
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    rep(i,1,n) 
    w[i] = lower_bound(nums.begin(),nums.end(),w[i]) - nums.begin();
    for(int i = 0;i < m;i ++){
        int l,r; cin >> l >> r;
        q[i] = {i, l, r};
    }
    sort(q,q + m,cmp);
    for(int x = 0;x < m; )
    {
        int y = x;
        while(y < m && get(q[y].l) == get(q[x].l)) y++;   
        // 确定左边界在同一块的询问
        int right = get(q[x].l) * len + len - 1;          
        // 确定左边界块的右端点
        while(x < y && q[x].r <= right)                   
        // 暴力处理同一块的询问
        {
            int res = 0;
            rep(k,q[x].l,q[x].r) add(w[k],res);
            ans[q[x].id] = res;
            rep(k,q[x].l,q[x].r) cnt[w[k]] --;
            x ++;
        }
        int res = 0;
        int i = right; int j = right + 1;                
        // 处理左右端点不在同一块的询问
        while(x < y)
        {
            while(i < q[x].r) add(w[++ i], res);          
            // 处理右端点所在部分
            int backup = res;                             
            // 备份只有右端点部分答案
            while(j > q[x].l) add(w[-- j],res);           
            // 处理左半部分
            ans[q[x].id] = res;                           
            // 记录答案
            while(j < right + 1) cnt[w[j ++]] --;         
            // 回溯数量
            res = backup;                                 
            // 回溯右端点答案
            x ++;
        }                                                 
        // 相当于每次只记录右端点的影响
        memset(cnt, 0,sizeof cnt);                        
        // 涉及左端点时重算
    }
    for(int i = 0;i < m;i ++) cout << ans[i] << endl;
}
```
学习参考:[大佬的资料](https://www.cnblogs.com/Parsnip/p/10969989.html#)

##### 点分治
```C++
const int N = 1e5 + 100;
int n, sz[N], maxs[N], L, ans;
vector<PII> e[N];
bool del[N];
void solves(int u, int s) {
	int ms = s + 1, root = -1;
	function<void(int, int)> dfs1 = [&](int u, int par) {
		sz[u] = 1; maxs[u] = 0;
		for (auto [v, w]: e[u]) {
			if (del[v] || v == par) continue;
			dfs1(v, u);
			sz[u] += sz[v];
			maxs[u] = max(maxs[u], sz[v]);
		}
		maxs[u] = max(maxs[u], s - sz[u]);
		if (maxs[u] < ms) ms = maxs[u], root = u;
	};
	dfs1(u, -1);
	vector<int> d1, d2;
	d1.push_back(0);
	auto calc = [&](vector<int> &d) {
		sort(d.begin(), d.end());
		int m = d.size();
		int r = m - 1;
		int ans = 0;
		for (int i = 0; i < m; i++) {
			while (r >= 0 && d[i] + d[r] > L) --r;
			if (i < r) ans += r - i;
		}
		return ans;
	};
	for (auto [v, w] : e[root]) {
		if (del[v]) continue;
		d2.clear();
        auto dfs2 = [&](int u, int par, int dep) {
			sz[u] = 1;
            d1.push_back(dep);
			d2.push_back(dep);
			for (auto [v, w] : e[u]) {
				if (del[v] || v == par) continue;
                dfs2(v, u, dep + w);
                sz[u] += sz[v];
			}
		};
		dfs2(v, root, w);
		ans -= calc(d2);
	}
	ans += calc(d1);
	del[root] = true;
	for (auto [v, w] : e[root]) {if (!del[v]) solves(v, sz[v]);}
}
void solve()
{
    cin >> n;
    for(int i = 1;i < n;i ++){
        int u,v,w; cin >> u >> v >> w;
        e[u].pb(make_pair(v,w));
        e[v].pb(make_pair(u,w));
    }
    cin >> L;
    solves(1, n);
    cout << ans << endl;
}
```

##### ST表
```C++
#include <bits/stdc++.h>
using namespace std;
const int logn = 21, maxn = 2000001;
int f[maxn][logn + 1], Logn[maxn + 1];
int read() {  // 快读
  char c = getchar();
  int x = 0, f = 1;
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return x * f;
}
void pre() {  // 准备工作，初始化
  Logn[1] = 0; Logn[2] = 1;
  for (int i = 3; i < maxn; i++) {Logn[i] = Logn[i / 2] + 1;}
}
int main() {
  int n = read(), m = read();
  for (int i = 1; i <= n; i++) f[i][0] = read();
  pre();
  for (int j = 1; j <= logn; j++)
    for (int i = 1; i + (1 << j) - 1 <= n; i++)
      f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);  
      // ST表具体实现
  for (int i = 1; i <= m; i++) {
    int x = read(), y = read();
    int s = Logn[y - x + 1];
    printf("%d\n", max(f[x][s], f[y - (1 << s) + 1][s]));
  }
  return 0;
}
```

#### 图论

##### 链式前向星
```C++
// 链式前向星的存储结构：
// 以静态一维结构体数组存储所有边，结构体内保存边的终点v，
// 边权w以及与起点相关的链信息next
// 所有边在一维结构体数组edge中是无序排列的，tot是边的总数
// head数组记录了每个节点的链头信息
const int MAXN = 10000;
struct Edge {int v, w, next;} edge[MAXN * MAXN];
int tot,head[MAXN];
// 插入一条起点为u，终点为v，权值为w的边。
// 将当前edge数组下一个没有使用的（下标为tot的）元素的v和w进行赋值
// 对于起点u，首先让当前元素的next指针向前指向前一个代表起点为u的表头元素
//（其下标存在head[u]中），
// 然后将当前的下标tot设置为起点为u的表头位置head[u]=tot，最后令tot加1，
// 完成操作等待接收下一输入
void AddEdge(int u, int v, int w)
{
    // 建边
    edge[tot].v = v;
    edge[tot].w = w;
    // 连边
    edge[tot].next = head[u];
    head[u] = tot++;
}
// “前向”的名字由来是因为插入过程中类似于链表的表头插入，
// 因此如果按照插入顺序来看，表头是在后端而不是前端，
// 查找的时候可以想象成从后往前查找，故称“前向”
// 从下标为head[u]的edge数组元素开始，不断通过next前向查找，直到next为空
// 适合遍历某一特定起点的所有边，不适合快速获得特定边的信息
int main()
{
    int u; cin >> u;
    for (int i = head[u]; ~i; i = edge[i].next) {
        cout << edge[i].v << " " << edge[i].w << "\n";}
}
```

##### 最小生成树

###### Kruskal
```C++
const int N = 5e3 + 10;
int n, m;
struct Edge{
    int u, v, w;
    bool operator<(const Edge &edge) const { return w < edge.w; }
} e[N];
struct Ufs
{
    int root[N], num[N];
    void init(){for(int i = 1; i <= n; ++i) {root[i] = i;num[i] = 1;}}
    int find(int x)
    {
        if (root[x] != x) return root[x] = find(root[x]);
        return root[x];
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (num[x] < num[y]) swap(x, y);
        root[y] = x;
        num[x] += num[y];
    }
} ufs;
long long Kruskal()
{
    sort(e + 1, e + 1 + m);
    ufs.init();
    long long ret = 0, cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        if (ufs.find(e[i].u) == ufs.find(e[i].v)) {continue;}
        ufs.merge(e[i].u, e[i].v);
        ret += e[i].w;
        if (++cnt == n - 1) {return ret;}
    }
    return -1;
}
```

###### Prim
```C++
const int N = 1010;
int n, m, adj[N][N], dis[N];
bool vis[N];
int Prim()
{
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        int u = -1;
        for (int j = 1; j <= n; ++j) 
        if (!vis[j] && (u == -1 || dis[j] < dis[u])) u = j;
        res += dis[u];
        vis[u] = 1;
        for (int j = 1; j <= n; ++j) 
        if (!vis[j]) dis[j] = min(dis[j], adj[u][j]);
    }
    return res;
}
```

##### 最短路

###### Dijkstra
```C++
const int maxn = 1010;
struct edge {int v, w;};
struct node{
    int dis, u;
    bool operator>(const node &a) const { return dis > a.dis; }
};
vector<edge> e[maxn];
int dis[maxn], vis[maxn];
priority_queue<node, vector<node>, greater<node>> q;
void dijkstra(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty())
    {
        int u = q.top().u;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto ed : e[u]){
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
}
```

###### Bellman-Ford
```C++
const int maxn = 1010, inf = 0x3f3f3f3f;
struct edge {int v, w;};
vector<edge> e[maxn];
int dis[maxn];
bool bellmanford(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    bool flag; // 判断一轮循环过程中是否发生松弛操作
    for (int i = 1; i <= n; i++)
    {
        flag = false;
        for (int u = 1; u <= n; u++)
        {
            if (dis[u] == inf) continue;
            // 无穷大与常数加减仍然为无穷大
            // 因此最短路长度为 inf 的点引出的边不可能发生松弛操作
            for (auto ed : e[u]){
                int v = ed.v, w = ed.w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w; flag = true;}
            }
        }
        // 没有可以松弛的边时就停止算法
        if (!flag) break;
    }
    // 第 n 轮循环仍然可以松弛时说明 s 点可以抵达一个负环
    return flag;
}
```

###### SPFA
```C++
const int maxn = 1010;
struct edge {int v, w;};
vector<edge> e[maxn];
int dis[maxn], cnt[maxn], vis[maxn];
queue<int> q;
bool spfa(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (auto ed : e[u])
        {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1; // 记录最短路经过的边数
                if (cnt[v] >= n) return true;
                // 在不经过负环的情况下，最短路至多经过 n - 1 条边
                // 因此如果经过了多于 n 条边，一定说明经过了负环
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
    return false;
}
```

###### Floyd
```C++
const int maxn = 1010;
int n,dis[maxn][maxn];
void Floyd()
{
    for (int i = 1; i <= n; ++i)         // 中转点
        for (int u = 1; u <= n; ++u)     // 起点
            for (int v = 1; v <= n; ++v) // 终点
                dis[u][v] = min(dis[u][v], dis[u][i] + dis[i][v]);
}
```

##### 拓补排序

###### Kahn
```C++
const int N = 1010;
int n,ind[N];
vector<int> G[N],ans;
bool Kahn()
{
    queue<int> q;
    for (int i = 1; i <= n; ++i) if (ind[i] == 0) q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ans.push_back(u);
        for (int v : G[u]) if (--ind[v] == 0) q.push(v);
    }
    return ans.size() == n;
}
```

##### LCA最近公共祖先

###### 倍增求LCA
```C++
const int N=5e5+5;
struct Edge {int to, next;}edge[N<<1];
std::vector<int> v[N], w[N];
int fa[N][31], cost[N][31], dep[N], n, m, a, b, c;
// dfs，用来为 lca 算法做准备。接受两个参数：dfs 起始节点和它的父亲节点。
void dfs(int root, int fno) {
  // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
  fa[root][0] = fno;
  dep[root] = dep[fa[root][0]] + 1;
  // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的
  // 第 2^(i-1) 的祖先节点。
  for (int i = 1; i < 31; ++i) {
    fa[root][i] = fa[fa[root][i - 1]][i - 1];
    cost[root][i] = cost[fa[root][i - 1]][i - 1] + cost[root][i - 1];
  }
  // 遍历子节点来进行 dfs。
  int sz = v[root].size();
  for (int i = 0; i < sz; ++i) {
    if (v[root][i] == fno) continue;
    cost[v[root][i]][0] = w[root][i];
    dfs(v[root][i], root);
  }
}
// lca。用倍增算法算取 x 和 y 的 lca 节点。
int lca(int x, int y) {
  // 令 y 比 x 深。
  if (dep[x] > dep[y]) swap(x, y);
  // 令 y 和 x 在一个深度。
  int tmp = dep[y] - dep[x], ans = 0;
  for (int j = 0; tmp; ++j, tmp >>= 1) 
  if (tmp & 1) ans += cost[y][j], y = fa[y][j];
  // 如果这个时候 y = x，那么 x，y 就都是它们自己的祖先。
  if (y == x) return ans; // return y;
  // 不然的话，找到第一个不是它们祖先的两个点。
  for (int j = 30; j >= 0 && y != x; --j) {
    if (fa[x][j] != fa[y][j]) {
      ans += cost[x][j] + cost[y][j];
      x = fa[x][j]; y = fa[y][j];
    }
  }
  // 返回结果。
  ans += cost[x][0] + cost[y][0];
  return ans; // return fa[y][0];
}
int main() {
  // 初始化表示祖先的数组 fa，代价 cost 和深度 dep。
  memset(fa, 0, sizeof(fa));
  memset(cost, 0, sizeof(cost));
  memset(dep, 0, sizeof(dep));
  // 读入树：节点数一共有 n 个。
  scanf("%d %d", &n, &m);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d %d", &a, &b, &c);
    v[a].push_back(b); v[b].push_back(a);
    w[a].push_back(c); w[b].push_back(c);
  }
  dfs(1, 0); // 为了计算 lca 而使用 dfs。
  // 查询 m 次，每一次查找两个节点的 lca 点。
  for (int i = 0; i < m; ++i) {
    scanf("%d %d", &a, &b);
    printf("%d\n", lca(a, b));
  }
  return 0;
}
```

##### Tarjan
给一个 n 个点 m 条边的图，输出所有的强连通分量。
```C++
#define pb push_back
int n,m,idx,cnt,dfn[N],low[N],ins[N],bel[N];
const int N = 1e5 + 100;
vector<int> e[N];
stack<int> stk;
vector<vector<int>> scc;
void dfs(int u)
{
    dfn[u] = low[u] = ++idx;
    ins[u] = true; stk.push(u);
    for(auto v : e[u])
    {
        if(!dfn[v]) dfs(v);
        if(ins[v]) low[u] = min(low[u],low[v]);
    }
    if(dfn[u] == low[u])
    {
        vector<int> c; ++ cnt;
        while(true){
            int v = stk.top();
            c.pb(v);ins[v] = false;
            bel[v] = cnt;
            stk.pop();
            if(u == v) break;
        }
        sort(c.begin(),c.end());
        scc.pb(c);
    }
}
void solve()
{ 
   cin >> n >> m;
   for(int i = 0;i < m;i ++) {int u,v; cin >> u >> v; e[u].pb(v);}
   for(int i = 1;i <= n;i ++) if(!dfn[i]) dfs(i);
   sort(scc.begin(),scc.end());
   for(auto c : scc) {for(auto u : c) cout << u << ' '; cout << endl;}
}
```

##### 匈牙利算法
```C++
#define pb push_back
#define rep(i, x, y) for(int i=x;i<=y;i++)
int n,m,k;
vector<int> g[N];
map<int,int> mp;
bool st[N];  // vailable of second set
bool find(int x){
    for(int y : g[x]){
        if(st[y] ^ 1)
        {
            st[y] = true;
            if(mp[y] == 0 || find(mp[y])){ 
                mp[y] = x;
                return true;
            }
        }
    }
    return false;
}
void solve()
{
    cin >> n >> m >> k;
    for(int i = 0;i < k;i ++) {int u, v; cin >> u >> v; g[u].pb(v);}
    int res = 0;
    rep(i,1,n) {memset(st,false,sizeof st); if(find(i)) res++;}
    cout << res << endl;
}
```

##### DSU 判断二分图
```C++
struct DSU {
    vector<int> p;
    DSU(int n) {
        p.resize(n + 1, 0); 
        for (int i = 1; i <= n; i++) p[i] = i;}
    int find(int x) {return x == p[x] ? x : p[x] = find(p[x]);}
    void merge(int x, int y) {
        x = find(x); y = find(y);
        if (x != y) p[x] = y;
    }
};
int main() {
    int n, m; cin >> n >> m;
    DSU d(n * 2);
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        d.merge(u, n + v); d.merge(u + n, v);
    }
    bool f = true;
    for (int i = 1; i <= n; i++) {
        if (d.find(i) == d.find(i + n)) {f = false;}}
    puts(f ? "Yes" : "No");
    return 0;
}
```

#### DP

##### bitset优化dp
题目在这里[qwq!](https://qoj.ac/problem/2325)
我们使用 `0 1` 背包优化 `dp`
```C++
const int N = 2e5 + 100;
int n,w;
bitset<N> f;
void solve()
{ 
   cin >> n >> w;
   f[0] = 1;
   for(int i = 0;i < n;i ++) {int x; cin >> x; f |= (f << x);}
   for(int i = w;i >= 0;i --) if(f[i]) {cout << i << endl; return;}
}
```

##### 换根DP
```C++
const int N = 1e6 + 100;
vector<int>g[N];
int d[N],sz[N],f[N],n,res = 0;
void dfs1(int u,int fa)
{
  for(int to : g[u])
  {
     if(to == fa) continue;
     dfs1(to,u);
     sz[u] += sz[to];
  }
  sz[u] += 1; d[u] = d[fa] + 1;
}
void dfs2(int u,int fa)
{
  for(int x : g[u])
  {
     if(x == fa) continue;
     f[x] = f[u] - sz[x] + (n - sz[x]);
     dfs2(x,u);
  }
}
void solve()
{
    cin >> n; 
    for(int i = 1;i < n;i ++)
    {
      int u,v; cin >> u >> v;
      g[u].pb(v); g[v].pb(u);
    }   
    dfs1(1,0);
    for(int i = 1;i <= n;i ++) f[1] += d[i];
    dfs2(1,0);
    int res = 0; int resid = 0;
    for(int i = 1;i <= n;i ++) if(f[i] > res) res = f[i] ,resid = i;
    cout << resid << endl;
}
```

#### 数学

##### GCD
```C++
int gcd(int a,int b) {return b?gcd(b,a%b):a;}
```

##### 判断素数
```C++
int isprime(int num)
{
    if (num == 1) return 0;
    if (num == 2 || num == 3) return 1;
    if (num % 6 != 1 && num % 6 != 5) return 0;
    for (int i = 5; i <= floor(sqrt((double)num)); i += 6) 
    if ((num % i) == 0 || (num % (i + 2)) == 0) return 0;
    return 1;
}
```

##### 快速幂
```C++
int qmi(int a, int k, int p)
{
    a %= p; int res = 1;
    while (k){
        if (k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}
```

##### 排列组合
```C++
long long inv(long long a) {return quick_pow(a, MOD - 2);}
vector<long long> fact(N), invFact(N);
void init()
{
    fact[0] = 1;
    for (int i = 1; i < N; ++i) 
        fact[i] = fact[i - 1] * i % MOD;
    invFact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; --i) 
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}
long long C(int n, int k)
{
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}
long long A(int n, int k)
{
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[n - k] % MOD;
}
```

##### 矩阵快速幂
```C++
const int N = 105;
const int mod = 1e9 + 7;
struct Matrix
{
    int x,y; int a[N][N];
    // matrix(){ memset(a,0,sizeof(a) ); }
    void read(int n,int m)
    {   
        x = n; y = m;
        for(int i = 1;i <= x;i ++)
            for(int j = 1;j <= y;j ++) cin >> a[i][j];
    }
    void init()
    {
        for(int i = 1;i <= x;i ++)
            for(int j = 1;j <= y;j ++) a[i][j] = 0;
    }
    void resize(int n,int m) {x = n; y = m;}
    void init_one()
    {
        rep(i,1,x) rep(j,1,y) a[i][j] = 0;
        for(int i = 1;i <= min(x,y);i ++) a[i][i] = 1;
    }
    void print()
    {
        for(int i = 1;i <= x;i ++)
            for(int j = 1;j <= y;j ++)
                cout << a[i][j] << " \n"[j == y];
    }
}model,res;
// p * q
// 0 . . . y 
// .
// .
// x
Matrix mul(const Matrix &p,const Matrix &q)
{
    //auto c = Matrix();
    Matrix c;
    c.resize(p.x,q.y); c.init();
    for(int i = 1;i <= p.x;i ++)
        for(int j = 1;j <= q.y;j ++)
            for(int k = 1;k <= p.y;k ++){
                c.a[i][j] += p.a[i][k] * q.a[k][j]; c.a[i][j] %= mod;
            }
    return c;
}
int n,k;
void solve()
{
    cin >> n >> k;
    model.read(n,n); 
    res.resize(n,n);
    res.init_one();
    for(int i = 0;i <= 60;i ++)
    {  
        if(i > 0) model = mul(model,model);
        if((k >> i) & 1ll) res = mul(res,model);
    }
    res.print();
}
```

##### 超级幂
```C++
string divide_by_2(const string &num_str)
{
    string result;
    int carry = 0;
    for (int i = 0; i < num_str.size(); i++)
    {
        char digit = num_str[i];
        int current = carry * 10 + (digit - '0');
        carry = current % 2;
        result += (current / 2) + '0';
    }
    // 去除结果中的前导零
    size_t pos = result.find_first_not_of('0');
    if (pos != string::npos) {result = result.substr(pos);}
    else {result = "0";}
    return result;
}
int qpow(int a, string &b, int mod)
{
    int res = 1; a = (a % mod + mod) % mod;
    while (b != "0")
    {
        if ((b.back() - '0') % 2) {res = (res * a) % mod;}
        a = (a * a) % mod;
        b = divide_by_2(b);
    }
    return res;
}
```

##### 分数取模
```C++
int get_mod(int a,int b) {
    (a *= qmi(b, mod - 2, mod) )%= mod; return a;}
```

##### exgcd
```C++
typedef long long ll;
const int N = 5e6 + 10, mod = 1e9 + 7;
ll inv[N], n, a[N], s[N], sv[N];
int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0) {x = 1, y = 0; return a;}
    int d = exgcd(b, a % b, x, y);
    int z = x; x = y; y = z - y * (a / b);
    if (d < 0) {d = -d, x = -x, y = -y;}
    return d; // d = gcd(a, b), d > 0;
}
int inverse(int a, int b) // a为要求乘法逆元的数, b为mod, x是a的乘法逆元
{
    int x, y;
    int d = exgcd(a, b, x, y);
    x = (x % mod + mod) % mod;
    return x;
}
```

##### FFT_FAST快速傅里叶变换
```C++
// FFT_MAXN = 2^k
// fft_init() to precalc FFT_MAXN-th roots
typedef long double db;
const int FFT_MAXN=262144;
const db pi=acos(-1.);
struct cp{
	db a,b;
	cp operator+(const cp&y)const{return (cp){a+y.a,b+y.b};}
	cp operator-(const cp&y)const{return (cp){a-y.a,b-y.b};}
	cp operator*(const cp&y)const{return (cp){
            a*y.a-b*y.b,a*y.b+b*y.a};}
	cp operator!()const{return (cp){a,-b};};
}nw[FFT_MAXN+1];int bitrev[FFT_MAXN];
void dft(cp*a,int n,int flag=1){
	int d=0;while((1<<d)*n!=FFT_MAXN)d++;
	rep(i,0,n)if(i<(bitrev[i]>>d)) swap(a[i],a[bitrev[i]>>d]);
	for (int l=2;l<=n;l<<=1){
		int del=FFT_MAXN/l*flag;
		for (int i=0;i<n;i+=l){
			cp *le=a+i,*ri=a+i+(l>>1),
            *w=flag==1?nw:nw+FFT_MAXN;
			rep(k,0,l>>1){
				cp ne=*ri**w;
				*ri=*le-ne,*le=*le+ne;
				le++,ri++,w+=del;}}}
	if(flag!=1)rep(i,0,n)a[i].a/=n,a[i].b/=n;
}
void fft_init(){
	int L=0;while((1<<L)!=FFT_MAXN)L++;
	bitrev[0]=0;
    rep(i,1,FFT_MAXN)
        bitrev[i]=bitrev[i>>1]>>1|((i&1)<<(L-1));
	nw[0]=nw[FFT_MAXN]=(cp){1,0};
	rep(i,0,FFT_MAXN+1)
        nw[i]=(cp){
            cosl(2*pi/FFT_MAXN*i),sinl(2*pi/FFT_MAXN*i)};	
    //very slow
}
void convo(db*a,int n,db*b,int m,db*c){
	static cp f[FFT_MAXN>>1],g[FFT_MAXN>>1],t[FFT_MAXN>>1];
	int N=2;while(N<=n+m)N<<=1;
	rep(i,0,N)
		if(i&1){
			f[i>>1].b=(i<=n)?a[i]:0.0;
			g[i>>1].b=(i<=m)?b[i]:0.0;
		}else{
			f[i>>1].a=(i<=n)?a[i]:0.0;
			g[i>>1].a=(i<=m)?b[i]:0.0;
		}
	dft(f,N>>1);dft(g,N>>1);
	int del=FFT_MAXN/(N>>1);
	cp qua=(cp){0,0.25},one=(cp){1,0},four=(cp){4,0},*w=nw;
	rep(i,0,N>>1){
		int j=i?(N>>1)-i:0;
		t[i]=(four*!(f[j]*g[j])-
        (!f[j]-f[i])*(!g[j]-g[i])*(one+*w))*qua;
		w+=del;
	}
	dft(t,N>>1,-1);
	rep(i,0,n+m+1)c[i]=(i&1)?t[i>>1].a:t[i>>1].b;
}
void mul(int *a,int *b,int n){// n<=N, 0<=a[i],b[i]<mo
	static cp f[N],g[N],t[N],r[N];
	int nn=2;while(nn<=n+n)nn<<=1;
	rep(i,0,nn){
		f[i]=(i<=n)?(cp){(db)(a[i]>>15),
        (db)(a[i]&32767)}:(cp){0,0};
		g[i]=(i<=n)?(cp){(db)(b[i]>>15),
        (db)(b[i]&32767)}:(cp){0,0};
	}
	swap(n,nn); dft(f,n,1);dft(g,n,1);
	rep(i,0,n){
		int j=i?n-i:0;
		t[i]=( (f[i]+!f[j])*(!g[j]-g[i]) + 
        (!f[j]-f[i])*(g[i]+!g[j]) )*(cp){0,0.25};
		r[i]=(!f[j]-f[i])*(!g[j]-g[i])*(cp){-0.25,0}+ 
        (cp){0,0.25}*(f[i]+!f[j])*(g[i]+!g[j]);
	}
	dft(t,n,-1); dft(r,n,-1);
	rep(i,0,n) a[i]=( (ll(t[i].a+0.5)%mo<<15) + 
    ll(r[i].a+0.5) + (ll(r[i].b+0.5)%mo<<30) )%mo;
}
```

##### NTT快速数论变换
```C++
const int md = 998244353;
inline void add(int &x, int y) {x += y; if (x >= md) {x -= md;}}
inline void sub(int &x, int y) {x -= y; if (x < 0) {x += md;}}
inline int mul(int x, int y) {return (long long) x * y % md;}
inline int power(int x, int y) {
  int res = 1;
  for (; y; y >>= 1, x = mul(x, x)) {if (y & 1) {res = mul(res, x);}}
  return res;
}
inline int inv(int a) {
  a %= md;
  if (a < 0) {a += md;}
  int b = md, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= t * a;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  if (u < 0) {u += md;}
  return u;
}
namespace ntt {
int base = 1, root = -1, max_base = -1;
vector<int> rev = {0, 1}, roots = {0, 1};
void init() {
  int temp = md - 1;
  max_base = 0;
  while (temp % 2 == 0) {
    temp >>= 1;
    ++max_base;
  }
  root = 2;
  while (true) {
    if (power(root, 1 << max_base) == 1 && 
    power(root, 1 << (max_base - 1)) != 1) {break;}
    ++root;
  }
}
void ensure_base(int nbase) {
  if (max_base == -1) {init();}
  if (nbase <= base) {return;}
  assert(nbase <= max_base);
  rev.resize(1 << nbase);
  for (int i = 0; i < 1 << nbase; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nbase - 1));}
  roots.resize(1 << nbase);
  while (base < nbase) {
    int z = power(root, 1 << (max_base - 1 - base));
    for (int i = 1 << (base - 1); i < 1 << base; ++i) {
      roots[i << 1] = roots[i];
      roots[i << 1 | 1] = mul(roots[i], z);
    }
    ++base;
  }
}
void dft(vector<int> &a) {
  int n = a.size(), zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; ++i) {
    if (i < rev[i] >> shift) {
      swap(a[i], a[rev[i] >> shift]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        int x = a[j + k], y = mul(a[j + k + i], roots[i + k]);
        a[j + k] = (x + y) % md;
        a[j + k + i] = (x + md - y) % md;
      }
    }
  }
}
vector<int> multiply(vector<int> a, vector<int> b) {
  int need = a.size() + b.size() - 1, nbase = 0;
  while (1 << nbase < need) {++nbase;}
  ensure_base(nbase);
  int sz = 1 << nbase;
  a.resize(sz);
  b.resize(sz);
  bool equal = a == b;
  dft(a);
  if (equal) {b = a;} 
  else {dft(b);}
  int inv_sz = inv(sz);
  for (int i = 0; i < sz; ++i) {a[i] = mul(mul(a[i], b[i]), inv_sz);}
  reverse(a.begin() + 1, a.end());
  dft(a);
  a.resize(need);
  return a;
}
vector<int> inverse(vector<int> a) {
  int n = a.size(), m = (n + 1) >> 1;
  if (n == 1) {return vector<int>(1, inv(a[0]));} 
  else {
    vector<int> b = inverse(vector<int>(a.begin(), a.begin() + m));
    int need = n << 1, nbase = 0;
    while (1 << nbase < need) {++nbase;}
    ensure_base(nbase);
    int sz = 1 << nbase;
    a.resize(sz);
    b.resize(sz);
    dft(a);
    dft(b);
    int inv_sz = inv(sz);
    for (int i = 0; i < sz; ++i) {
        a[i] = mul(mul(md + 2 - mul(a[i], b[i]), b[i]), inv_sz);}
    reverse(a.begin() + 1, a.end());
    dft(a);
    a.resize(n);
    return a;
  }
}
}
using ntt::multiply;
using ntt::inverse;
vector<int>& operator += (vector<int> &a, const vector<int> &b) {
  if (a.size() < b.size()) {a.resize(b.size());}
  for (int i = 0; i < b.size(); ++i) {add(a[i], b[i]);}
  return a;
}
vector<int> operator + (const vector<int> &a, const vector<int> &b) {
  vector<int> c = a;
  return c += b;
}
vector<int>& operator -= (vector<int> &a, const vector<int> &b) {
  if (a.size() < b.size()) {a.resize(b.size());}
  for (int i = 0; i < b.size(); ++i) {sub(a[i], b[i]);}
  return a;
}
vector<int> operator - (const vector<int> &a, const vector<int> &b) {
  vector<int> c = a;
  return c -= b;
}
vector<int>& operator *= (vector<int> &a, const vector<int> &b) {
  if (min(a.size(), b.size()) < 128) {
    vector<int> c = a;
    a.assign(a.size() + b.size() - 1, 0);
    for (int i = 0; i < c.size(); ++i) {
      for (int j = 0; j < b.size(); ++j) {
        add(a[i + j], mul(c[i], b[j]));
      }
    }
  } else {a = multiply(a, b);}
  return a;
}
vector<int> operator * (const vector<int> &a, const vector<int> &b) {
  vector<int> c = a;
  return c *= b;
}
vector<int>& operator /= (vector<int> &a, const vector<int> &b) {
  int n = a.size(), m = b.size();
  if (n < m) {a.clear();} 
  else {
    vector<int> c = b;
    reverse(a.begin(), a.end());
    reverse(c.begin(), c.end());
    c.resize(n - m + 1);
    a *= inverse(c);
    a.erase(a.begin() + n - m + 1, a.end());
    reverse(a.begin(), a.end());
  }
  return a;
}
vector<int> operator / (const vector<int> &a, const vector<int> &b) {
  vector<int> c = a;
  return c /= b;
}
vector<int>& operator %= (vector<int> &a, const vector<int> &b) {
  int n = a.size(), m = b.size();
  if (n >= m) {
    vector<int> c = (a / b) * b;
    a.resize(m - 1);
    for (int i = 0; i < m - 1; ++i) {sub(a[i], c[i]);}
  }
  return a;
}
vector<int> operator % (const vector<int> &a, const vector<int> &b) {
  vector<int> c = a;
  return c %= b;
}
vector<int> derivative(const vector<int> &a) {
  int n = a.size();
  vector<int> b(n - 1);
  for (int i = 1; i < n; ++i) {b[i - 1] = mul(a[i], i);}
  return b;
}
vector<int> primitive(const vector<int> &a) {
  int n = a.size();
  vector<int> b(n + 1), invs(n + 1);
  for (int i = 1; i <= n; ++i) {
    invs[i] = i == 1 ? 1 : mul(md - md / i, invs[md % i]);
    b[i] = mul(a[i - 1], invs[i]);
  }
  return b;
}
vector<int> logarithm(const vector<int> &a) {
  vector<int> b = primitive(derivative(a) * inverse(a));
  b.resize(a.size());
  return b;
}
vector<int> exponent(const vector<int> &a) {
  vector<int> b(1, 1);
  while (b.size() < a.size()) {
    vector<int> c(a.begin(), a.begin() + min(a.size(), b.size() << 1));
    add(c[0], 1);
    vector<int> old_b = b;
    b.resize(b.size() << 1);
    c -= logarithm(b);
    c *= old_b;
    for (int i = b.size() >> 1; i < b.size(); ++i) {b[i] = c[i];}
  }
  b.resize(a.size());
  return b;
}
vector<int> power(vector<int> a, int m) {
  int n = a.size(), p = -1;
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {if (a[i]) {p = i; break;}}
  if (p == -1) {b[0] = !m; return b;}
  if ((long long) m * p >= n) {return b;}
  int mu = power(a[p], m), di = inv(a[p]);
  vector<int> c(n - m * p);
  for (int i = 0; i < n - m * p; ++i) {c[i] = mul(a[i + p], di);}
  c = logarithm(c);
  for (int i = 0; i < n - m * p; ++i) {c[i] = mul(c[i], m);}
  c = exponent(c);
  for (int i = 0; i < n - m * p; ++i) {b[i + m * p] = mul(c[i], mu);}
  return b;
}
vector<int> sqrt(const vector<int> &a) {
  vector<int> b(1, 1);
  while (b.size() < a.size()) {
    vector<int> c(a.begin(), a.begin() + min(a.size(), b.size() << 1));
    vector<int> old_b = b;
    b.resize(b.size() << 1);
    c *= inverse(b);
    for (int i = b.size() >> 1; i < b.size(); ++i) {
        b[i] = mul(c[i], (md + 1) >> 1);}
  }
  b.resize(a.size());
  return b;
}
vector<int> multiply_all(int l, int r, vector<vector<int>> &all) {
  if (l > r) {return vector<int>();} 
  else if (l == r) {return all[l];} 
  else {
    int y = (l + r) >> 1;
    return multiply_all(l, y, all) * multiply_all(y + 1, r, all);
  }
}
vector<int> evaluate(const vector<int> &f, const vector<int> &x) {
  int n = x.size();
  if (!n) {return vector<int>();}
  vector<vector<int>> up(n * 2);
  for (int i = 0; i < n; ++i) {
    up[i + n] = vector<int>{(md - x[i]) % md, 1};}
  for (int i = n - 1; i; --i) {up[i] = up[i << 1] * up[i << 1 | 1];}
  vector<vector<int>> down(n * 2);
  down[1] = f % up[1];
  for (int i = 2; i < n * 2; ++i) {down[i] = down[i >> 1] % up[i];}
  vector<int> y(n);
  for (int i = 0; i < n; ++i) {y[i] = down[i + n][0];}
  return y;
}
vector<int> interpolate(const vector<int> &x, const vector<int> &y) {
  int n = x.size();
  vector<vector<int>> up(n * 2);
  for (int i = 0; i < n; ++i) {
    up[i + n] = vector<int>{(md - x[i]) % md, 1};}
  for (int i = n - 1; i; --i) {up[i] = up[i << 1] * up[i << 1 | 1];}
  vector<int> a = evaluate(derivative(up[1]), x);
  for (int i = 0; i < n; ++i) {a[i] = mul(y[i], inv(a[i]));}
  vector<vector<int>> down(n * 2);
  for (int i = 0; i < n; ++i) {down[i + n] = vector<int>(1, a[i]);}
  for (int i = n - 1; i; --i) {
    down[i] = down[i << 1] * up[i << 1 | 1] + 
    down[i << 1 | 1] * up[i << 1];}
  return down[1];
}
```

##### 线性基
```C++
const int N = 210;
const int B = 60;
struct linear_basis{
	int num[B + 1];
	bool insert(int x){
	for(int i = B - 1;i >= 0;i --){
	if(x & (1ll << i)) {
		if(num[i] == 0) {num[i] = x; return true;}
		x ^= num[i];
		// 如果当前最高位的数存在 就消掉
		// 如果不存在 就填上去
	}
	}
		return false;
	}
	int querymin(int x){
		for(int i = B - 1; i >= 0;i --) {
            x = min(x, x ^ num[i]);}
		return x;
	}
	int querymax(int x) {
		for(int i = B - 1;i >= 0;i --) {
            x = max(x, x ^ num[i]);}
		return x;
	} // 求最大
	bool askval(int x){
        for(int i = B - 1;i >= 0;i --) 
        if(x & (1ll << i)) x ^= num[i];
        return x == 0;
	} // 求可不可以异或出来
}T;
```

#### STL

##### string
```C++
//利用反向迭代器翻转
s = string(s.rbegin(),s.rend());
```

##### assign()
```C++
void assign(const_iterator first,const_iterator last);
void assign(size_type n,const T& x = T());
```

##### map
```C++
void solve()
{
   map<int, char> cont{{1, 'a'}, {2, 'b'}, {3, 'c'}};
    for(auto [k,v] : cont)
    cout << "( " << k << " , " << v << " ) ";
    cout << endl;
    // ( 1 , a ) ( 2 , b ) ( 3 , c ) 
    // Extract node handle and change key
    auto nh = cont.extract(1);
    nh.key() = 4;
    for(auto [k,v] : cont)
    cout << "( " << k << " , " << v << " ) "; 
    cout << endl;
    // ( 2 , b ) ( 3 , c ) 
    cont.insert(move(nh));
    for(auto [k,v] : cont)
    cout << "( " << k << " , " << v << " ) "; 
    // ( 2 , b ) ( 3 , c ) ( 4 , a )
}
```

##### set
妙用，使用set对数组进行去重，排序。
```C++
const int N = 100;
int n,a[N];
void solve()
{
   cin >> n; for(int i = 1;i <= n;i ++) cin >> a[i];
   set<int> s(a + 1,a + 1 + n); 
   for(int x : s) cout << x << ' '; cout << '\n';
}
```

#### 计算几何
```C++
namespace Geometry
{
    const double pi = acos(-1);
    const double eps = 1e-8;
    // 点与向量
    struct Point
    {
        double x, y;
        Point(double x = 0, double y = 0) : x(x), y(y) {}
        bool operator==(const Point a) const
        {
            return (fabs(x - a.x) <= eps && fabs(y - a.y) <= eps);
        }
        void input()
        {
            cin >> x >> y;
        }
        void output()
        {
            cout << fixed << setprecision(10) << x << ' ' << y << '\n';
        }
        double distance(Point p)
        {
            return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
        }
    };
    typedef Point Vector;
    Vector operator+(Vector A, Vector B)
    {
        return Vector(A.x + B.x, A.y + B.y);
    }
    Vector operator-(Vector A, Vector B)
    {
        return Vector(A.x - B.x, A.y - B.y);
    }
    Vector operator*(Vector A, double p)
    {
        return Vector(A.x * p, A.y * p);
    }
    Vector operator/(Vector A, double p)
    {
        return Vector(A.x / p, A.y / p);
    }
    int sign(double x)
    { // 符号函数
        if (fabs(x) < eps) return 0;
        if (x < 0) return -1;
        return 1;
    }
    int cmp(double x, double y)
    { // 比较函数
        if (fabs(x - y) < eps) return 0;
        if (x < y) return -1;
        return 1;
    }
    double dot(Point a, Point b)
    { // 向量点积
        return a.x * b.x + a.y * b.y;
    }
    double cross(Point a, Point b)
    { // 向量叉积
        return a.x * b.y - b.x * a.y;
    }
    double get_length(Point a)
    { // 求向量模长
        return sqrt(dot(a, a));
    }
    double get_angle(Point a, Point b)
    { // 求A->B的有向角
        return acos(dot(a, b) / get_length(a) / get_length(b));
    }
    double area(Point a, Point b, Point c)
    { // A为顶点，向量AB与向量AC的叉积，即三角形ABC的面积的2倍（有向）
        return cross(b - a, c - a);
    }
    Point rotate(Point a, double angle)
    { // 将向量A顺时针旋转angle度
        return Point(a.x * cos(angle) + a.y * sin(angle), 
        -a.x * sin(angle) + a.y * cos(angle));
    }
    Point get_line_intersection(Point p, Vector v, Point q, Vector w)
    { // 两直线的交点
        // 使用前提，直线必须有交点
        // cross(v, w) == 0则两直线平行或者重合
        Vector u = p - q;
        double t = cross(w, u) / cross(v, w);
        return p + v * t;
    }
    double distance_to_line(Point p, Point a, Point b)
    { // 点到直线的距离，直线为AB所在直线
        Vector v1 = b - a, v2 = p - a;
        return fabs(cross(v1, v2) / get_length(v1));
    }
    double distance_to_segment(Point p, Point a, Point b)
    { // 点到线段的距离，线段为线段AB
        if (a == b) return get_length(p - a);
        Vector v1 = b - a, v2 = p - a, v3 = p - b;
        if (sign(dot(v1, v2)) < 0) return get_length(v2);
        if (sign(dot(v1, v3)) > 0) return get_length(v3);
        return distance_to_line(p, a, b);
    }
    Point get_line_projection(Point p, Point a, Point b)
    { // 点在直线上的投影，直线为AB所在直线
        Vector v = b - a;
        return a + v * (dot(v, p - a) / dot(v, v));
    }
    bool on_segment(Point p, Point a, Point b)
    { // 点是否在线段上
        return sign(cross(p - a, p - b)) == 0 && 
        sign(dot(p - a, p - b)) <= 0;
    }
    bool segment_intersection(Point a1, Point a2, Point b1, Point b2)
    { // 判断两个线段是否相交
        double c1 = cross(a2 - a1, b1 - a1), 
        c2 = cross(a2 - a1, b2 - a1);
        double c3 = cross(b2 - b1, a2 - b1), 
        c4 = cross(b2 - b1, a1 - b1);
        return sign(c1) * sign(c2) <= 0 && 
        sign(c3) * sign(c4) <= 0;
    }
    // 多边形
    double polygon_area(Point p[], int n)
    { // 求多边形面积
        double s = 0;
        for (int i = 1; i + 1 < n; i++) 
        s += cross(p[i] - p[0], p[i + 1] - p[i]);
        return s / 2;
    }
}
using namespace Geometry;
```

#### 字符串

##### KMP
```C++
class KMP
{
    string b;
public:
    vector<int> nx;
    KMP(string b)
    {
        this->b = b;
        int n = b.length(), j = 0;
        nx.resize(n);
        for (int i = 1; i < n; i++)
        {
            while (j > 0 && b[i] != b[j]) j = nx[j - 1];
            if (b[i] == b[j]) j++;
            nx[i] = j;
        }
    }
    int matchTimes(string a) // a中出现多少次b
    {
        int n = b.length(), m = a.length(), j = 0, ans = 0;
        for (int i = 0; i < m; i++)
        {
            while (j > 0 && a[i] != b[j]) j = nx[j - 1];
            if (a[i] == b[j]) j++;
            if (j == n) {ans++; j = nx[j - 1];}
        }
        return ans;
    }
    int firstMatchLocation(string a) // b在a中第一次出现的位置下标
    {
        int n = b.length(), m = a.length(), j = 0, ans = 0;
        for (int i = 0; i < m; i++)
        {
            while (j > 0 && a[i] != b[j]) j = nx[j - 1];
            if (a[i] == b[j]) j++;
            if (j == n) {return i - n + 1;}
        }
        return -1;
    }
};
```

##### 字符串哈希
```C++
const int b = 131;
long long hs[N], b_pow[N];
void initHash(){
    b_pow[0] = 1;
    for (int i = 1; i <= n; i++){
        hs[i] = hs[i - 1] * b + s[i] - 'a' + 1;
        b_pow[i] = b_pow[i - 1] * b;
    }
}
long long getSub(int l, int r) 
    return hs[r] - hs[l - 1] * b_pow[r - l + 1];
```

##### 最小表示法
```C++
int k = 0, i = 0, j = 1;
while (k < n && i < n && j < n) {
  if (sec[(i + k) % n] == sec[(j + k) % n]) { k++;} 
  else {
    sec[(i + k) % n] > sec[(j + k) % n] ? 
    i = i + k + 1 : j = j + k + 1;
    if (i == j) i++;
    k = 0;
  }
}
i = min(i, j);
```

##### Trie字典树
```C++
#define re register
int top(1);
char str[60];
const int N=5e5+10;
struct Trie{
    bool count;    // count表示此单词是否已被查询。
    int next[26];
    bool exist;    // exist表示此处是否为一个单词；
} a[N];
inline void Trie_insert()
{ 
    //普通insert操作，将字符串一一加入字典中
    int num(0), root = 1;
    for (re int i = 0; str[i]; ++i)
    {
        num = str[i] - 'a';
        if (!a[root].next[num]) a[root].next[num] = ++top;
        root = a[root].next[num];
    }
    a[root].exist = true;
    return;
}
inline int Trie_search()
{ 
    //普通search操作，查询是否存在该字符串
    int num(0), root = 1;
    for (re int i = 0; str[i]; ++i)
    {
        num = str[i] - 'a';
        if (!a[root].next[num]) return 0; 
        //若无法查询到后继的字母，直接退出
        root = a[root].next[num];
    }
    if (!a[root].exist) return 0; //若此处不存在字符串，返回“WRONG”
    else if (a[root].count) return 2;         
    //若此处字符串已被查询，返回“REPEAT”
    a[root].count = true; //若以上均不满足，说明合法
    return 1;             //此字符串标记为已查询，返回“OK”
}
```

#### 高精度
```C++
class BigInteger {
private:
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    bool sign;
    size_t length;
    vector<int> num;

    void cutLeadingZero();
    void setLength();

public:
    BigInteger(int n = 0);
    BigInteger(long long n);
    BigInteger(const char *n);
    BigInteger(const BigInteger &n);

    const BigInteger& operator=(int n);
    const BigInteger& operator=(long long n);
    const BigInteger& operator=(const char *n);
    const BigInteger& operator=(const BigInteger &n);

    size_t size() const;
    BigInteger e(size_t n) const;
    BigInteger abs() const;

    const BigInteger& operator+() const;
    friend BigInteger operator+(const BigInteger &a, const BigInteger &b);
    const BigInteger& operator+=(const BigInteger &n);
    const BigInteger& operator++();
    BigInteger operator++(int);

    BigInteger operator-() const;
    friend BigInteger operator-(const BigInteger &a, const BigInteger &b);
    const BigInteger& operator-=(const BigInteger &n);
    const BigInteger& operator--();
    BigInteger operator--(int);

    friend BigInteger operator*(const BigInteger &a, const BigInteger &b);
    const BigInteger& operator*=(const BigInteger &n);

    friend BigInteger operator/(const BigInteger &a, const BigInteger &b);
    const BigInteger& operator/=(const BigInteger &n);

    friend BigInteger operator%(const BigInteger &a, const BigInteger &b);
    const BigInteger& operator%=(const BigInteger &n);

    friend bool operator<(const BigInteger &a, const BigInteger &b);
    friend bool operator<=(const BigInteger &a, const BigInteger &b);
    friend bool operator>(const BigInteger &a, const BigInteger &b);
    friend bool operator>=(const BigInteger &a, const BigInteger &b);
    friend bool operator==(const BigInteger &a, const BigInteger &b);
    friend bool operator!=(const BigInteger &a, const BigInteger &b);

    friend bool operator||(const BigInteger &a, const BigInteger &b);
    friend bool operator&&(const BigInteger &a, const BigInteger &b);
    bool operator!();

    friend ostream& operator<<(ostream &out, const BigInteger &n);
    friend istream& operator>>(istream &in, BigInteger &n);
};

void BigInteger::cutLeadingZero() {
    while(num.back() == 0 && num.size() != 1) {
        num.pop_back();
    }
}

void BigInteger::setLength() {
    cutLeadingZero();
    int tmp = num.back();
    if(tmp == 0) {
        length = 1;
    } else {
        length = (num.size() - 1) * 8;
        while(tmp > 0) {
            ++length;
            tmp /= 10;
        }
    }
}

BigInteger::BigInteger(int n) {
    *this = n;
}

BigInteger::BigInteger(long long n) {
    *this = n;
}

BigInteger::BigInteger(const char *n) {
    *this = n;
}

BigInteger::BigInteger(const BigInteger &n) {
    *this = n;
}

const BigInteger& BigInteger::operator=(int n) {
    *this = (long long)n;
    return *this;
}

const BigInteger& BigInteger::operator=(long long n) {
    num.clear();
    if(n == 0) {
        num.push_back(0);
    }
    if(n >= 0) {
        sign = true;
    } else if(n == LONG_LONG_MIN) {
        *this = "-9223372036854775808";
        return *this;
    } else if(n < 0) {
        sign = false;
        n = -n;
    }
    while(n != 0) {
        num.push_back(n % BASE);
        n /= BASE;
    }
    setLength();
    return *this;
}

const BigInteger& BigInteger::operator=(const char *n) {
    int len = strlen(n);
    int tmp = 0;
    int ten = 1;
    int stop = 0;
    num.clear();
    sign = (n[0] != '-');
    if(!sign) {
        stop = 1;
    }
    for(int i = len; i > stop; --i) {
        tmp += (n[i - 1] - '0') * ten;
        ten *= 10;
        if((len - i) % 8 == 7) {
            num.push_back(tmp);
            tmp = 0;
            ten = 1;
        }
    }
    if((len - stop) % WIDTH != 0) {
        num.push_back(tmp);
    }
    setLength();
    return *this;
}

const BigInteger& BigInteger::operator=(const BigInteger &n) {
    num = n.num;
    sign = n.sign;
    length = n.length;
    return *this;
}

size_t BigInteger::size() const {
    return length;
}

BigInteger BigInteger::e(size_t n) const {
    int tmp = n % 8;
    BigInteger ans;
    ans.length = n + 1;
    n /= 8;
    while(ans.num.size() <= n) {
        ans.num.push_back(0);
    }
    ans.num[n] = 1;
    while(tmp--) {
        ans.num[n] *= 10;
    }
    return ans * (*this);
}

BigInteger BigInteger::abs() const {
    BigInteger ans(*this);
    ans.sign = true;
    return ans;
}

const BigInteger& BigInteger::operator+() const {
    return *this;
}

BigInteger operator+(const BigInteger &a, const BigInteger &b) {
    if(!b.sign) {
        return a - (-b);
    }
    if(!a.sign) {
        return b - (-a);
    }
    BigInteger ans;
    int carry = 0;
    int aa, bb;
    size_t lena = a.num.size();
    size_t lenb = b.num.size();
    size_t len = max(lena, lenb);
    ans.num.clear();
    for(size_t i = 0; i < len; ++i) {
        if(lena <= i) {
            aa = 0;
        } else {
            aa = a.num[i];
        }
        if(lenb <= i) {
            bb = 0;
        } else {
            bb = b.num[i];
        }
        ans.num.push_back((aa + bb + carry) % BigInteger::BASE);
        carry = (aa + bb + carry) / BigInteger::BASE;
    }
    if(carry > 0) {
        ans.num.push_back(carry);
    }
    ans.setLength();
    return ans;
}

const BigInteger& BigInteger::operator+=(const BigInteger &n) {
    *this = *this + n;
    return *this;
}

const BigInteger& BigInteger::operator++() {
    *this = *this + 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger ans(*this);
    *this = *this + 1;
    return ans;
}

BigInteger BigInteger::operator-() const {
    BigInteger ans(*this);
    if(ans != 0) {
        ans.sign = !ans.sign;
    }
    return ans;
}

BigInteger operator-(const BigInteger &a, const BigInteger &b) {
    if(!b.sign) {
        return a + (-b);
    }
    if(!a.sign) {
        return -((-a) + b);
    }
    if(a < b) {
        return -(b - a);
    }
    BigInteger ans;
    int carry = 0;
    int aa, bb;
    size_t lena = a.num.size();
    size_t lenb = b.num.size();
    size_t len = max(lena, lenb);
    ans.num.clear();
    for(size_t i = 0; i < len; ++i) {
        aa = a.num[i];
        if(i >= lenb) {
            bb = 0;
        } else {
            bb = b.num[i];
        }
        ans.num.push_back((aa - bb - carry + BigInteger::BASE) % BigInteger::BASE);
        if(aa < bb + carry) {
            carry = 1;
        } else {
            carry = 0;
        }
    }
    ans.setLength();
    return ans;
}

const BigInteger& BigInteger::operator-=(const BigInteger &n) {
    *this = *this - n;
    return *this;
}

const BigInteger& BigInteger::operator--() {
    *this = *this - 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger ans(*this);
    *this = *this - 1;
    return ans;
}

BigInteger operator*(const BigInteger &a, const BigInteger&b) {
    size_t lena = a.num.size();
    size_t lenb = b.num.size();
    vector<long long> ansLL;
    for(size_t i = 0; i < lena; ++i) {
        for(size_t j = 0; j < lenb; ++j) {
            if(i + j >= ansLL.size()) {
                ansLL.push_back((long long)a.num[i] * (long long)b.num[j]);
            } else {
                ansLL[i + j] += (long long)a.num[i] * (long long)b.num[j];
            }
        }
    }
    while(ansLL.back() == 0 && ansLL.size() != 1) {
        ansLL.pop_back();
    }
    size_t len = ansLL.size();
    long long carry = 0;
    long long tmp;
    BigInteger ans;
    ans.sign = (ansLL.size() == 1 && ansLL[0] == 0) || (a.sign == b.sign);
    ans.num.clear();
    for(size_t i = 0; i < len; ++i) {
        tmp = ansLL[i];
        ans.num.push_back((tmp + carry) % BigInteger::BASE);
        carry = (tmp + carry) / BigInteger::BASE;
    }
    if(carry > 0) {
        ans.num.push_back(carry);
    }
    ans.setLength();
    return ans;
}

const BigInteger& BigInteger::operator*=(const BigInteger &n) {
    *this = *this * n;
    return *this;
}

BigInteger operator/(const BigInteger &a, const BigInteger &b) {
    BigInteger aa(a.abs());
    BigInteger bb(b.abs());
    if(aa < bb) {
        return 0;
    }
    char *str = new char[aa.size() + 1];
    memset(str, 0, sizeof(char) * (aa.size() + 1));
    BigInteger tmp;
    int lena = aa.length;
    int lenb = bb.length;
    for(int i = 0; i <= lena - lenb; ++i) {
        tmp = bb.e(lena - lenb - i);
        while(aa >= tmp) {
            ++str[i];
            aa = aa - tmp;
        }
        str[i] += '0';
    }

    BigInteger ans(str);
    delete[]str;
    ans.sign = (ans == 0 || a.sign == b.sign);
    return ans;
}

const BigInteger& BigInteger::operator/=(const BigInteger &n) {
    *this = *this / n;
    return *this;
}

BigInteger operator%(const BigInteger &a, const BigInteger &b) {
    return a - a / b * b;
}

const BigInteger& BigInteger::operator%=(const BigInteger &n) {
    *this = *this - *this / n * n;
    return *this;
}

bool operator<(const BigInteger &a, const BigInteger &b) {
    if(a.sign && !b.sign) {
        return false;
    } else if(!a.sign && b.sign) {
        return true;
    } else if(a.sign && b.sign) {
        if(a.length < b.length) {
            return true;
        } else if(a.length > b.length) {
            return false;
        } else {
            size_t lena = a.num.size();
            for(int i = lena - 1; i >= 0; --i) {
                if(a.num[i] < b.num[i]) {
                    return true;
                } else if(a.num[i] > b.num[i]) {
                    return false;
                }
            }
            return false;
        }
    } else {
        return -b < -a;
    }
}

bool operator<=(const BigInteger &a, const BigInteger &b) {
    return !(b < a);
}

bool operator>(const BigInteger &a, const BigInteger &b) {
    return b < a;
}

bool operator>=(const BigInteger &a, const BigInteger &b) {
    return !(a < b);
}

bool operator==(const BigInteger &a, const BigInteger &b) {
    return !(a < b) && !(b < a);
}

bool operator!=(const BigInteger &a, const BigInteger &b) {
    return (a < b) || (b < a);
}

bool operator||(const BigInteger &a, const BigInteger &b) {
    return a != 0 || b != 0;
}

bool operator&&(const BigInteger &a, const BigInteger &b) {
    return a != 0 && b != 0;
}

bool BigInteger::operator!() {
    return *this == 0;
}

ostream& operator<<(ostream &out, const BigInteger &n) {
    size_t len = n.num.size();
    if(!n.sign) {
        out << '-';
    }
    out << n.num.back();
    for(int i = len - 2; i >= 0; --i) {
        out << setw(BigInteger::WIDTH) << setfill('0') << n.num[i];
    }
    return out;
}

istream& operator>>(istream &in, BigInteger &n) {
    string str;
    in >> str;
    size_t len = str.length();
    size_t i, start = 0;
    if(str[0] == '-') {
        start = 1;
    }
    if(str[start] == '\0') {
        return in;
    }
    for(i = start; i < len; ++i) {
        if(str[i] < '0' || str[i] > '9') {
            return in;
        }
    }
    n = str.c_str();
    return in;
}
```

#### 小寄巧

##### 离散化
> 离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。
```C++
rep(i,1,n) cin >> w[i],nums.pb(w[i]);
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    rep(i,1,n) 
    w[i] = lower_bound(nums.begin(),nums.end(),w[i]) - nums.begin();
```

##### 随机函数
```C++
vector<int> g;
int Rand(int i) {return rand()%i;}
int main()
{
	fileoi();
	int n;cin >> n;
	for(int i = 1;i <= n;i ++) {int x; cin >> x; g.push_back(x);}
	//sort(g.begin(),g.end());
	srand ( unsigned ( time(0) ) );
	for(int i = 0;i < 10;i ++){
	random_shuffle(g.begin(),g.end(),Rand);
	for(int x : g) cout << x << ' ';
	cout << endl;
   }
}
```

#### 打印

##### 打印__int128
```C++
void print(__int128_t x)
{
    if (x < 0) {x = -x; putchar('-');}
    if (x > 9) {print(x / 10);}
    putchar(x % 10 + '0');
}
```