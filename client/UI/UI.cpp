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
    //TODO: checkIfValid(request) with parser
    client.send(request.c_str());
    string response = client.receive();
    cout << "Response: " << response << endl;
    //TODO: checkIfValid(response) with parser
    //if (client.isValid(response)) return true;
    //return false;
    if (response == "100 Login successful") {
        cout << "Logged in successfully" << endl;
        return true; //temporarily
    }
    if (response == "210 Login unsuccessful") {
        cout << "Couldn't login" << endl;
        return true; //change
    }
    if (response == "400 Logged out") {
        return false;
    }
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
