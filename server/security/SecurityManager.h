//26.05.2021

#ifndef PEYOT_SECURITYMANAGER_H
#define PEYOT_SECURITYMANAGER_H
#include <string>


class SecurityManager {
public:
    void generate_salt(unsigned char encoded_salt[], int salt_length);
    void hash_password(const char* input, unsigned char binary_output[], unsigned char base64_output[], int length);
    static const char* merge_salt_with_password(unsigned char salt[], int salt_length, std::string passwd);
    void encode(unsigned char input[], unsigned char output[], int length);
    void decode(unsigned char input[], unsigned char output[], int length);
};

#endif //PEYOT_SECURITYMANAGER_H
