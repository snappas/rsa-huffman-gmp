//
// Created by Ryan on Nov 28.
//

#ifndef GMP_RSA_HUFFMANCODE_H
#define GMP_RSA_HUFFMANCODE_H


#include "HuffmanTree.h"

class HuffmanCode {
private:
    tree_node *root;
    vector<vector<bool>> *codes;
public:
    HuffmanCode(HuffmanTree &tree);
    HuffmanCode(HuffmanTree *tree);
    string encode(string message);
    string decode(string encodedString);
};


#endif //GMP_RSA_HUFFMANCODE_H
