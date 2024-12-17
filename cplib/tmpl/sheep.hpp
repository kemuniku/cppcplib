#include <bits/stdc++.h>
using namespace std;

// ★★★★★ いわゆるQCFium、おまじない的につけとくと速い
#ifndef LOCAL_TEST
#pragma GCC target ("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif // LOCAL_TEST

// ★★★★★ 型名を短くする、ちょっと嬉しい
using ll = long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
using vi = vector<int>;  using vvi = vector<vi>; using vvvi = vector<vvi>;
using vl = vector<ll>;  using vvl = vector<vl>; using vvvl = vector<vvl>;
using vb = vector<bool>; using vvb = vector<vb>; using vvvb = vector<vvb>;
using vc = vector<char>; using vvc = vector<vc>; using vvvc = vector<vvc>;
using vd = vector<double>; using vvd = vector<vd>; using vvvd = vector<vvd>;
using vs = vector<string>; using vvs = vector<vector<string>>; using vvvs = vector<vector<vector<string>>>;

// ★★★ 多次元vector初期化用の関数、ちょっと癖があるけど短く書ける
// テンプレなし：vector dp(n+1, vector(m+1, vector<ll>(k+1, 0)));
// テンプレあり：auto dp = vvv<ll>(n+1, m+1, k+1, 0);
template<typename T> vector<vector<T>> vv(int h, int w, T val = T()) { return vector(h, vector<T>(w, val)); }
template<typename T> vector<vector<vector<T>>> vvv(int h1, int h2, int h3, T val = T()) { return vector(h1, vector(h2, vector<T>(h3, val))); }
template<typename T> vector<vector<vector<vector<T>>>> vvvv(int h1, int h2, int h3, int h4, T val = T()) { return vector(h1, vector(h2, vector(h3, vector<T>(h4, val)))); }

// ★★ いわゆるheapq、C++のデフォルトpriority_queueは大きい順（Python、Nimとは逆）に注意
template <class T> using priority_queue_min = priority_queue<T, vector<T>, greater<T>>;

// ★ 定数系、お好みで
constexpr double PI = 3.14159265358979323;
constexpr int INF = 100100111; constexpr ll INFL = 3300300300300300491LL;
float EPS = 1e-8; double EPSL = 1e-10;


// ★★★★ 入出力高速化、おまじない
struct Nyan { Nyan() { cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(18); } } nyan;

// マクロ類
// わりと全部使う
// all: sort(all(a)) とか lower_bount(all(a), x) とか
// rep: オーバーロードしているので、引数の個数で挙動が変わる、基本Pythonのrangeに近い感覚で使えるようにしてるはず
//      rep(5) -> 5回ループ（新たにループ変数は作らない）
//      rep(i, 5) -> i=0,1,...,4
//      rep(i, 5) -> i=0,1,...,4
//      rep(i, 1, 6) -> i=1,...,4
//      rep(i, 1, 6, 2) -> i=1,3,5
//      rep(i, 10, -1, -1) -> i=10,9,.., 0
// smod, sdiv: python-like mod, div
// uniq: 重複削除、ソートされるのに注意
// vl a = {1, 3, 2, 5, 2, 3}; uniq(a); // a = {1, 2, 3, 5}
#define all(a) (a).begin(), (a).end()
#define sz(x) ((ll)(x).size())
#define rep1(n) for(ll dummy_iter = 0LL; dummy_iter < n; ++dummy_iter) // 0,1,...,n-1
#define rep2(i, n) for(ll i = 0LL, i##_counter = 0LL; i##_counter < ll(n); ++(i##_counter), (i) = i##_counter) // i=0,1,...,n-1
#define rep3(i, s, t) for(ll i = ll(s), i##_counter = ll(s); i##_counter < ll(t); ++(i##_counter), (i) = (i##_counter)) // i=s,s+1,...,t-1
#define rep4(i, s, t, step) for(ll i##_counter = step > 0 ? ll(s) : -ll(s), i##_end = step > 0 ? ll(t) : -ll(t), i##_step = abs(step), i = ll(s); i##_counter < i##_end; i##_counter += i##_step, i = step > 0 ? i##_counter : -i##_counter) // i=s,s+step,...,<t
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define repe(a, v) for(auto& a : (v)) // iterate over all elements in v
#define smod(n, m) ((((n) % (m)) + (m)) % (m))
#define sdiv(n, m) (((n) - smod(n, m)) / (m))
#define uniq(a) {sort(all(a)); (a).erase(unique(all(a)), (a).end());}

// ★★ Yes, No なくても困らない
int Yes(bool b=true) { cout << (b ? "Yes\n" : "No\n"); return 0; };
int YES(bool b=true) { cout << (b ? "YES\n" : "NO\n"); return 0; };
int No(bool b=true) {return Yes(!b);};
int NO(bool b=true) {return YES(!b);};

// ★★★★ max, min, sum のvector向けオーバーロード、デフォルトがちょっと使いにくいので
template<typename T, size_t N> T max(array<T, N>& a) { return *max_element(all(a)); };
template<typename T, size_t N> T min(array<T, N>& a) { return *min_element(all(a)); };
template<typename T> T max(vector<T>& a) { return *max_element(all(a)); };
template<typename T> T min(vector<T>& a) { return *min_element(all(a)); };
template<typename T> vector<T> vec_slice(const vector<T>& a, int l, int r) { vector<T> rev; rep(i, l, r) rev.push_back(a[i]); return rev; };
template<typename T> T sum(vector<T>& a, T zero = T(0)) { T rev = zero; rep(i, sz(a)) rev += a[i]; return rev; };

// ★★★ vector の各要素を1増やす／減らす、グラフ系の入力受けでちょっと嬉しい
// vector<ll> a = {1, 2, 4}; ++a; // a = {2, 3, 5}
template <class T> inline vector<T>& operator--(vector<T>& v) { repe(x, v) --x; return v; }
template <class T> inline vector<T>& operator++(vector<T>& v) { repe(x, v) ++x; return v; }

// ★★★★ 整数pow/sqrt
ll powm(ll a, ll n, ll mod=INFL) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = (res * a) % mod;
        if (n > 1) a = (a * a) % mod;
        n >>= 1;
    }
    return res;
}
ll sqrtll(ll x) {
    assert(x >= 0);
    ll rev = sqrt(x);
    while(rev * rev > x) --rev;
    while((rev+1) * (rev+1)<=x) ++rev;
    return rev;
}

// ★★★★ chmax, chmin
template <class T> inline bool chmax(T& M, const T& x) { if (M < x) { M = x; return true; } return false; }
template <class T> inline bool chmin(T& m, const T& x) { if (m > x) { m = x; return true; } return false; }

// ★★★★★ vector を直接cinできるようにする
// map, set, multiset とかを直接 cout できるようにする
template <class T, class U> inline istream& operator>>(istream& is, pair<T, U>& p);
template <class T> inline istream& operator>>(istream& is, vector<T>& v);
template <class T, class U> inline ostream& operator<<(ostream& os, const pair<T, U>& p);
template <class T> inline ostream& operator<<(ostream& os, const vector<T>& v);
template <typename T, typename S> ostream &operator<<(ostream &os, const map<T, S> &mp);
template <typename T> ostream &operator<<(ostream &os, const set<T> &st);
template <typename T> ostream &operator<<(ostream &os, const multiset<T> &st);
template <typename T> ostream &operator<<(ostream &os, const unordered_set<T> &st);
template <typename T> ostream &operator<<(ostream &os, deque<T> q);
template <class T, class Container, class Compare> ostream &operator<<(ostream &os, priority_queue<T, Container, Compare> pq);

// overload operators
template <class T, class U> inline istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template <class T> inline istream& operator>>(istream& is, vector<T>& v) { repe(x, v) is >> x; return is; }
template <class T, class U> inline ostream& operator<<(ostream& os, const pair<T, U>& p) { os << p.first << " " << p.second; return os; }
template <class T> inline ostream& operator<<(ostream& os, const vector<T>& v) { rep(i, sz(v)) { os << v.at(i); if (i != sz(v) - 1) os << " "; } return os; }
template <typename T, typename S> ostream &operator<<(ostream &os, const map<T, S> &mp) { for (auto &[key, val] : mp) { os << key << ":" << val << " "; } return os; }
template <typename T> ostream &operator<<(ostream &os, const set<T> &st) { auto itr = st.begin(); for (int i = 0; i < (int)st.size(); i++) { os << *itr << (i + 1 != (int)st.size() ? " " : ""); itr++; } return os; }
template <typename T> ostream &operator<<(ostream &os, const multiset<T> &st) { auto itr = st.begin(); for (int i = 0; i < (int)st.size(); i++) { os << *itr << (i + 1 != (int)st.size() ? " " : ""); itr++; } return os; }
template <typename T> ostream &operator<<(ostream &os, const unordered_set<T> &st) { ll cnt = 0; for (auto &e : st) { os << e << (++cnt != (int)st.size() ? " " : ""); } return os; }
template <typename T> ostream &operator<<(ostream &os, deque<T> q) { while (q.size()) { os << q.front(); q.pop_front(); if (q.size()) os << " "; } return os; }
template <class T, class Container, class Compare> ostream &operator<<(ostream &os, priority_queue<T, Container, Compare> pq) { while (pq.size()) { os << pq.top() << " "; pq.pop(); } return os; }
#define out(x) cout << x << endl
#define dout(x) cout << fixed << setprecision(10) << x << endl