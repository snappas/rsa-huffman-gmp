//
// Created by Ryan on Nov 28.
//

#include <sstream>
#include <iostream>
#include "HuffmanCode.h"

HuffmanCode::HuffmanCode(HuffmanTree &tree) {
    root = tree.getRoot();
    codes = tree.getCodes();
}

HuffmanCode::HuffmanCode(HuffmanTree *tree){
    root = tree->getRoot();
    codes = tree->getCodes();
}

string HuffmanCode::encode(string message) {
    stringstream ss;
    ss << 1; //encode as binary number starting with 1
    for(char c: message){
        for(auto x: codes->at(c)){
            ss << x;
        }
    }
    return ss.str();
}

string HuffmanCode::decode(string encodedString){
    string decodedString;
    tree_node* temp = root;
    encodedString.erase(encodedString.begin()); //encoded as binary number starting with 1
    for(char c: encodedString){
        if(c == '0'){
            temp = temp->left.get();
        }else{
            temp = temp->right.get();
        }
        if(temp->c){
            decodedString += temp->c;
            temp = root;
        }
    }
    return decodedString;
}
