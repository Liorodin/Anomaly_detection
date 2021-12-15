//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#ifndef ANOMALY_DETECTION_EX2_ANOMALY_DETECTION_UTIL_H
#define ANOMALY_DETECTION_EX2_ANOMALY_DETECTION_UTIL_H

#include <vector>
#include <cmath>

using std::vector;

// returns the variance of X and Y
float var(float *x, int size);

// returns the covariance of X and Y
float cov(float *x, float *y, int size);

// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size);

class Point {
public:
    float x, y;

    Point(float x, float y) : x(x), y(y) {}

    static float distance(Point a, Point b) {
        return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
};

class Line {
public:
    float a, b;

    Line() : a(0), b(0) {}

    Line(float a, float b) : a(a), b(b) {}

    float f(float x) const {
        return a * x + b;
    }

    static Line perpendicular_line(const Point &a, const Point &b) {
        float altitude_ab = (b.y - a.y) / (b.x - a.x);
        Point mid_ab = Point((b.x + a.x) / 2, (b.y + a.y) / 2);
        float b_ab = mid_ab.y + (1 / altitude_ab) * mid_ab.x;
        return {-1 / altitude_ab, b_ab};
    }

    static Point intersection(const Line &line1, const Line &line2) {
        float intersection_x = (line2.b - line1.b) / (line1.a - line2.a);
        return {intersection_x, line1.f(intersection_x)};
    }
};


// performs a linear regression and return s the line equation
Line linear_reg(Point **points, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size);

// returns the deviation between point p and the line
float dev(Point p, Line l);

#endif //ANOMALY_DETECTION_EX2_ANOMALY_DETECTION_UTIL_H