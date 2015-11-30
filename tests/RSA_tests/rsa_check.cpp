//
// Created by Ryan on Nov 27.
//

#include "gtest/gtest.h"
#include "RSA.h"

class RSAFixture : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        rsa = new RSA();
    }

    static void TearDownTestCase() {
        delete rsa;
        rsa = NULL;
    }

public:
//    RSAFixture() : Test() {
//        //rsa = new RSA();
//    }
//
//    virtual ~RSAFixture(){
//        //delete rsa;
//    }

    virtual void TearDown(){
    }
    virtual void SetUp(){
    }

    static RSA * rsa;
};

RSA * RSAFixture::rsa = NULL;

TEST_F(RSAFixture, generate_keys64){ //0ms
    size_t length = rsa->generateKeys(64);
    EXPECT_EQ(2, length);
}

TEST_F(RSAFixture, generate_keys128){ //1ms
    size_t length = rsa->generateKeys(128);
    EXPECT_EQ(4, length);
}

TEST_F(RSAFixture, generate_keys256){ //3ms
    size_t length = rsa->generateKeys(256);
    EXPECT_EQ(8, length);
}

TEST_F(RSAFixture, generate_keys512){ //52ms
    size_t length = rsa->generateKeys(512);
    EXPECT_EQ(16, length);
}

