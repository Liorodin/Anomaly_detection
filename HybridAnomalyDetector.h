//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"

class HybridAnomalyDetector : public SimpleAnomalyDetector {

public:
    HybridAnomalyDetector();

    HybridAnomalyDetector(float corrlation) {
        this->min_corrlation = corrlation;
    }

    virtual ~HybridAnomalyDetector();

    void check_correlated(const TimeSeries &ts, vector<Point *> point_vec, float correlation, int i, int j);

    float get_dev(Point point, int i);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
