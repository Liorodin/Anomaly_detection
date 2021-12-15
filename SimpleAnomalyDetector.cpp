//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#include <utility>
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

#define MIN_CORRLATION 0.9
#define SCALE 1.1

correlatedFeatures
SimpleAnomalyDetector::create_correlated_features(string feature1, string feature2, float corrlation, Line lin_reg,
                                                  vector<Point *> point_vec) {
    correlatedFeatures new_cf;
    new_cf.feature1 = std::move(feature1);
    new_cf.feature2 = std::move(feature2);
    new_cf.corrlation = corrlation;
    new_cf.lin_reg = lin_reg;
    new_cf.point_vec = std::move(point_vec);
    new_cf.threshold = 0;
    return new_cf;
}

void SimpleAnomalyDetector::check_correlated(const TimeSeries &ts, vector<Point *> point_vec, float correlation, int i,
                                             int j) {
    if (correlation > MIN_CORRLATION) {
        int arr_size = ts.get_features()[i].get_vec().size();
        correlatedFeatures new_cf = create_correlated_features(ts.get_features()[i].get_name(),
                                                               ts.get_features()[j].get_name(), correlation,
                                                               linear_reg(&point_vec[0], arr_size),
                                                               point_vec);
        cf.push_back(new_cf);
    }
}

float SimpleAnomalyDetector::get_dev(Point point, int index) {
    return dev(point, getNormalModel()[index].lin_reg);
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    int features_size = ts.get_features().size();
    for (int i = 0; i < features_size; i++) {
        float m = 0;
        int c = -1;
        for (int j = i + 1; j < features_size; j++) {
            float p = fabs(pearson(&ts.get_features()[i].get_vec()[0], &ts.get_features()[j].get_vec()[0],
                                   ts.get_features()[i].get_vec().size()));
            if (p > m) {
                m = p;
                c = j;
            }
        }
        if (c != -1) {
            int arr_size = ts.get_features()[i].get_vec().size();
            vector<Point *> point_vec(arr_size);
            for (int k = 0; k < arr_size; k++) {
                point_vec[k] = new Point(ts.get_features()[i].get_vec()[k], ts.get_features()[c].get_vec()[k]);
            }
            check_correlated(ts, point_vec, m, i, c);
        }
    }
    unsigned long cf_size = getNormalModel().size();
    for (int i = 0; i < cf_size; ++i) {
        float deviation = 0;
        unsigned long size = getNormalModel()[i].point_vec.size();
        for (int j = 0; j < size; ++j) {
            float temp = get_dev(*getNormalModel()[i].point_vec[j], i);
            if (temp > deviation) {
                deviation = temp;
            }
        }
        cf[i].threshold = deviation * SCALE;
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> report;
    string feature1, feature2;
    unsigned long size = getNormalModel().size();
    for (int i = 0; i < size; i++) {
        feature1 = getNormalModel()[i].feature1;
        feature2 = getNormalModel()[i].feature2;
        vector<float> vector1 = ts.get_vector_by_feature_name(feature1);
        vector<float> vector2 = ts.get_vector_by_feature_name(feature2);
        for (int j = 0; j < vector1.size(); j++) {
            float x = vector1[j], y = vector2[j];
            Point p(x, y);
            float deviation = get_dev(p, i);
            //if the deviation is bigger than the threshold, it will be reported as an anomaly
            if (deviation > getNormalModel()[i].threshold) {
                string description = feature1.append("-").append(feature2);
                AnomalyReport ap(description, j + 1);
                report.push_back(ap);
            }
        }
    }
    return report;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() noexcept {
    int model_size = getNormalModel().size();
    for (int i = 0; i < model_size; i++) {
        int vec_size = getNormalModel()[i].point_vec.size();
        for (int j = 0; j < vec_size; j++) {
            delete (getNormalModel()[i].point_vec[j]);
        }
    }
}