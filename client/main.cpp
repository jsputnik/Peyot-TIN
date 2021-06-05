//13.05.2021
#include <iostream>
#include "Client.h"
#include "UI/UI.h"

using namespace std;

int main() {
    std::cout << "Start client" << std::endl;
    const char* server_address = "192.168.177.128";
    const char* server_port = "45265";
    Client client(server_address, server_port);
    client.print_server_details(); //server IP address and port client is connecting to
    client.connect_to_server();
    UI ui(client);
    long maxAttempts = 10;
    long attempt = 0;
    ui.get_request();
    while (ui.help() || (ui.handle_request())) {
        ++attempt;
        cout << "Attempt: " << attempt << endl;
        if (attempt > maxAttempts) {
            client.stop(1); //disconnect
            return 1;
        }
        ui.get_request();
    }
    client.stop(0);
    return 0;
}

