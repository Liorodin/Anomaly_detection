//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#ifndef ANOMALY_DETECTION_EX2_TIMESERIES_H
#define ANOMALY_DETECTION_EX2_TIMESERIES_H

#include <fstream>
#include <iostream>
#include <iosfwd>
#include <vector>

using std::vector;
using std::string;

class feature {
    string name;
    vector<float> values;

public:
    explicit feature(string &name) : name(name) {
    }

    string get_name() const {
        return name;
    }

    void insert_value(float value) {
        values.push_back(value);
    }

    vector<float> get_vec() const {
        return values;
    }
};

class TimeSeries {
    string file_name;
    vector<feature> features;
public:
    explicit TimeSeries(const char *CSVfileName) : file_name(CSVfileName) {
        init_class();
    }

    void init_class();

    vector<feature> get_features() const {
        return features;
    }

    vector<float> get_vector_by_feature_name(const string &feature) const;
};

#endif //ANOMALY_DETECTION_EX2_TIMESERIES_H
