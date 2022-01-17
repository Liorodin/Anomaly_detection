
#include "Server.h"


string socketIO::read() {
    char c = 0;
    string input = "";
    while (c != '\n') {
        recv(clientID, &c, 1, 0);
        if (c == '\n') {
            break;
        }
        input += c;
    }
    return input;
}

void socketIO::write(string text) {
    const char *txt = text.c_str();
    send(clientID, txt, strlen(txt), 0);
}

void socketIO::write(float f) {
    ostringstream ss;
    ss << f;
    string s(ss.str());
    write(s);
}

void socketIO::read(float *f) {}

Server::Server(int port) throw(const char *) {
    running = true;
    socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id < 0) {
        throw "socket failed";
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if (bind(socket_id, (struct sockaddr *) &server, sizeof(server)) < 0) {
        throw "bind failure";
    }

    if (listen(socket_id, 3) < 0) {
        throw "listen failure";
    }
}

void Server::start(ClientHandler &ch) throw(const char *) {
    t = new thread([&ch, this]() {
        while (running) {
            socklen_t clientSize = sizeof(client);
            int aClient = accept(socket_id, (struct sockaddr *) &client, &clientSize);
            if (aClient > 0) {
                ch.handle(aClient);
            }
        }
        close(socket_id);
    });
}

void Server::stop() {
    running = false;
    t->join(); // do not delete this!
}

Server::~Server() {
}

