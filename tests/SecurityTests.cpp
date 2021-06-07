//Peyot
//Iwo Sokal
//30.05.2021

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../libs/catch.hpp"
#include "../server/security/SecurityManager.h"
#include <openssl/sha.h>
//#include <cstring>
//#include <iostream>
//#include <openssl/rand.h>
//#include <openssl/evp.h>

using namespace std;

TEST_CASE( "Always true" ) {
    REQUIRE(1 == 1);
}

TEST_CASE( "Same passwords and different salts => different hashes" ) {
    SecurityManager sm;
    unsigned char salt1[sm.getNotEncodedSaltLength()];
    unsigned char encoded_salt1[sm.getEncodedSaltLength()];
    unsigned char salt2[sm.getNotEncodedSaltLength()];
    unsigned char encoded_salt2[sm.getEncodedSaltLength()];
    sm.generate_salt(encoded_salt1, salt1, sm.getNotEncodedSaltLength());
    sm.generate_salt(encoded_salt2, salt2, sm.getNotEncodedSaltLength());
    unsigned char hash1[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash1[4*(SHA512_DIGEST_LENGTH+2)/3];
    unsigned char hash2[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash2[4*(SHA512_DIGEST_LENGTH+2)/3];
    sm.hash_password(SecurityManager::merge_salt_with_password(encoded_salt1, sm.getEncodedSaltLength(), "qwerty"), hash1, encoded_hash1, SHA512_DIGEST_LENGTH);
    sm.hash_password(SecurityManager::merge_salt_with_password(encoded_salt2, sm.getEncodedSaltLength(), "qwerty"), hash2, encoded_hash2, SHA512_DIGEST_LENGTH);

    string hash_string1 = reinterpret_cast<char*>(encoded_hash1);
    string hash_string2 = reinterpret_cast<char*>(encoded_hash2);
    REQUIRE(hash_string1 != hash_string2);
}

TEST_CASE( "Same passwords and same salts => same hashes" ) {
    SecurityManager sm;
    unsigned char salt[sm.getNotEncodedSaltLength()];
    unsigned char encoded_salt[sm.getEncodedSaltLength()];
    sm.generate_salt(encoded_salt, salt, sm.getNotEncodedSaltLength());
    sm.generate_salt(encoded_salt, salt, sm.getNotEncodedSaltLength());
    unsigned char hash1[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash1[4*(SHA512_DIGEST_LENGTH+2)/3];
    unsigned char hash2[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash2[4*(SHA512_DIGEST_LENGTH+2)/3];
    sm.hash_password(SecurityManager::merge_salt_with_password(encoded_salt, sm.getEncodedSaltLength(), "qwerty"), hash1, encoded_hash1, SHA512_DIGEST_LENGTH);
    sm.hash_password(SecurityManager::merge_salt_with_password(encoded_salt, sm.getEncodedSaltLength(), "qwerty"), hash2, encoded_hash2, SHA512_DIGEST_LENGTH);

    string hash_string1 = reinterpret_cast<char*>(encoded_hash1);
    string hash_string2 = reinterpret_cast<char*>(encoded_hash2);
    REQUIRE(hash_string1 == hash_string2);
}