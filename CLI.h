//Leonardo Rodin 207377151
//Shirin Bazis 211492970

#ifndef CLI_H_
#define CLI_H_

#include "commands.h"

using namespace std;

class CLI {
    DefaultIO *dio;
    std::vector<Command *> commands;
    // you can add data members
public:
    CLI(DefaultIO *dio) { this->dio = dio; };

    void start();

    void add_command(Command *command) {
        commands.push_back(command);
    }

    virtual ~CLI() = default;
};


#endif /* CLI_H_ */
