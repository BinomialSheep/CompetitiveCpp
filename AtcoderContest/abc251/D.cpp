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

int main() {
  /* input */
  int W;
  cin >> W;

  /* solve */
  vi ans;
  rep(i, 127) {
    // 下7桁
    ans.push_back(i + 1);
  }
  rep(i, 127) {
    //　次の7桁
    ans.push_back(128 * (i + 1));
  }
  rep(i, 61) {
    // そのあとの6桁
    // 最後2つは使わない（単体で10^6を超えるため）
    ans.push_back(128 * 128 * (i + 1));
  }

  /* output */
  cout << ans.size() << endl;
  rep(i, ans.size()) { cout << ans[i] << " "; }
  cout << endl;

  return 0;
}