
#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

// Solve for intersection of lines (P1→P2) and (P3→P4).
// Returns true if they intersect in exactly one point (fills `out`).
// Returns false if lines are parallel or coincident.
bool lineLineIntersection(const Point &P1, const Point &P2,
                          const Point &P3, const Point &P4,
                          Point &out)
{
    // Represent each line in parametric form:
    //   L1: P1 + t*(P2−P1)
    //   L2: P3 + u*(P4−P3)
    //
    // We solve for t,u:
    //   P1 + t*(P2−P1) = P3 + u*(P4−P3)
    //
    // Which gives two equations:
    //   (P2.x−P1.x)*t  − (P4.x−P3.x)*u = (P3.x−P1.x)
    //   (P2.y−P1.y)*t  − (P4.y−P3.y)*u = (P3.y−P1.y)
    //
    // Solve via Cramer’s rule.

    double A1 = P2.x - P1.x;
    double B1 = P3.x - P4.x;
    double C1 = P3.x - P1.x;

    double A2 = P2.y - P1.y;
    double B2 = P3.y - P4.y;
    double C2 = P3.y - P1.y;

    double det = A1 * B2 - A2 * B1;
    if (fabs(det) < 1e-12) {
        // Lines are parallel (det≈0). Could also be coincident.
        return false;
    }

    double t = (C1 * B2 - C2 * B1) / det;

    out.x = P1.x + t * (P2.x - P1.x);
    out.y = P1.y + t * (P2.y - P1.y);
    return true;
}

int main() {
    Point A{0, 0}, B{10, 10};
    Point C{0, 10}, D{10,  0};
    Point I;
    if (lineLineIntersection(A, B, C, D, I)) {
        cout << fixed << setprecision(6)
             << "Intersect at (" << I.x << ", " << I.y << ")\n";
    } else {
        cout << "Lines are parallel or coincident.\n";
    }
    return 0;
}
