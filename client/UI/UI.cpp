//29.05.2021

#include "UI.h"
#include <iostream>

using namespace std;

//TODO: read by char not by line

UI::UI(Client client): client(client) {
    ;
};

//right now assumes login is always correct
bool UI::handleLogin() {
    cout << "Request: " << request << endl;
    //if (!isLogin(request)) return false
    //TODO: checkIfValid(request)
    client.send(request.c_str());
    string response = client.receive();
    cout << response << endl;
    //TODO: checkIfValid(response)
    //if (client.isValid(response)) return true;
    //return false;
    getline(cin, request);
    return true; //temporarily
}

//right now assumes register is always correct
bool UI::handleRegister() {
    cout << "Request: " << request << endl;
    //if (!isRegister(request)) return false
    //TODO: checkIfValid(request)
    client.send(request.c_str());
    string response = client.receive();
    cout << response << endl;
    //TODO: checkIfValid(response)
    //if (!client.isValid(response)) return false;
    //if (response.status == fail) return false;
    if (response == "150 Logged out") {
        return false;
    }
    getline(cin, request);
    return true; //temporarily
}

bool UI::handleBook() {
    cout << "Request: " << request << endl;
    //TODO: checkIfValid(request)
    if (request != "book instructor 2021-05-30T16:00") {
        return false;
    }
    client.send(request.c_str());
    string response = client.receive();
    cout << response << endl;
    //TODO: checkIfValid(response)
    //if (!client.isValid(response)) return false;
    if (response == "150 Logged out") {
        return false;
    }
    //if (response.status == fail) return false;
    getline(cin, request);
    return true;
}

const string &UI::getRequest() const {
    return request;
}

void UI::setRequest(const string &request) {
    this->request = request;
}
