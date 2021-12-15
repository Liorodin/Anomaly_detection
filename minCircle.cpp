//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#include "minCircle.h"

/**
 * @param circle the circle which we want to find out if the point is in it
 * @param a the tested point
 * @return 1 is the point is in the circle, 0 otherwise
 */
bool is_in_circle(const Circle &circle, const Point &a) {
    float distance_from_circle = Point::distance(circle.center, a);
    if (distance_from_circle > circle.radius) {
        return false;
    }
    return true;
}

/**
 * @param p_vec set of input points
 * @param circle the circle which we want to find out if the points are in it
 * @return 1 if all the points in the set are in it, 0 otherwise
 */
bool does_circle_contains_all(const vector<Point> &p_vec, const Circle &circle) {
    for (Point point: p_vec) {
        if (!(is_in_circle(circle, point))) {
            return false;
        }
    }
    return true;
}

/**
 * @param a 1st point
 * @param b 2nd point
 * @return the minimal circle containing both points
 */
Circle makeCircle(const Point &a, const Point &b) {
    Point center = Point((a.x + b.x) / 2, (a.y + b.y) / 2);
    return {center, Point::distance(a, center)};
}

/**
 * @param a 1st point
 * @param b 2nd point
 * @param c 3rd point
 * @return the minimal circle containing all three points
 */
Circle makeCircle(const Point &a, const Point &b, const Point &c) {
    Line perpendicular_ab = Line::perpendicular_line(a, b);
    Line perpendicular_ac = Line::perpendicular_line(a, c);
    Point center = Line::intersection(perpendicular_ab, perpendicular_ac);
    return {center, Point::distance(a, center)};
}

/**
 * @param p_vec set of input points
 * @return returns the minimal circle for set size up to 3
 */
Circle trivial_min_circle(const vector<Point> &p_vec) {
    if (p_vec.empty()) {
        return {Point(0, 0), 0};
    } else if (p_vec.size() == 1) {
        return {p_vec[0], 0};
    } else if (p_vec.size() == 2) {
        return makeCircle(p_vec[0], p_vec[1]);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle center = makeCircle(p_vec[i], p_vec[j]);
            if (does_circle_contains_all(p_vec, center))
                return center;
        }
    }
    return makeCircle(p_vec[0], p_vec[1], p_vec[2]);
}

/**
 * @param p_vec set of input points
 * @param R set of input points
 * @param size represents the number of points in p_vec
 * @return the MEC using Welzl's algorithm.
 */
Circle helper(vector<Point> &p_vec, vector<Point> R, size_t size) {
    // Base case when all points processed or |R| = 3
    if (size == 0 || R.size() == 3) {
        return trivial_min_circle(R);
    }
    Point p = p_vec[size - 1];

    // Get the MEC circle d from the
    // set of points p_vec - {p}
    Circle temp = helper(p_vec, R, size - 1);

    // If d contains p, return d
    if (is_in_circle(temp, p)) {
        return temp;
    }

    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for p_vec - {p} and R U {p}
    return helper(p_vec, R, size - 1);
}

/**
 * @param points set of input points
 * @param size size of the set
 * @return the minimal circle containing all the points from the set
 */
Circle findMinCircle(Point **points, size_t size) {
    vector<Point> p_vec;
    p_vec.reserve(size);
    for (int i = 0; i < size; i++) {
        p_vec.push_back(*points[i]);
    }
    return helper(p_vec, {}, size);
}
