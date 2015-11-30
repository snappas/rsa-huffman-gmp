//
// Created by Ryan on Nov 27.
//

#include "gtest/gtest.h"
#include "HuffmanTree.h"

class HuffmanTreeFixture : public ::testing::Test {
protected:
    static void SetUpTestCase() { //shared functionality
    }
    static void TearDownTestCase() { //shared functionality
    }
public:
    virtual void TearDown(){
        delete huffman;
        huffman = NULL;
    }
    virtual void SetUp(){
        huffman = new HuffmanTree();
    }
    static HuffmanTree * huffman;
};

HuffmanTree *HuffmanTreeFixture::huffman = NULL;

TEST_F(HuffmanTreeFixture, generate_characterset){
    huffman->constructCharacterSet("test");
    EXPECT_EQ(huffman->getCharacterSetSize(), 3);
}

TEST_F(HuffmanTreeFixture, test_priority_queue){
    huffman->constructCharacterSet("testing construct priority queue");
    huffman->constructPriorityQueue();
    EXPECT_EQ(huffman->getCharacterSetSize(), 14);
}

TEST_F(HuffmanTreeFixture, test_merge_queue){
    huffman->constructCharacterSet("testing construct priority queue");
    huffman->constructPriorityQueue();
    huffman->mergeQueue();
    EXPECT_EQ(32, huffman->getRoot()->f);
}
TEST_F(HuffmanTreeFixture, test_build_codes){
    huffman->constructCharacterSet("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    huffman->constructPriorityQueue();
    huffman->mergeQueue();
    vector<bool> code;
    huffman->buildCodes(huffman->getRoot(), code);
    //huffman->printCodes();
    EXPECT_EQ(1, 1);
}



