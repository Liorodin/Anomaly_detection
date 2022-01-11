//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iomanip>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    // you may add additional methods here
};

class Data {
public:
    int lines;
    int positive;
    int negative;
};

class User {
public:
    float correlation = 0.9;
    string train_file = "train";
    string test_file = "test";
    vector<AnomalyReport> report;
    Data data;
};

// you may add here helper classes

// you may edit this class
class Command {
protected:
    DefaultIO *dio;
public:
    Command(DefaultIO *dio) : dio(dio) {}

    virtual void execute() = 0;

    virtual ~Command() = default;
};

class Print_menu : public Command {

public:
    Print_menu(DefaultIO *dio) : Command(dio) {}

    void execute() {
        dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n"
                   "1.upload a time series csv file\n2.algorithm settings\n"
                   "3.detect anomalies\n4.display results\n"
                   "5.upload anomalies and analyze results\n6.exit\n");
    }
};

//option 1
class Upload_ts : public Command {
    User *user;
public:
    Upload_ts(DefaultIO *dio, User *user) : Command(dio) { this->user = user; }

    void get_file(const string &name) {
        ofstream file(name);
        string line = dio->read();
        while (line != "done") {
            file << line + "\n";
            line = dio->read();
        }
        file.close();
    }

    void execute() {
        //getting train file
        dio->write("Please upload your local train CSV file.\n");
        get_file(user->train_file);
        dio->write("Upload complete.\n");
        //getting test file
        dio->write("Please upload your local test CSV file.\n");
        get_file(user->test_file);
        dio->write("Upload complete.\n");
    }
};

//option 2
class Algo_settings : public Command {
    User *user;
public:
    Algo_settings(DefaultIO *dio, User *user) : Command(dio) { this->user = user; }

    void execute() {
        dio->write("The current correlation threshold is " + to_string((double) user->correlation) + "\n");
        dio->write("Type a new threshold\n");
        string correlationS = dio->read();
        float correlation = stof(correlationS);
        while (correlation < 0 || correlation > 1) {
            dio->write("“please choose a value between 0 and 1\n");
            correlationS = dio->read();
            correlation = stof(correlationS);
        }
        user->correlation = correlation;
    }
};

//option 3
class Detect_anomalies : public Command {
    User *user;
public:
    Detect_anomalies(DefaultIO *dio, User *user) : Command(dio) { this->user = user; }

    void execute() {
        char train_file[user->train_file.length()];
        strcpy(train_file, user->train_file.c_str());
        TimeSeries train(train_file);
        char test_file[user->test_file.length()];
        strcpy(test_file, user->test_file.c_str());
        TimeSeries test(test_file);
        HybridAnomalyDetector had(user->correlation);
        had.learnNormal(train);
        this->user->report = had.detect(test);
        dio->write("anomaly detection complete.\n");
        ifstream file;
        file.open(user->test_file);
        string line;
        int lines_counter = 0;
        while (getline(file, line)) { ++lines_counter; }
        file.close();
        --lines_counter;
        this->user->data.lines = lines_counter;
        int counter = this->user->report.empty() ? 0 : 1;
        string features = user->report[0].description;
        for (AnomalyReport ap: this->user->report) {
            if (ap.description != features) {
                features = ap.description;
                counter++;
            }
        }
        this->user->data.positive = counter;
    }
};

//option 4
class Display_res : public Command {
    User *user;
public:
    Display_res(DefaultIO *dio, User *user) : Command(dio) { this->user = user; }

    void execute() {
        for (AnomalyReport ap: user->report) {
            dio->write(to_string((ap.timeStep)) + "\t" + ap.description + "\n");
        }
        dio->write("Done.\n");
    }
};

//option 5
class Upload_analyze : public Command {
    User *user;
public:
    Upload_analyze(DefaultIO *dio, User *user) : Command(dio) { this->user = user; }

    void execute() {
        Upload_ts uts(dio, user);
        dio->write("Please upload your local anomalies file.\n");
        uts.get_file("analyze");
        dio->write("Upload complete.\n");
        ifstream file;
        file.open("analyze");
        string line;
        int N_counter = 0, P = 0;
        float TP = 0, FP = 0;
        //calculate N (negative), TP, FP
        while (getline(file, line)) {
            ++P;
            int index = line.find(',');
            int start = atoi(line.substr(0, index).c_str());
            int end = atoi(line.substr(index + 1, line.length()).c_str());
            //calculate P (positive)
            int foundPerAp = 0;
            string features = user->report[0].description;
            for (AnomalyReport ap: this->user->report) {
                if (ap.description != features) {
                    features = ap.description;
                    foundPerAp = 0;
                }
                if (!foundPerAp) {
                    if (ap.timeStep >= start && ap.timeStep <= end) {
                        ++TP;
                        foundPerAp = 1;
                    }
                }
            }
            N_counter += end - start + 1;
        }
        file.close();
        this->user->data.negative = this->user->data.lines - N_counter;
        float TPR = TP / P;
        dio->write("True Positive Rate: ");
        dio->write(((int) (TPR * 1000)) / 1000.0f);
        dio->write("\n");

        float FPR = (user->data.positive - TP) / this->user->data.negative;
        dio->write("False Positive Rate: ");
        dio->write(((int) (FPR * 1000)) / 1000.0f);
        dio->write("\n");
    }
};

//option 6
class Exit_prog : public Command {
public:
    Exit_prog(DefaultIO *dio) : Command(dio) {}

    void execute() {
        std::exit(0);
    }
};


#endif /* COMMANDS_H_ */
