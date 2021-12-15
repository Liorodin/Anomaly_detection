//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#include "anomaly_detection_util.h"

float avg(float *x, float size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / size;
}

float var(float *x, int size) {
    float x_squared[size];
    for (int i = 0; i < size; ++i) {
        x_squared[i] = x[i] * x[i];
    }
    float mu = avg(x, size);
    float avg_x_squared = avg(x_squared, size);
    return avg_x_squared - mu * mu;
}

float cov(float *x, float *y, int size) {
    float xy[size];
    float avg_xy, avg_x, avg_y;
    for (int i = 0; i < size; ++i) {
        xy[i] = x[i] * y[i];
    }
    avg_xy = avg(xy, size);
    avg_x = avg(x, size);
    avg_y = avg(y, size);
    return avg_xy - avg_x * avg_y;
}

float pearson(float *x, float *y, int size) {
    float cov_x_y, sigma_x, sigma_y;
    cov_x_y = cov(x, y, size);
    sigma_x = sqrtf(var(x, size));
    sigma_y = sqrtf(var(y, size));
    return cov_x_y / (sigma_x * sigma_y);
}

Line linear_reg(Point **points, int size) {
    float x[size], y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float a = cov(x, y, size) / var(x, size);
    float b = avg(y, size) - a * (avg(x, size));
    return Line(a, b);
}

float dev(Point p, Point **points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}

float dev(Point p, Line l) {
    return std::fabs(l.f(p.x) - p.y);
}