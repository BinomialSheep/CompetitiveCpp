#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;
// #include <atcoder/all>
// using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

struct Solver {
  void solve() {
    /* input */
    ll A, B;
    cin >> A >> B;
    if (A >= B) {
      cout << A - B << "\n";
      return;
    }
    if (A <= 2000) {
      ll X = 0;
      ll tmp = B % A;
      ll Y = (tmp == 0 ? 0 : A - tmp);
      ll ans = X + Y;
      X++;
      while (ans >= X) {
        tmp = B % (A + X);
        Y = (tmp == 0 ? 0 : A + X - tmp);
        chmin(ans, X + Y);
        X++;
      }
      cout << ans << "\n";
      return;
    }
  
    ll ans = INFTY;
    for (ll Z = 1; Z <= 1e6; Z++) {
      ll nowX, nowY;
      if (A * Z >= B) {
        nowX = 0;
        nowY = A * Z - B;
      } else {
        ll tmp = B - A * Z;
        if (tmp % Z == 0) {
          nowX = tmp / Z;
          nowY = 0;
        } else {
          nowX = tmp / Z + 1;
          nowY = (A + nowX) * Z - B;
        }
      }
      assert(nowX >= 0 && nowY >= 0);
      chmin(ans, nowX + nowY);
    }

    cout << ans << "\n";

    /* solve */

    /* output */
  }
};

int main() {
  int T;
  cin >> T;
  rep(ti, T) {
    Solver solver;
    solver.solve();
  }
  return 0;
}