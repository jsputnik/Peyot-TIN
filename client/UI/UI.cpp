//29.05.2021

#include "UI.h"
#include <iostream>

using namespace std;

//TODO: read by char not by line

UI::UI(Client client): client(client) {
    ;
};

bool UI::handle_request() {
    getline(cin, request);
    cout << "Request: " << request << endl;
    if (request == "help") {
        help();
        return true;
    }
    //TODO: checkIfValid(request) with parser
    client.send(request.c_str());
    return true;
}

bool UI::handle_response() {
    string response = client.receive();
    cout << "Response: " << response << endl;
    //TODO: checkIfValid(response) with parser
    //if (client.isValid(response)) return true;
    //return false;
    //
    //if (response->getFirst() == 1) return true; //success
    //if (response->getFirst() == 2) return true; //client error
    //if (response->getFirst() == 2) return true; //server error
    //if (response->getFirst() == 4) return false; //quit
    //if (response->getFirst() == 5) return true; //other

    if (response == "100 Login successful") {
        cout << "Logged in successfully" << endl;
        return true;
    }
    if (response == "240 Login unsuccessful") {
        cout << "Couldn't login" << endl;
        return true;
    }
    if (response == "220 Couldn't parse request") {
        cout << "Couldn't parse request" << endl;
        return true;
    }
    if (response == "101 Register successful") {
        cout << "Registered successfully" << endl;
        return true;
    }
    if (response == "241 Register unsuccessful") {
        cout << "Couldn't register" << endl;
        return true;
    }
    if (response == "104 Modification successful") {
        cout << "Modification successful" << endl;
        return true;
    }
    if (response == "400 Logged out") {
        return false;
    }
    return false;
}

void UI::help() {
    cout << "Date format: [DD.MM.YYYY HH::MM]" << endl;
    cout << "Login: login [login] [password]" << endl;
    cout << "Register: register [login] [password]" << endl;
    cout << "Book termin:  book [instructor's login] [date]" << endl;
    cout << "Resign from termin as instructor: resign [client's login] [date]" << endl;
    cout << "Resign from termin as client: resign [instructor's login] [date]" << endl;
    cout << "Change termin as client: modify [instructor's login] [old_date] [new_date]" << endl;
    cout << "Check my termins as instructor or client: check -mytermins" << endl;
    cout << "Check my termins with given instructor: check -instermins [instructor's login]" << endl;
}

const string &UI::getRequest() const {
    return request;
}

void UI::setRequest(const string &request) {
    this->request = request;
}
