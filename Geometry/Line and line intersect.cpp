#include <bits/stdc++.h>
using namespace std;
struct Point {
    double x, y;
};

// orientation test:  
//   0 → colinear, 1 → clockwise, 2 → counterclockwise
int orientation(const Point &a, const Point &b, const Point &c) {
    double v = (b.y - a.y)*(c.x - b.x)
             - (b.x - a.x)*(c.y - b.y);
    if (fabs(v) < 1e-12) return 0;
    return (v > 0) ? 1 : 2;
}

// does point c lie on segment ab? (assumes colinearity)
bool onSegment(const Point &a, const Point &b, const Point &c) {
    return min(a.x,b.x) <= c.x && c.x <= max(a.x,b.x)
        && min(a.y,b.y) <= c.y && c.y <= max(a.y,b.y);
}

// true if segments p1q1 and p2q2 intersect
bool segmentsIntersect(const Point &p1, const Point &q1,
                       const Point &p2, const Point &q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) 
        return true;

    // special cases (colinear + on‐segment)
    if (o1 == 0 && onSegment(p1,q1,p2)) return true;
    if (o2 == 0 && onSegment(p1,q1,q2)) return true;
    if (o3 == 0 && onSegment(p2,q2,p1)) return true;
    if (o4 == 0 && onSegment(p2,q2,q1)) return true;

    return false;
}

// (optional) compute intersection point of the two infinite lines.
// returns false if parallel; otherwise fills `out` and returns true.
bool lineIntersection(const Point &A, const Point &B,
                      const Point &C, const Point &D,
                      Point &out)
{
    // Solve A + t*(B−A) = C + u*(D−C)
    double a1 = B.x - A.x, b1 = C.x - D.x, c1 = C.x - A.x;
    double a2 = B.y - A.y, b2 = C.y - D.y, c2 = C.y - A.y;
    double det = a1*b2 - a2*b1;
    if (fabs(det) < 1e-12) 
        return false;  // parallel or coincident

    double t = (c1*b2 - c2*b1) / det;
    out = { A.x + t*(B.x - A.x),  A.y + t*(B.y - A.y) };
    return true;
}
int main(){
    return 0;
}
