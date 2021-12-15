//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#ifndef ANOMALY_DETECTION_EX2_ANOMALYDETECTOR_H
#define ANOMALY_DETECTION_EX2_ANOMALYDETECTOR_H

#include "timeseries.h"
#include <string>
#include <math.h>

using std::string;
using std::vector;

class AnomalyReport {
public:
    const string description;
    const long timeStep;

    AnomalyReport(const string description, const long timeStep) : description(description), timeStep(timeStep) {}
};

class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries &ts) = 0;

    virtual vector<AnomalyReport> detect(const TimeSeries &ts) = 0;

    virtual ~TimeSeriesAnomalyDetector() {}
};

#endif //ANOMALY_DETECTION_EX2_ANOMALYDETECTOR_H
