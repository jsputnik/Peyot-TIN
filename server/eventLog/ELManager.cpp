// 26.05.2021

#include "ELManager.h"
#include <iostream>
#include <time.h>

using namespace std;

ELManager::ELManager(string el_name) {
    el.open(el_name, std::ios::in | std::ios::out | std::ios_base::app);
    if (!el.good()) {
        cerr << "Can't open file: " << el_name << endl;
    }
}

void ELManager::save(string message){
    time_t t;
    time(& t);
    string data = ctime(& t);

    data += message;

    el << data;
}

void ELManager::close() {
    el.close();
}



