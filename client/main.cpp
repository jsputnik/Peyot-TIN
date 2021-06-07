//Peyot
//Iwo Sokal, Szymon Kisiel, Olgierd Sobieraj, Illia Yatskevich
//13.05.2021

#include <iostream>
#include "Client.h"
#include "UI/UI.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "Start client" << std::endl;
    string ip_address;
    if (argc == 1) {
        cout << "Connecting to server with IP: 127.0.0.1";
        ip_address = "127.0.0.1";
    }
    else if (argc > 2) {
        cout << "Invalid usage" << endl;
        return 1;
    }
    else {
        ip_address = argv[1];
    }
    const char* server_address = ip_address.c_str();
    const char* server_port = "45265";
    Client client(server_address, server_port);
    client.print_server_details(); //server IP address and port client is connecting to
    client.connect_to_server();
    UI ui(client);
    long attempt = 0;
    ui.get_request();
    while (ui.help() || (ui.handle_request())) {
        ++attempt;
        cout << "Request " << attempt << endl;
        ui.get_request();
    }
    client.stop(0);
    return 0;
}

