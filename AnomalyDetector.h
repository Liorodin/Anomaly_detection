//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#ifndef ANOMALY_DETECTION_ANOMALYDETECTOR_H
#define ANOMALY_DETECTION_ANOMALYDETECTOR_H


#include "timeseries.h"
#include <math.h>
#include <string>

using namespace std;

class AnomalyReport {
public:
    const string description;
    const long timeStep;

    AnomalyReport(string description, long timeStep) : description(description), timeStep(timeStep) {}
};

class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries &ts) = 0;

    virtual vector<AnomalyReport> detect(const TimeSeries &ts) = 0;

    virtual ~TimeSeriesAnomalyDetector() {}
};

#endif //ANOMALY_DETECTION_ANOMALYDETECTOR_H
