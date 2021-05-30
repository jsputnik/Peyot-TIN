//26.05.2021

#ifndef PEYOT_SECURITYMANAGER_H
#define PEYOT_SECURITYMANAGER_H
#include <string>


class SecurityManager {
    int not_encoded_salt_length = 16;
    int encoded_salt_length = 4*(not_encoded_salt_length+2)/3;
public:
    void generate_salt(unsigned char encoded_salt[], unsigned char salt[], int salt_length);
    void hash_password(const char* input, unsigned char binary_output[], unsigned char base64_output[], int length);
    static const char* merge_salt_with_password(unsigned char* salt, int salt_length, std::string passwd);
    void calculate_encoded_salt_length();
    void encode(unsigned char input[], unsigned char output[], int length);
    void decode(unsigned char input[], unsigned char output[], int length);

    int getNotEncodedSaltLength() const;

    int getEncodedSaltLength() const;
};

#endif //PEYOT_SECURITYMANAGER_H
