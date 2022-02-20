#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

/* 幾何学的オブジェクトのまとめ */

// 点とベクトル
struct Point {
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  // ベクトルの基本演算
  Point operator+(Point &p) { return Point(x + p.x, y + p.y); }
  Point operator-(Point &p) { return Point(x - p.x, y - p.y); }
  Point operator*(double k) { return Point(x * k, y * k); }
  Point operator/(double k) { return Point(x / k, y / k); }
  // ベクトルの大きさ
  double norm() { return x * x + y * y; }
  double abs() { return sqrt(norm()); }
  // ベクトルの内積
  double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  // ベクトルの外積
  double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

  // 点の不等式（ここではx座標の大きさ。x座標が等しければy座標の大きさ）
  bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
  // 点の等式
  bool operator==(const Point &p) const {
    // fabsは小数点用の絶対値計算
    // EPSはマクロで定義した1e-10。小数点の誤差を考慮
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};
typedef Point Vector;

//線分と直線
struct Segment {
  Point p1, p2;
};
typedef Segment Line;

// 円
class Circle {
 public:
  Point c;
  double r;
  Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}
};

// 多角形
typedef vector<Point> Polygon;

int main() {
  int n;
  cin >> n;

  return 0;
}