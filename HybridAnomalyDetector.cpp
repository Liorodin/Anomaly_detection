//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#include "HybridAnomalyDetector.h"

#define MIN_HYBRID_CORRLATION 0.5

HybridAnomalyDetector::HybridAnomalyDetector() = default;

HybridAnomalyDetector::~HybridAnomalyDetector() = default;

correlatedFeatures create_cf_circle(string feature1, string feature2, float corrlation, Circle circle,
                                    vector<Point *> point_vec) {
    correlatedFeatures new_cf;
    new_cf.feature1 = std::move(feature1);
    new_cf.feature2 = std::move(feature2);
    new_cf.corrlation = corrlation;
    new_cf.circle = circle;
    new_cf.point_vec = std::move(point_vec);
    new_cf.threshold = 0;
    return new_cf;
}

void HybridAnomalyDetector::check_correlated(const TimeSeries &ts, vector<Point *> point_vec, float correlation, int i,
                                             int j) {
    if (correlation > this->min_corrlation) {
        int arr_size = ts.get_features()[i].get_vec().size();
        correlatedFeatures new_cf = SimpleAnomalyDetector::create_correlated_features(ts.get_features()[i].get_name(),
                                                                                      ts.get_features()[j].get_name(),
                                                                                      correlation,
                                                                                      linear_reg(&point_vec[0],
                                                                                                 arr_size), point_vec);
        cf.push_back(new_cf);
    } else if (correlation > MIN_HYBRID_CORRLATION) {
        int arr_size = ts.get_features()[i].get_vec().size();
        correlatedFeatures new_cf = create_cf_circle(ts.get_features()[i].get_name(),
                                                     ts.get_features()[j].get_name(), correlation,
                                                     findMinCircle(&point_vec[0], arr_size),
                                                     point_vec);
        cf.push_back(new_cf);
    }

}

float HybridAnomalyDetector::get_dev(Point point, int index) {
    if (getNormalModel()[index].lin_reg.a == 0 && getNormalModel()[index].lin_reg.b == 0) {
        return Point::distance(point, getNormalModel()[index].circle.center);
    }
    return SimpleAnomalyDetector::get_dev(point, index);
}
