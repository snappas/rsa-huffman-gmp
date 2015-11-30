//
// Created by Ryan on Nov 27.
//

#include "HuffmanTree.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <queue>
#include <utility>

HuffmanTree::HuffmanTree() {
    codes = new vector<vector<bool>>(255);
}

HuffmanTree::~HuffmanTree() {

}

HuffmanTree::HuffmanTree(std::string corpus) {
    codes = new vector<vector<bool>>(255);
    constructCharacterSet(corpus);
    constructPriorityQueue();
    mergeQueue();
    vector<bool> code;
    buildCodes(root.get(), code);
    //printCodes();
}

void HuffmanTree::constructCharacterSet(std::string basic_string) {
    for(char c: basic_string){
        characterMap[c] += 1;
//        if(characterMap.find(c) == characterMap.end()){
//            characterMap.insert({c, 1});
//        }else{
//            characterMap.at(c) += 1;
//        }
    }
//    std::cout << std::endl;
//    int sum = 0;
//    for(auto& x: characterMap){
//        sum += x.second;
//    }
//    cout << "sum: " << sum << endl;

}

size_t HuffmanTree::getCharacterSetSize() {
    return characterMap.size();
}

size_t HuffmanTree::getQueueSize() {
    return queue.size();
}

void HuffmanTree::constructPriorityQueue(){
    for(auto& x: characterMap){
        unique_ptr<tree_node> z(new tree_node);
        z->c = x.first;
        z->f = x.second;
        z->left = nullptr;
        z->right = nullptr;
        queue.push(move(z));
    }
}

void HuffmanTree::mergeQueue(){
    while(queue.size() != 1){
        unique_ptr<tree_node> z(new tree_node);
        z->left = extractMin();
        z->right = extractMin();
        z->f = z->left->f + z->right->f;
        queue.push(move(z));
    }
    root = extractMin();
}

unique_ptr<tree_node> HuffmanTree::extractMin(){
    if (!queue.empty()) {
        unique_ptr<tree_node> x(queue.pop_top());
        //x = ;
        return x;
    }
    return nullptr;
}


void HuffmanTree::buildCodes(tree_node* n, vector<bool> bits) {
    if(n->c){
        codes->at(n->c) = bits;
        return;
    }else{
        bits.push_back(false);
        buildCodes(n->left.get(), bits);
        bits[bits.size()-1] = true;
        buildCodes(n->right.get(), bits);
    }


}

void HuffmanTree::printCodes(){
    for(int i = 32; i<127; i++){
        //if(!codes[i].empty()){
            cout << (char)i << ": ";
            for(auto x: codes->at(i)){
                cout << x;
            }
            cout << endl;
        //}
    }
}

tree_node* HuffmanTree::getRoot() {
    return root.get();
}

vector<vector<bool>>* HuffmanTree::getCodes(){
    return codes;
}
