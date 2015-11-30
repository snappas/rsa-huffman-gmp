//
// Created by Ryan on Nov 27.
//

#ifndef GMP_RSA_HUFFMANTREE_H
#define GMP_RSA_HUFFMANTREE_H
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>
#include "nonconst_priority_queue.h"


using namespace std;

struct tree_node{
    unique_ptr<tree_node> left, right;
    char c;
    unsigned int f;
};


class CompareNode
{
public:
    bool operator()(const unique_ptr<tree_node>& lhs,const unique_ptr<tree_node>& rhs) {
        return lhs->f > rhs->f;
    }
};



class HuffmanTree {
private:
    vector<vector<bool>>* codes;

    unique_ptr<tree_node> root;
    unordered_map<char, unsigned int> characterMap;
    nonconst_priority_queue<unique_ptr<tree_node>, vector<unique_ptr<tree_node>>, CompareNode> queue;
public:

    HuffmanTree();
    HuffmanTree(std::string corpus);
    ~HuffmanTree();
    size_t getCharacterSetSize();
    size_t getQueueSize();
    void constructCharacterSet(std::string basic_string);

    void constructPriorityQueue();

    void mergeQueue();

    unique_ptr<tree_node> extractMin();

    void buildCodes(tree_node* n, vector<bool> bits);

    tree_node* getRoot();
    void printCodes();

    vector<vector<bool>>* getCodes();
};



#endif //GMP_RSA_HUFFMANTREE_H
