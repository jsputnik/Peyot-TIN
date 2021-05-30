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
    if (request != "login") {
        return false;
    }
    cout << "bk1" << endl;
    client.send(request.c_str());
    string response = client.receive();
    cout << response << endl;
    //TODO: checkIfValid(response)
    //if (client.isValid(response)) return true;
    //return false;
    if (response == "100 Login successful") {
        cout << "Logged in successfully" << endl;
        getline(cin, request);
        return true; //temporarily
    }
    if (response == "210 Login unsuccessful") {
        cout << "Couldn't login" << endl;
        getline(cin, request);
        return false;
    }
    if (response == "400 Logged out") {
        return false;
    }
    return true; //temporarily
}

//right now assumes register is always correct
bool UI::handleRegister() {
    cout << "Request: " << request << endl;
    //if (!isRegister(request)) return false
    //TODO: checkIfValid(request)
    if (request != "register") {
        return false;
    }
    cout << "bk" << endl;
    client.send(request.c_str());
    string response = client.receive();
    cout << response << endl;
    //TODO: checkIfValid(response)
    //if (!client.isValid(response)) return false;
    if (response == "101 Registration successful") {
        cout << "Registered successfully" << endl;
        return true; //temporarily
    }
    //if (!isStatusSuccess(response)) return false;
    if (response == "400 Logged out") {
        return false;
    }
    getline(cin, request);
    return false; //temporarily
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

void UI::help() {
    cout << "Date format: [YYYY-MM-DDTHH::MM]" << endl;
    cout << "Login: login [login] [password]" << endl;
    cout << "Register: register [login] [password]" << endl;
    cout << "Book termin:  book [instructor's login] [date]" << endl;
    cout << "Resign from termin as instructor: resign [client's login] [date]" << endl;
    cout << "Resign from termin as client: resign [instructor's login] [date]" << endl;
    cout << "Change termin as client: modify [instructor's login] [date]" << endl;
    cout << "Check my termins as instructor or client: check -mytermins" << endl;
    cout << "Check my termins with given instructor: check -instermins [instructor's login]" << endl;
}

const string &UI::getRequest() const {
    return request;
}

void UI::setRequest(const string &request) {
    this->request = request;
}
