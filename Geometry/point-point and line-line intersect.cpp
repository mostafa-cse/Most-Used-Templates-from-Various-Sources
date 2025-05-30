#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};
int orientation(const Point &a, const Point &b, const Point &c) {
    long long v = (b.y - a.y) * (c.x - b.x)
                - (b.x - a.x) * (c.y - b.y);
    if (v == 0) return 0;
    return (v > 0) ? 1 : 2;
}

bool onSegment(const Point &a, const Point &b, const Point &c) {
    return c.x >= min(a.x, b.x) && c.x <= max(a.x, b.x) &&
           c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y);
}

bool segmentsIntersect(const Point &p1, const Point &q1,
                       const Point &p2, const Point &q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(p1, q1, p2)) return true;
    if (o2 == 0 && onSegment(p1, q1, q2)) return true;
    if (o3 == 0 && onSegment(p2, q2, p1)) return true;
    if (o4 == 0 && onSegment(p2, q2, q1)) return true;

    return false;
}

bool pointInRect(const Point &p,
                 long long xmin, long long xmax,
                 long long ymin, long long ymax) {
    return (p.x >= xmin && p.x <= xmax &&
            p.y >= ymin && p.y <= ymax);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        Point p1, p2;
        Point r1, r2;
        cin >> p1.x >> p1.y
            >> p2.x >> p2.y
            >> r1.x >> r1.y
            >> r2.x >> r2.y;

        long long xmin = min(r1.x, r2.x);
        long long xmax = max(r1.x, r2.x);
        long long ymin = min(r1.y, r2.y);
        long long ymax = max(r1.y, r2.y);

        bool intersects = false;

        if (pointInRect(p1, xmin, xmax, ymin, ymax) ||
            pointInRect(p2, xmin, xmax, ymin, ymax)) {
            intersects = true;
        } else {
            Point topLeft     = { xmin, ymax };
            Point topRight    = { xmax, ymax };
            Point bottomLeft  = { xmin, ymin };
            Point bottomRight = { xmax, ymin };

            // top edge
            if (segmentsIntersect(p1, p2, topLeft, topRight))    intersects = true;
            // bottom edge
            if (!intersects && segmentsIntersect(p1, p2, bottomLeft, bottomRight)) intersects = true;
            // left edge
            if (!intersects && segmentsIntersect(p1, p2, topLeft, bottomLeft))      intersects = true;
            // right edge
            if (!intersects && segmentsIntersect(p1, p2, topRight, bottomRight))    intersects = true;
        }

        cout << (intersects ? 'T' : 'F') << "\n";
    }
    return 0;
}
//https://vjudge.net/problem/UVA-191
