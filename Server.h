
#ifndef SERVER_H_
#define SERVER_H_

#include <thread>
#include "CLI.h"
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <unistd.h>

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler {
public:
    virtual void handle(int clientID) = 0;
};


// you can add helper classes here and implement on the cpp file


class socketIO : public DefaultIO {
    int clientID;
public:

    socketIO(int clientID) : clientID(clientID) {}

    virtual string read();

    virtual void write(string text);

    virtual void write(float f);

    virtual void read(float *f);

};

// implement on Server.cpp
class Server {
    int socket_id;
    sockaddr_in server;
    sockaddr_in client;
    thread *t; // the thread to run the start() method in
    volatile bool running;

public:
    Server(int port) throw(const char *);

    virtual ~Server();

    void start(ClientHandler &ch) throw(const char *);

    void stop();
};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler : public ClientHandler {
public:
    virtual void handle(int clientID) {
        socketIO socketIo(clientID);
        CLI cli(&socketIo);
        cli.start();
    }
};


#endif /* SERVER_H_ */
