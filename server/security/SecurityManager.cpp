//26.05.2021

#include "SecurityManager.h"
#include <openssl/sha.h>
#include <cstring>
#include <iostream>
#include <openssl/rand.h>
#include <openssl/evp.h>

using namespace std;

void SecurityManager::hash_password(const char* input, unsigned char binary_output[], unsigned char base64_output[], int length) {
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, input, strlen(input));
    SHA512_Final(binary_output, &sha512);
    EVP_EncodeBlock(base64_output, binary_output, length);
//    unsigned char decoded[SHA512_DIGEST_LENGTH];
//    int a = EVP_DecodeBlock(decoded, base64_output, l);
}

void SecurityManager::generate_salt(unsigned char encoded_salt[], unsigned char salt[], int not_encoded_salt_length) {
    RAND_bytes(salt, not_encoded_salt_length);
    EVP_EncodeBlock(encoded_salt, salt, not_encoded_salt_length);
}

const char* SecurityManager::merge_salt_with_password(unsigned char* salt, int salt_length, string passwd) {
    string salt_string = reinterpret_cast<char*>(salt);
    passwd += salt_string;
    cout << "Merged passwd and salt: " << passwd << endl;
    return passwd.c_str();
}

void SecurityManager::encode(unsigned char output[], unsigned char input[], int length) {
    EVP_EncodeBlock(output, input, length);
}

void SecurityManager::decode(unsigned char output[], unsigned char input[], int input_length) {
    EVP_DecodeBlock(output, input, input_length);
}
