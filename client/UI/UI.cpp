//29.05.2021

#include "UI.h"
#include "../../parser/Parser.h"
#include <iostream>

using namespace std;

//TODO: read by char not by line

UI::UI(Client client): client(client) {
    ;
};

void UI::get_request() {
    getline(cin, request);
}


bool UI::handle_request() {
    cout << "Request: " << request << endl;
    parser.init(request);
    if (parser.parse_request() == nullptr) {
        cout << "Client error" << endl;
        cout << "221 Tried to send incorrect request" << endl;
        return true;
    }
    client.send(request.c_str());
    return handle_response();
}

bool UI::handle_response() {
    string message = client.receive();
    cout << "Response: " << message << endl;
    parser.init(message);
    unique_ptr<Response> response = parser.parse_response();
    if (response == nullptr) {
        cout << "Server error" << endl;
        cout << "320 Couldn't parse server response" << endl;
        return true;
    }
    if (response->getFirst() == 1) {
        cout << "Success" << endl;
        cout << response->getMessage() << endl;
        return true;
    }
    if (response->getFirst() == 2) {
        cout << "Client error" << endl;
        cout << response->getMessage() << endl;
        return true;
    }
    if (response->getFirst() == 3) {
        cout << "Server error" << endl;
        cout << response->getMessage() << endl;
        return true;
    }
    if (response->getFirst() == 4) {
        cout << response->getMessage() << endl;
        return false;
    }
    return false;
}

bool UI::help() {
    if (request != "help") {
        return false;
    }
    cout << "Date format: [DD.MM.YYYY HH::MM]" << endl;
    cout << "Login: login [login] [password]" << endl;
    cout << "Register: register [login] [password]" << endl;
    cout << "Book termin:  book [instructor's login] [date]" << endl;
    cout << "Resign from termin as instructor: resign [client's login] [date]" << endl;
    cout << "Resign from termin as client: resign [instructor's login] [date]" << endl;
    cout << "Change termin as client: modify [instructor's login] [old_date] [new_date]" << endl;
    cout << "Check my termins as instructor or client: check -mytermins" << endl;
    cout << "Check my termins with given instructor: check -instermins [instructor's login]" << endl;
    return true;
}

const string &UI::getRequest() const {
    return request;
}

void UI::setRequest(const string &request) {
    this->request = request;
}
