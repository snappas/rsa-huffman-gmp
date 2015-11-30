#include <iostream>
#include <cstdio>

#include <chrono>
#include <assert.h>
#include "RSA.h"
//#include "GUI.h"


using namespace std;



int main(int argc, char** argv) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    string message;
    string text = "----------"; //510 characters for 2048 bit 1020 characters for 4096
    for(int i = 0; i<102; i++){
        message.append(text);
    }

    RSA rsa;

    bool privKey = rsa.loadPrivateKey("");
    bool pubKey = rsa.loadPublicKey("");
    if(!privKey || !pubKey) {

        rsa.generateKeys(4096);
        rsa.saveKeys("");
    }

    string encryptedMessage = rsa.encryptMessage(message);
    start = std::chrono::system_clock::now();

    string decryptedMessage = rsa.decryptMessage(encryptedMessage);
    end = std::chrono::system_clock::now();

    cout << "encrypted: " << endl;
    cout << encryptedMessage << endl;

    cout << "decrypted:" << endl;
    cout << decryptedMessage << endl;

    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "time: " << elapsed_seconds.count() << "s\n";
    return 0;
}



