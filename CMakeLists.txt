cmake_minimum_required(VERSION 3.21)
project(Anomaly_detection)

set(CMAKE_CXX_STANDARD 11)

add_executable(Anomaly_detection anomaly_detection_util.cpp anomaly_detection_util.h AnomalyDetector.h minCircle.cpp
        minCircle.h timeseries.cpp timeseries.h SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h
        HybridAnomalyDetector.cpp HybridAnomalyDetector.h MainTrain.cpp)
