#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;
using namespace chrono;
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
#include <atcoder/all>
using namespace atcoder;
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

static uint32_t randXor() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

int N, K;
vs originC;
ll sumScore;  // 手元でのデバッグ用

int calcScore(vs &c, vvi &cons) {
  dsu uf(N * N);

  rep(i, (int)cons.size()) {
    int p1 = cons[i][0] * N + cons[i][1];
    int p2 = cons[i][2] * N + cons[i][3];
    uf.merge(p1, p2);
  }

  // コンピュータが存在する座標を全部入れて全探索
  vpii coms;
  rep(i, N) rep(j, N) if (c[i][j] != '0' && c[i][j] != 'x')
      coms.emplace_back(i, j);

  int ret = 0;
  rep(i, (int)coms.size()) rep(j, i) {
    auto c1 = coms[i];
    auto c2 = coms[j];
    if (uf.same(c1.first * N + c1.second, c2.first * N + c2.second)) {
      ret += (c[c1.first][c1.second] == c[c2.first][c2.second]) ? 1 : -1;
    }
  }
  return max(ret, 0);
}

vvi deletePair(vvi &cons, dsu &uf, vs &c) {
  vvi ret;
  int Y = (int)cons.size();
  rep(i, Y) {
    int p1 = cons[i][0] * N + cons[i][1];
    if (uf.size(p1) >= 4) {
      ret.push_back(cons[i]);
      continue;
    }
    // 間を'0'で埋める
    if (cons[i][0] == cons[i][2]) {
      int from = cons[i][1];
      int to = cons[i][3];
      if (to < from) swap(to, from);
      if (from - to == 1) continue;
      // 隣り合っていれば消すところはない
      for (int xi = from + 1; xi < to; xi++) {
        c[cons[i][0]][xi] = '0';
      }
    } else {
      int from = cons[i][0];
      int to = cons[i][2];
      if (to < from) swap(to, from);
      if (from - to == 1) continue;  // 隣り合っていれば消すところはない
      for (int yi = from + 1; yi < to; yi++) {
        c[yi][cons[i][1]] = '0';
      }
    }
  }
  uf = dsu(N * N);
  rep(ci, (int)ret.size()) {
    int p1 = ret[ci][0] * N + ret[ci][1];
    int p2 = ret[ci][2] * N + ret[ci][3];
    uf.merge(p1, p2);
  }

  return ret;
}

vi xs = {-1, 0, 0, 1};
vi ys = {0, -1, 1, 0};
vpii decideMove(dsu &uf, char ck, map<pii, int> &invP, pii start, vs &c,
                int pidx, int maxD, int &maxChange, pii &changeP) {
  vpii changePiis;
  int dist = -1;

  queue<pair<pii, vpii>> q;
  vpii emp;
  q.emplace(start, emp);

  set<pii> visited;

  while (!q.empty()) {
    auto piis = q.front().second;
    auto p = q.front().first;
    q.pop();
    piis.emplace_back(p);
    visited.insert(p);

    if (c[p.first][p.second] != 'x') {
      rep(di, 4) {
        for (int i = 1; i < N; i++) {
          int y = p.first + ys[di] * i;
          int x = p.second + xs[di] * i;
          if (y < 0 || y == N || x < 0 || x == N) break;
          if (c[y][x] == '0') continue;
          if (c[y][x] == 'x') break;
          if (c[y][x] != ck) break;
          auto p2 = make_pair(y, x);
          if (uf.same(invP[p2], pidx)) break;
          if (chmax(maxChange, uf.size(invP[p2]))) {
            changePiis = piis, changeP = p2;
            dist = i;
          } else if (i < dist && maxChange == uf.size(invP[p2])) {
            changePiis = piis, changeP = p2;
            dist = i;
          }
          break;
        }
      }
    }
    dist = -1;
    if ((int)piis.size() < maxD) {
      rep(di, 4) {
        int y = p.first + ys[di];
        int x = p.second + xs[di];
        if (y < 0 || y == N || x < 0 || x == N) continue;
        if (maxD <= 12) {
          if (c[y][x] != '0') continue;
        } else {
          if (c[y][x] != '0' && c[y][x] != 'x') continue;
        }
        auto yx = make_pair(y, x);
        if (!visited.count(yx)) q.emplace(yx, piis);
      }
    }
  }
  return changePiis;
}

void annealing(double endTime, vvi &nowMoves, vvi &nowCons, vs &nowC,
               map<pii, int> invP, int nowMaxD, vector<vpii> points, vi &ks) {
  // 時間管理用
  auto startClock = system_clock::now();
  double time = 0.0;
  // デバッグ用
  vector<int> cntY(K);  // 数字ごとの接続本数
  int cnt = 0;
  // efficient用
  // vector<vector<double>> effifientDbg(K, vector<double>(100));
  int falthCount = 0;

  dsu uf(K * 100);
  int X = 0;
  int Y = 0;

  bool resetFlag = false;

  while (true) {
    for (int ki : ks) {
      rep(_pi, 100) {
        // int pi = randXor() % 100;
        int pi = _pi;
        cnt++;
        // 時間更新
        time = ((double)duration_cast<microseconds>(system_clock::now() -
                                                    startClock)
                    .count() *
                1e-6);
        if (time > endTime || X + Y >= K * 100) {
          debug(nowMaxD, time, cnt);
          // debug(effifientDbg);
          // debug(falthCount);
          return;
        }

        // ここまで組が小さいものはあまり寄与してないので削除する
        if (!resetFlag && X + Y >= K * 90) {
          dsu tmp(N * N);
          rep(ci, (int)nowCons.size()) {
            int p1 = nowCons[ci][0] * N + nowCons[ci][1];
            int p2 = nowCons[ci][2] * N + nowCons[ci][3];
            tmp.merge(p1, p2);
          }
          nowCons = deletePair(nowCons, tmp, nowC);
          Y = (int)nowCons.size();
          // rep(i, (int)nowCons.size()) {
          //   cntY[(char)('0' + nowC[nowCons[i][0]][nowCons[i][1]] + 1)]++;
          // }

          uf = dsu(K * 100);
          rep(ci, (int)nowCons.size()) {
            auto p1 = invP[make_pair(nowCons[ci][0], nowCons[ci][1])];
            auto p2 = invP[make_pair(nowCons[ci][2], nowCons[ci][3])];
            uf.merge(p1, p2);
          }

          resetFlag = true;
        }

        char ck = (char)('0' + ki + 1);
        // points[ki][pi]を動かす
        int pidx = ki * 100 + pi;
        // 幅優先探索して、動かすか決める
        int maxD = min(nowMaxD, K * 100 - X - Y);
        if (uf.size(pidx) != 1) {
          // どこかと繋がっているので動かしてはいけない（動かさずに繋ぐのはOK）
          maxD = 0;
        }

        int maxChange = 0;
        pii changeP;
        int nowD = (cntY[ki] <= 10 ? max(0, maxD) : maxD);
        vpii changePiis = decideMove(uf, ck, invP, points[ki][pi], nowC, pidx,
                                     nowD, maxChange, changeP);

        if (maxChange == 0) continue;
        // アドホック：どうせ余るので、効率の悪い接続はしないでおく
        {
          falthCount++;
          int plus = uf.size(pidx) + uf.size(invP[changeP]);
          plus = plus * (plus - 1) / 2;
          double efficiency = (double)plus / (int)changePiis.size();
          if (falthCount <= 1000) {
            if (cntY[ki] <= 10) {
              if (efficiency < 1) continue;
            } else if (cntY[ki] <= 20) {
              if (efficiency < 3) continue;
            } else if (cntY[ki] <= 40) {
              if (efficiency < 5) continue;
            } else if (cntY[ki] <= 60) {
              if (efficiency < 20) continue;
            } else {
              if (efficiency < 100) continue;
            }
          }

          // effifientDbg[ki][cntY[ki]] = efficiency;
        }

        // debug(pidx, maxChange, changePiis);
        //  1番いいところに移動して繋ぐ
        if (changePiis.size() > 1) {
          rep(i, (int)changePiis.size() - 1) {
            nowMoves.push_back(vi(4));
            nowMoves.back()[0] = changePiis[i].first;
            nowMoves.back()[1] = changePiis[i].second;
            nowMoves.back()[2] = changePiis[i + 1].first;
            nowMoves.back()[3] = changePiis[i + 1].second;
          }
          X += (int)changePiis.size() - 1;

          // 座標の移動
          invP.erase(points[ki][pi]);
          nowC[points[ki][pi].first][points[ki][pi].second] = '0';
          points[ki][pi].first = nowMoves.back()[2];
          points[ki][pi].second = nowMoves.back()[3];
          invP[points[ki][pi]] = pidx;
          nowC[points[ki][pi].first][points[ki][pi].second] = ck;
        }

        Y++;
        cntY[ki]++;
        nowCons.push_back(vi(4));
        nowCons.back()[0] = points[ki][pi].first;
        nowCons.back()[1] = points[ki][pi].second;
        nowCons.back()[2] = changeP.first;
        nowCons.back()[3] = changeP.second;
        uf.merge(pidx, invP[changeP]);
        // debug(pidx, invP[changeP]);
        //  接続した線をxで埋める
        if (points[ki][pi].first == changeP.first) {
          int from = points[ki][pi].second;
          int to = changeP.second;
          if (to < from) swap(to, from);
          if (from - to == 1) break;  // 隣り合っていれば消すところはない
          int y = points[ki][pi].first;
          for (int i = from + 1; i < to; i++) {
            nowC[y][i] = 'x';
          }
        } else {
          int from = points[ki][pi].first;
          int to = changeP.first;
          if (to < from) swap(to, from);
          if (from - to == 1) break;  // 隣り合っていれば消すところはない
          int x = points[ki][pi].second;
          for (int i = from + 1; i < to; i++) {
            nowC[i][x] = 'x';
          }
        }
      }
    }
    if (nowMaxD < 13) nowMaxD++;
  }
}

// 移動：movesとconsを更新する（※Xのインクリメントは行わない）
void move(int y1, int x1, int y2, int x2, vvi &moves, vs &c) {
  c[y2][x2] = c[y1][x1];
  c[y1][x1] = '0';
  moves.push_back(vi(4));
  moves.back()[0] = y1;
  moves.back()[1] = x1;
  moves.back()[2] = y2;
  moves.back()[3] = x2;
}

// x埋めとconsへの追加を行う（※unionFindやYのインクリメントは行わない）
void connect(int y1, int x1, int y2, int x2, vvi &cons, vs &c) {
  // 間を'x'で埋める
  if (y1 == y2) {
    int from = x1;
    int to = x2;
    if (to < from) swap(to, from);
    if (from - to == 1) return;  // 隣り合っていれば消すところはない
    for (int xi = from + 1; xi < to; xi++) {
      c[y1][xi] = 'x';
    }
  } else {
    int from = y1;
    int to = y2;
    if (to < from) swap(to, from);
    if (from - to == 1) return;  // 隣り合っていれば消すところはない
    for (int yi = from + 1; yi < to; yi++) {
      c[yi][x1] = 'x';
    }
  }
  // consに加える
  cons.push_back(vi(4));
  cons.back()[0] = y1;
  cons.back()[1] = x1;
  cons.back()[2] = y2;
  cons.back()[3] = x2;
  // debug用
  // debug(y1, x1, y2, x2);
}

void tryhub(vvi &cons, vs &c, vvi &moves, vvb &isHub, dsu &uf, int threshold) {
  int X = (int)moves.size();
  int Y = (int)cons.size();

  //
  rep(i, N) rep(j, N) {
    if (X + Y >= K * 100 - 1) return;
    if (c[i][j] == '0' || c[i][j] == 'x') continue;
    // とりあえず他とくっついてるやつは入れない
    if (uf.size(i * N + j) != 1) continue;

    // 隣接しているコンピュータを列挙
    map<char, vpii> mp;
    vc direct(4, 'z');
    vpii directP(4);
    char ck = c[i][j];
    rep(di, 4) {
      for (int k = 1; k < N; k++) {
        int y = i + ys[di] * k;
        int x = j + xs[di] * k;
        if (y < 0 || y == N || x < 0 || x == N) break;
        if (c[y][x] == '0') continue;
        if (c[y][x] == ck || c[y][x] == 'x') break;
        if (isHub[y][x]) break;  // 既にハブになってるやつとは繋げたくない
        pii yx = make_pair(y, x);
        mp[c[y][x]].push_back(yx);
        direct[di] = c[y][x];
        directP[di] = yx;
        break;
      }
    }
    // 移動考慮
    // 伸びるスコアと必要な操作(score, 移動先yx, 繋げる座標1, 繋げる座標2)
    vi moveCandidate(7);

    rep(di, 4) {
      int y = i + ys[di];
      int x = j + xs[di];
      if (y < 0 || y == N || x < 0 || x == N) break;
      if (c[y][x] != '0') continue;
      if (di == 0 || di == 3) {
        if (direct[1] == direct[2] && direct[1] != 'z') {
          // 横方向に移動すると改善
          int p1 = directP[1].first * N + directP[1].second;
          int p2 = directP[2].first * N + directP[2].second;
          if (uf.same(p1, p2)) continue;
          int sz1 = uf.size(p1);
          int sz2 = uf.size(p2);
          int addScore =
              (sz1 + sz2) * (sz1 + sz2 - 1) - sz1 * (sz1 - 1) - sz2 * (sz2 - 1);

          if (moveCandidate[0] > addScore) continue;
          moveCandidate[0] = addScore;
          moveCandidate[1] = y;
          moveCandidate[2] = x;
          moveCandidate[3] = directP[1].first;
          moveCandidate[4] = directP[1].second;
          moveCandidate[5] = directP[2].first;
          moveCandidate[6] = directP[2].second;
        }
      } else {
        if (direct[0] == direct[3] && direct[0] != 'z') {
          // 縦方向に移動すると改善
          int p1 = directP[0].first * N + directP[0].second;
          int p2 = directP[3].first * N + directP[3].second;
          if (uf.same(p1, p2)) continue;
          int sz1 = uf.size(p1);
          int sz2 = uf.size(p2);
          int addScore =
              (sz1 + sz2) * (sz1 + sz2 - 1) - sz1 * (sz1 - 1) - sz2 * (sz2 - 1);
          if (moveCandidate[0] > addScore) continue;
          moveCandidate[0] = addScore;
          moveCandidate[1] = y;
          moveCandidate[2] = x;
          moveCandidate[3] = directP[0].first;
          moveCandidate[4] = directP[0].second;
          moveCandidate[5] = directP[3].first;
          moveCandidate[6] = directP[3].second;
        }
      }
    }

    // どの数字のハブになるのが最善か
    int mx = 0;
    char mxChar = 'z';
    for (auto p : mp) {
      int sz = (int)p.second.size();
      if (sz <= 1) continue;

      vi sizes;
      int num = 0;

      rep(a, sz) {
        bool sameFlag = false;
        int p1 = p.second[a].first * N + p.second[a].second;
        rep(b, a) {
          int p2 = p.second[b].first * N + p.second[b].second;
          if (uf.same(p1, p2)) {
            // 既に同じ島なら繋げる意味ない
            sameFlag = true;
            break;
          }
        }
        if (sameFlag) continue;
        sizes.push_back(uf.size(p1));
        num++;
        if (X + Y + num >= K * 100) break;
      }
      if (num <= 1) continue;  // ハブにならない
      int addScore = 0;
      int sum = 0;
      for (auto v : sizes) {
        addScore -= v * (v - 1);
        sum += v;
      }
      addScore += sum * (sum - 1);
      addScore -= sum;  // ハブのペナルティ
      if (chmax(mx, addScore)) mxChar = p.first;
    }

    if (moveCandidate[0] >= mx && moveCandidate[0] > 0) {
      // 移動して繋ぐ
      X++;
      move(i, j, moveCandidate[1], moveCandidate[2], moves, c);
      Y++;
      uf.merge(moveCandidate[3] * N + moveCandidate[4],
               moveCandidate[5] * N + moveCandidate[6]);
      connect(moveCandidate[3], moveCandidate[4], moveCandidate[5],
              moveCandidate[6], cons, c);
    } else {
      // どの数字のハブにもしない
      if (mx <= threshold) break;

      isHub[i][j] = true;

      // mp[mxChar]のハブにする
      vpii ps = mp[mxChar];
      // psをsize順にソートする
      vector<pair<int, pii>> ps2;
      rep(psi, (int)ps.size()) ps2.emplace_back(
          uf.size(ps[psi].first * N + ps[psi].second), ps[psi]);
      sort(ps2.rbegin(), ps2.rend());

      rep(psi, (int)ps.size()) {
        if (uf.same(i * N + j,
                    ps2[psi].second.first * N + ps2[psi].second.second))
          continue;
        Y++;
        uf.merge(i * N + j, ps2[psi].second.first * N + ps2[psi].second.second);
        connect(i, j, ps2[psi].second.first, ps2[psi].second.second, cons, c);
        if (X + Y >= K * 100) return;
      }
    }
  }
}

void finishingPair(vvi &cons, vs &c, int X, vvb &isHub, dsu &uf) {
  int Y = (int)cons.size();

  rep(i, N) rep(j, N) {
    if (c[i][j] == '0' || c[i][j] == 'x') continue;
    if (isHub[i][j]) continue;
    char ck = c[i][j];

    rep(di, 4) {
      if (X + Y >= K * 100) return;
      for (int k = 1; k < N; k++) {
        int y = i + ys[di] * k;
        int x = j + xs[di] * k;
        if (y < 0 || y == N || x < 0 || x == N) break;
        if (c[y][x] == '0') continue;
        if (c[y][x] != ck || c[y][x] == 'x') break;
        if (isHub[y][x]) break;  // 既にハブになってるやつとは繋げたくない
        if (uf.same(i * N + j, y * N + x)) break;  // 既に繋がってるなら繋げない
        uf.merge(i * N + j, y * N + x);
        Y++;
        connect(i, j, y, x, cons, c);
        break;
      }
    }
    //
  }
}

void printOutput(vvi &moves, vvi &cons) {
  int X = (int)moves.size();
  int Y = (int)cons.size();
  cout << X << "\n";
  rep(i, X) printf("%d %d %d %d\n", moves[i][0], moves[i][1], moves[i][2],
                   moves[i][3]);
  cout << Y << "\n";
  rep(i, Y)
      printf("%d %d %d %d\n", cons[i][0], cons[i][1], cons[i][2], cons[i][3]);
}

struct Solver {
  void solve() {
    /* input */
    cin >> N >> K;
    originC.resize(N);
    rep(i, N) cin >> originC[i];

    /* solve */
    vector<vpii> points(K);
    map<pii, int> invP;

    rep(i, N) rep(j, N) {
      if (originC[i][j] != '0') {
        auto p = make_pair(i, j);
        points[originC[i][j] - '0' - 1].push_back(p);
        int v = (originC[i][j] - '0' - 1) * 100 +
                (int)points[originC[i][j] - '0' - 1].size() - 1;
        invP[p] = v;
      }
    }

    vvi bestMoves;
    vvi bestCons;
    int bestScore = 0;
    vi ds;

    int num = 6;
    double time = 0.45;
    if (K == 2) {
      num = 22;
      time = 0.12;
      rep(i, 11) {
        ds.push_back(i);
        ds.push_back(i);
      }
    } else if (K == 3) {
      if (N < 24) {
        num = 10;
        time = 0.25;
        ds.push_back(0);
        ds.push_back(0);
        ds.push_back(2);
        ds.push_back(2);
        ds.push_back(4);
        ds.push_back(4);
        ds.push_back(6);
        ds.push_back(6);
        ds.push_back(8);
        ds.push_back(8);
      } else {
        num = 15;
        time = 0.16;
        ds.push_back(0);
        ds.push_back(0);
        ds.push_back(0);
        ds.push_back(2);
        ds.push_back(2);
        ds.push_back(2);
        ds.push_back(4);
        ds.push_back(4);
        ds.push_back(4);
        ds.push_back(6);
        ds.push_back(6);
        ds.push_back(6);
        ds.push_back(8);
        ds.push_back(8);
        ds.push_back(8);
      }
    } else if (K == 4) {
      num = 10;
      time = 0.25;
      ds.push_back(0);
      ds.push_back(2);
      ds.push_back(3);
      ds.push_back(4);
      ds.push_back(5);
      ds.push_back(6);
      ds.push_back(7);
      ds.push_back(8);
      ds.push_back(9);
      ds.push_back(10);
    } else {
      ds.push_back(8);
      ds.push_back(10);
      ds.push_back(8);
      ds.push_back(10);
      ds.push_back(8);
      ds.push_back(10);
      // ds.push_back(8);
      // ds.push_back(8);
      // ds.push_back(8);
      // ds.push_back(8);
      // ds.push_back(8);
    }

    rep(i, num) {
      vvi moves;
      vvi cons;
      int nowMaxD = ds[i];
      vs c = originC;

      auto before = system_clock::now();

      auto nowT = [&] {
        double now =
            ((double)duration_cast<microseconds>(system_clock::now() - before)
                 .count() *
             1e-6);

        return now;
      };

      vi ks(K);
      rep(j, K) ks[j] = (j + i) % K;
      annealing(time, moves, cons, c, invP, nowMaxD, points, ks);


      int X = (int)moves.size();
      dsu uf(N * N);
      rep(ci, (int)cons.size()) {
        int p1 = cons[ci][0] * N + cons[ci][1];
        int p2 = cons[ci][2] * N + cons[ci][3];
        uf.merge(p1, p2);
      }
      //  ペア削除
      cons = deletePair(cons, uf, c);
      // if (X + (int)cons.size() >= K * 95) {
      //   cons = deletePair(cons, uf, c);
      // }
      // 繋げ直し
      // debug(nowT());
      vvb isHub(N, vb(N));
      // before = system_clock::now();
      tryhub(cons, c, moves, isHub, uf, 7);
      tryhub(cons, c, moves, isHub, uf, 5);
      tryhub(cons, c, moves, isHub, uf, 4);
      // debug(nowT());
      //    仕上げ
      X = (int)moves.size();
      cons = deletePair(cons, uf, c);
      finishingPair(cons, c, X, isHub, uf);

      int nowScore = calcScore(c, cons);
      if (chmax(bestScore, nowScore)) {
        bestMoves = moves;
        bestCons = cons;
      }
    }

    assert((int)bestMoves.size() + (int)bestCons.size() <= K * 100);

    // デバッグ用のスコア計算

    // nowTime =
    //     ((double)duration_cast<microseconds>(system_clock::now() -
    //     startClock)
    //          .count() *
    //      1e-6);
    // debug(nowTime);
    // printf("%d %d %.4f %.4f %.4f %.4f %.4f\n", K, N, times[0], times[1],
    //        times[2], times[3], nowTime);
    // printf("%d %d %d\n", K, N, bestScore);
    // printf("%d\n", bestScore);
    sumScore += bestScore;

    /* output */
    printOutput(bestMoves, bestCons);
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
    debug(ti);
  }

  // cout << sumScore << endl;
  return 0;
}