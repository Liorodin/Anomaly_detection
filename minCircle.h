//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

class Circle {
public:
    Point center;
    float radius;

    Circle(Point c, float r) : center(c), radius(r) {}
};

Circle findMinCircle(Point **points, size_t size);

#endif /* MINCIRCLE_H_ */
