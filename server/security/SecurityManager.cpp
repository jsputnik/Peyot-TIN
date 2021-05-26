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
    int l = EVP_EncodeBlock(base64_output, binary_output, length);
    cout << "Hashed: " << endl;
    for (unsigned int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        cout << binary_output[i];
    }
    cout << endl;
    cout << "Encoded in base64: " << endl;
    for (unsigned int i = 0; i < l; ++i) {
        cout << base64_output[i];
    }
    cout << endl;
    unsigned char decoded[SHA512_DIGEST_LENGTH];
    EVP_DecodeBlock(decoded, base64_output, l);
    cout << "Decoded from base64: " << endl;
    for (unsigned int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        cout << decoded[i];
    }
    cout << endl;
}

void SecurityManager::generate_salt(unsigned char encoded_salt[], int salt_length) {
    unsigned char salt[16];    //32 is just an example
    RAND_bytes(salt, 16);
    cout << "Hashed salt: " << endl;
    for (unsigned int i = 0; i < 16; ++i) {
        cout << salt[i];
    }
    cout << endl;
//    unsigned char encoded_salt[4*(16+2)/3];
    int l = EVP_EncodeBlock(encoded_salt, salt, 16);
    cout << "Encoded salt: " << endl;
    for (unsigned int i = 0; i < l; ++i) {
        cout << encoded_salt[i];
    }
    cout << endl;
}

const char* SecurityManager::merge_salt_with_password(unsigned char salt[], int salt_length, string passwd) {
    for (int i = 0; i < salt_length; ++i) {
        passwd += salt[i];
    }
    cout << "Merged hash: " << passwd << endl;
    return passwd.c_str();
}

void SecurityManager::encode(unsigned char input[], unsigned char output[], int length) {
    EVP_EncodeBlock(output, input, length);
}

void SecurityManager::decode(unsigned char input[], unsigned char output[], int length) {
    EVP_DecodeBlock(output, input, length);
}
