#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

// 1-indexedなので注意
struct BIT {
 private:
  vector<int> bit;
  int N;

 public:
  BIT(int size) {
    N = size;
    bit.resize(N + 1);
  }

  // 一点更新（位置aにwを加算）
  void add(int a, int w) {
    for (int x = a; x <= N; x += x & -x) bit[x] += w;
  }

  // 1～Nの和を求める
  int sum(int a) {
    int ret = 0;
    for (int x = a; x > 0; x -= x & -x) ret += bit[x];
    return ret;
  }
};

long long calcInvNum(int n, vector<int> &v) {
  ll ret = 0;
  BIT b(n);
  for (int i = 0; i < n; i++) {
    // 自分より右側 = BITの総和 - 自分より左側
    ret += i - b.sum(v[i]);
    // 自分の位置に1を足す
    b.add(v[i], 1);
  }
  return ret;
}

// 各数における「自分より左にいるのに自分より大きい数」が転倒数
// BITを使ったO(NlogN)の転倒数計算
// https://scrapbox.io/pocala-kyopro/%E8%BB%A2%E5%80%92%E6%95%B0

int main() {
  /* input */
  int n;
  cin >> n;
  vector<int> v(n);
  rep(i, n) cin >> v[i];

  // いいサンプル
  // https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j

  /* solve */
  ll ans = calcInvNum(n, v);

  /* output */
  cout << ans << endl;

  return 0;
}