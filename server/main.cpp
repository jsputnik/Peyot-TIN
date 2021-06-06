//13.05.2021
#include <iostream>
#include "Server.h"
#include "database/DBManager.h"
#include "eventLog/ELManager.h"
#include "Executor.h"
#include "database/DBScheduleManager.h"

using namespace std;

int main() {
    std::cout << "Start server" << std::endl;
    Server server;
    server.print_server_details();
//    server.log_server_details();
    server.start();
    server.stop();
    return 0;
}
