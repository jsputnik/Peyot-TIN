// 26.05.2021


#ifndef PEYOT_ELMANAGER_H
#define PEYOT_ELMANAGER_H
#include <string>
#include <fstream>

class ELManager {
    std::fstream el;
public:
    ELManager(std::string el_name);
    void open(); //open file

    void save(std::string message);

    void close(); //close file
};

#endif //PEYOT_ELMANAGER_H
