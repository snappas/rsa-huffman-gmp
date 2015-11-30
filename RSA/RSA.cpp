//
// Created by Ryan on Nov 26.
//

#include "RSA.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <HuffmanCode.h>

using namespace std;

RSA::RSA() {
    randstate_init();
    //buildHuffmanTree();
    englishTree = new HuffmanTree("\nABCDEFGHIJKLMNOPQRSTUVWXYZ aeiouy aeiouy abcdefghijklmnopqrstuvwxyz abcdefghijklmnopqrstuvwxyz abcdefghijklmnopqrstuvwxyz 1234567890!@#$%^&*()-=_+[{]};:'\"\\|,<.>/?`~");
    base62Tree = new HuffmanTree("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0987654321");
}

RSA::~RSA() {

}

bool RSA::randstate_init() {
    srand(time(0));
    gmp_randinit_mt(randState);
    gmp_randseed_ui(randState, rand() % INT_MAX);
    return false;
}

bool RSA::random(__mpz_struct *result, unsigned int bits) {
    mpz_urandomb(result, randState, bits);
    return false;
}



/* Function: generateKeys
 * Store:
 *  n, (private/public)
 *  e, (public)
 *  d  (private)
 */
size_t RSA::generateKeys(unsigned int bits) {
    cout << "generating key pair" << endl;
    key.bits = bits;
    mpz_t p, q, phi;
    mpz_init(p);
    mpz_init(q);
    mpz_init(phi);

    random(p, bits);
    random(q, bits);
    mpz_nextprime(p, p);
    mpz_nextprime(q, q);

    mpz_init(key.n);
    mpz_init(key.d);
    mpz_init(key.e);

    mpz_mul(key.n, p, q);

    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);


    unsigned long _e = 786433;
    while(mpz_gcd_ui(NULL, phi, _e) != 1){
        _e += 2;
    }

    mpz_set_ui(key.e, _e);
    mpz_invert(key.d, key.e, phi);

    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi);

    return mpz_size(key.n);
}

/*
 * Function: base62 encryptMessage
 * Input:
 *  string plaintext
 * Output:
 *  string ciphertext
 */
std::string RSA::b62encryptMessage(std::string plaintext) {
    cout << "encrypting message" << endl;
    mpz_t binary, message, encrypted;
    mpz_init(message);
    mpz_init(binary);
    mpz_init(encrypted);
    mpz_set_str(binary, convertTextToNumber(plaintext, englishTree).c_str(), 2);
    cout << mpz_size(binary) << endl;
    std::stringstream output;
    output << mpz_get_str(NULL, 62, binary);
    mpz_set_str(message, convertTextToNumber(output.str(), base62Tree).c_str(), 2);
    output << mpz_size(message);
    mpz_powm(encrypted, message, key.e, key.n);
    stringstream outputmessage;
    outputmessage << mpz_get_str(NULL, 62, encrypted);
    cout << mpz_size(encrypted);
    return outputmessage.str();
}
/*
 * Function: encryptMessage
 * Input:
 *  string plaintext
 * Output:
 *  string ciphertext
 */
std::string RSA::encryptMessage(std::string plaintext) {
    cout << "encrypting message" << endl;
    mpz_t message, encrypted;
    mpz_init(message);
    mpz_init(encrypted);
    mpz_set_str(message, convertTextToNumber(plaintext, englishTree).c_str(), 2);
    mpz_powm(encrypted, message, key.e, key.n);
    stringstream outputmessage;
    outputmessage << mpz_get_str(NULL, 62, encrypted);
    cout << mpz_size(encrypted);
    return outputmessage.str();
}

/*
 * Function: base62 decryptMessage
 * Input:
 *  const char* ciphertext
 * Output:
 *  const char* plaintext
 */
std::string RSA::b62decryptMessage(std::string ciphertext) {
    cout << "decrypting message" << endl;
    mpz_t encrypted, decrypted, binary;
    mpz_init(encrypted);
    mpz_init(binary);
    mpz_init(decrypted);
    mpz_set_str(encrypted, ciphertext.c_str(), 62);
    mpz_powm(decrypted, encrypted, key.d, key.n);
    std::stringstream outputbinary;
    outputbinary << mpz_get_str(NULL, 2, decrypted);
    mpz_set_str(binary, convertNumberToText(outputbinary.str(), base62Tree).c_str(), 62);
    std::stringstream output;
    output << mpz_get_str(NULL, 2, binary);
    return convertNumberToText(output.str(), englishTree);

}
/*
 * Function: decryptMessage
 * Input:
 *  const char* ciphertext
 * Output:
 *  const char* plaintext
 */
std::string RSA::decryptMessage(std::string ciphertext) {
    cout << "decrypting message" << endl;
    mpz_t encrypted, decrypted;
    mpz_init(encrypted);
    mpz_init(decrypted);
    mpz_set_str(encrypted, ciphertext.c_str(), 62);
    mpz_powm(decrypted, encrypted, key.d, key.n);
    std::stringstream output;
    output << mpz_get_str(NULL, 2, decrypted);
    return convertNumberToText(output.str(), englishTree);

}


/*
 * Function: convertTextToNumber
 * Input:
 *  string plaintext
 * Output:
 *  string huffman encoded binary representation
 */
std::string RSA::convertTextToNumber(std::string plaintext, HuffmanTree* tree){
    HuffmanCode h(tree);
    return h.encode(plaintext);
}

/*
 * Function: convertNumberToText
 * Input:
 *  string huffman encoded binary representation
 * Output:
 *  string plaintext
 */
std::string RSA::convertNumberToText(std::string huffmancode, HuffmanTree* tree) {
    HuffmanCode h(tree);
    return h.decode(huffmancode);
}

bool RSA::saveKeys(const char *path) {
    std::ofstream publicKey("key.pub", std::ofstream::out);
    if(publicKey.fail()){
        cout << "could not write public key" << endl;
        return false;
    }
    publicKey << key.bits << " " << mpz_get_str(NULL, 62, key.n) << " " << mpz_get_str(NULL, 62, key.e);
    publicKey.close();

    std::ofstream privateKey("key.priv", std::ofstream::out);
    if(privateKey.fail()){
        cout << "could not write private key" << endl;
        return false;
    }
    privateKey << key.bits << " " << mpz_get_str(NULL, 62, key.n) << " " << mpz_get_str(NULL, 62, key.d);
    privateKey.close();
    return true;
}

bool RSA::loadPublicKey(const char *path) {
    string n, e, line;
    unsigned int bits;
    mpz_init(key.n);
    mpz_init(key.e);
    std::ifstream publicKey("key.pub", std::fstream::in);
    if(publicKey.fail()){
        cout << "could not load public key" << endl;
        return false;
    }

    if(std::getline(publicKey, line)){
        istringstream iss(line);
        iss >> bits >> n >> e;

        key.bits = bits;
        mpz_set_str(key.n, n.c_str(), 62);
        mpz_set_str(key.e, e.c_str(), 62);
        publicKey.close();
        return true;
    }
    return false;
}

bool RSA::loadPrivateKey(const char* path){
    string n, d, line;
    unsigned int bits;
    mpz_init(key.d);
    mpz_init(key.n);
    std::ifstream privateKey("key.priv", std::fstream::in);
    if(privateKey.fail()){
        cout << "could not load private key" << endl;
        return false;
    }

    if(std::getline(privateKey, line)){
        istringstream iss(line);
        iss >> bits >> n >> d;

        key.bits = bits;
        mpz_set_str(key.n, n.c_str(), 62);
        mpz_set_str(key.d, d.c_str(), 62);
        privateKey.close();
        return true;
    }
    return false;
}