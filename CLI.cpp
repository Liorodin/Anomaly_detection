//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#include "CLI.h"

bool is_input_valid(const string &input) {
    if ("1" <= input && input <= "6") {
        return true;
    }
    return false;
}

void CLI::start() {
    User *user = new User();
    //1st option
    add_command(new Upload_ts(this->dio, user));
    //2nd option
    add_command(new Algo_settings(this->dio, user));
    //3rd option
    add_command(new Detect_anomalies(this->dio, user));
    //4th option
    add_command(new Display_res(this->dio, user));
    //5th option
    add_command(new Upload_analyze(this->dio, user));
    //6th option
    add_command(new Exit_prog(this->dio));
    Command *print = new Print_menu(this->dio);
    print->execute();
    std::string option = dio->read();
    while (option != "6") {
        if (is_input_valid(option)) {
            commands[std::stoi(option) - 1]->execute();
        }
        print->execute();
        option = dio->read();
    }
}

