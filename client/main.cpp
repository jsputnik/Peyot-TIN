//13.05.2021
#include <iostream>
#include <string>
#include "Client.h"
#include "UI/UI.h"

using namespace std;

int main() {
    std::cout << "Start client" << std::endl;
    const char* server_address = "127.0.0.1";
    const char* server_port = "45265";
    Client client(server_address, server_port);
    client.print_server_details(); //server IP address and port client is connecting to
    client.connect_to_server();
    UI ui(client);
    long maxAttempts = 10;
    long attempt = 0;
    string request;
    getline(cin, request);
    ui.setRequest(request);
    while (ui.handleLogin() || ui.handleRegister()) {
        ++attempt;
        cout << "Attempt: " << attempt << endl;
        if (attempt > maxAttempts) {
            client.stop(); //disconnect
            return 1;
        }
    }
    client.stop();

//    while (!ui.handleLogin() && !ui.handleRegister()) {
//        ++attempt;
//        if (attempt > maxAttempts) {
//            client.stop(); //disconnect
//        }
//    }

//    string msg = "";
//    while (msg != "quit") {
//       getline(cin, msg);
//       client.send(msg.c_str());
//       cout << client.receive() << endl;
//    }
    return 0;
}

