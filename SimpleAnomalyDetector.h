//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#ifndef ANOMALY_DETECTION_EX2_SIMPLEANOMALYDETECTOR_H
#define ANOMALY_DETECTION_EX2_SIMPLEANOMALYDETECTOR_H

#include "anomaly_detection_util.h"
#include "minCircle.h"
#include "AnomalyDetector.h"
#include <algorithm>
#include <string.h>

using std::string;

struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    Line lin_reg;
    Circle circle = Circle(Point(0, 0), 0);
    vector<Point *> point_vec;
    float corrlation;
    float threshold;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
protected:
    vector<correlatedFeatures> cf;
public:
    SimpleAnomalyDetector() = default;

    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    virtual void check_correlated(const TimeSeries &ts, vector<Point *> point_vec, float correlation, int i, int j);

    virtual float get_dev(Point point, int index);

    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }

    static correlatedFeatures
    create_correlated_features(string feature1, string feature2, float corrlation, Line lin_reg,
                               vector<Point *> point_vec);
};

#endif //ANOMALY_DETECTION_EX2_SIMPLEANOMALYDETECTOR_H
