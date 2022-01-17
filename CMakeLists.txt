cmake_minimum_required(VERSION 3.21)
project(Anomaly_detection)

set(CMAKE_CXX_STANDARD 11)

set(Headers anomaly_detection_util.h AnomalyDetector.h SimpleAnomalyDetector.h timeseries.h commands.h CLI.h Server.h)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(Anomaly_detection anomaly_detection_util.cpp minCircle.cpp timeseries.cpp SimpleAnomalyDetector.cpp
        HybridAnomalyDetector.cpp HybridAnomalyDetector.h CLI.cpp MainTrain.cpp Server.cpp)
