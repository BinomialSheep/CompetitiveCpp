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
    int N;
    cin >> N;
    vi p(N);
    rep(i, N) cin >> p[i];

    /* solve */
    vi zeros(N);
    vi maxs(N);

    rep(i, N) {
      int tmp = (i + N - p[i]) % N;
      zeros[tmp]++;
      maxs[(tmp + N / 2) % N];
    }
    // debug(zeros);

    ll ans = 0;
    int plus = 0, m = 0;
    int same = 0;
    rep(i, N) {
      //
      int tmp = (p[i] + N - i) % N;
      if (tmp > N - tmp) {
        m++;
      } else if (tmp == N - tmp) {
        if (N % 2) {
          //int tmp2 = (p[(i + 1) % N] + N - (i + 1)) % N;
          if () {
            same++;
          } else {
            m++;
          }
        } else {
          m++;
        }
      } else {
        plus++;
      }
      ans += min(tmp, N - tmp);
    }
    // debug("init", ans);

    // N回転シミュレーション
    ll now = ans;
    for (int i = 1; i < N; i++) {
      now = now + plus - m;
      chmin(ans, now);
      // debug(now, plus, m, same, zeros[i], zeros[(i + N / 2) % N]);
      debug((i + N / 2) % N, zeros[i], zeros[(i + N / 2) % N]);
      //  0で切り替え
      m -= zeros[i];
      plus += zeros[i];
      // 偶奇次第では
      if (N % 2) {
        m += same;
        same = zeros[(i + N / 2) % N];
        plus -= same;
      } else {
        m += zeros[(i + N / 2) % N];
        plus -= zeros[(i + N / 2) % N];
      }
    }

    /* output */
    cout << ans << endl;
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}