//
// Created by Ryan on Nov 26.
//

#ifndef GMP_RSA_RSA_H
#define GMP_RSA_RSA_H
#include <gmpxx.h>
#include <string>
#include <HuffmanTree.h>

class RSA {
private:
    gmp_randstate_t randState;
    bool randstate_init();
    bool random(mpz_t result, unsigned int bits);
    struct keypair{
        unsigned int bits;
        mpz_t n;
        mpz_t d;
        mpz_t e;
    } key;
    HuffmanTree *englishTree;
    HuffmanTree *base62Tree;

public:
    RSA();
    ~RSA();
    size_t generateKeys(unsigned int bits);
    bool saveKeys(const char* path);
    bool loadPublicKey(const char *path);
    bool loadPrivateKey(const char* path);
    std::string encryptMessage(std::string plaintext);
    std::string b62encryptMessage(std::string plaintext);
    std::string decryptMessage(std::string ciphertext);
    std::string b62decryptMessage(std::string ciphertext);
    std::string convertTextToNumber(std::string plaintext, HuffmanTree* tree);
    std::string convertNumberToText(std::string plaintext, HuffmanTree* tree);



};

#endif //GMP_RSA_RSA_H
