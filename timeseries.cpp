//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#include "timeseries.h"

vector<float> TimeSeries::get_vector_by_feature_name(const string &feature) const {
    for (int i = 0; i < features.size(); i++) {
        //if the current feature is the feature we have accepted
        if (features[i].get_name() == feature)
            return get_features()[i].get_vec();
    }
}

void TimeSeries::init_class() {
    std::ifstream my_file;
    //opens csv file and gathers data
    my_file.open(file_name);
    string line;
    size_t position;
    //indicator of first line read
    int flag = 1;
    while (getline(my_file, line)) {
        int counter = 0;
        while ((position = line.find(',')) != string::npos) {
            string token = line.substr(0, position);
            //checks flag
            if (flag) {
                //inserts new feature object
                features.emplace_back(feature(token));
            } else {
                //inserts new value to feature's vector numbered by counter
                features[counter].insert_value(std::stof(token));
                counter++;
            }
            line.erase(0, position + 1);
        }
        //checks flag
        if (flag) {
            //inserts new feature object
            features.emplace_back(feature(line));
            //changes flag's state
            flag = 0;
        } else {
            //inserts new value to feature's vector numbered by counter
            features[counter].insert_value(std::stof(line));
        }
    }
    my_file.close();
}