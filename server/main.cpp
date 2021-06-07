//Peyot
//Iwo Sokal, Szymon Kisiel, Olgierd Sobieraj, Illia Yatskevich
//13.05.2021

#include <iostream>
#include "Server.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "Start server" << std::endl;
    string ip_address;
    if (argc == 1) {
        cout << "Initialising server with IP: 127.0.0.1" << endl;
        ip_address = "127.0.0.1";
    }
    else if (argc > 2) {
        cout << "Invalid usage" << endl;
        return 1;
    }
    else {
        ip_address = argv[1];
    }
    Server server(ip_address);
    server.print_server_details();
    server.log_server_details();
    server.start();
    server.stop();
    return 0;
}
