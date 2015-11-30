//
// Created by Ryan on Nov 27.
//

#include "gtest/gtest.h"
#include "HuffmanTree.h"
#include "HuffmanCode.h"

class HuffmanCodeFixture : public ::testing::Test {
protected:
    static void SetUpTestCase() { //shared functionality
    }
    static void TearDownTestCase() { //shared functionality
    }
public:
    virtual void TearDown(){
        //delete huffman;
        //huffman = NULL;
    }
    virtual void SetUp(){
       // huffman = new HuffmanTree("yo sup testing");
    }
    static HuffmanTree * huffman;
};

HuffmanTree *HuffmanCodeFixture::huffman = NULL;

TEST_F(HuffmanCodeFixture, test_encode){
    HuffmanTree huffmanTree("yo sup testing");
    HuffmanCode huffmanCode(huffmanTree);
    string result = huffmanCode.encode("test");
    EXPECT_EQ(result, "0111010010011");
}
TEST_F(HuffmanCodeFixture, test_decode){
    HuffmanTree huffmanTree("yo sup testing");
    HuffmanCode huffmanCode(huffmanTree);
    string result = huffmanCode.decode(huffmanCode.encode("test"));
    EXPECT_EQ(result, "test");
}




