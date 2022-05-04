#include <gtest/gtest.h>
#include "../code/QuadTree.h"

#include <iostream>
#include <string>

using namespace std;

class test_QuadTree : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
        return;
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
        return;
	}
    
	// this function runs before every TEST_F function
	void SetUp() override {
        return;
    }

	// this function runs after every TEST_F function
	void TearDown() override {
        return;
	}
};

TEST_F(test_QuadTree, TestEmptyFunc1){
    QuadTree myobj;
    
    ASSERT_EQ(2, myobj.EmptyFunc());
}

TEST_F(test_QuadTree, TestEmptyFunc2){
    QuadTree myobj;
    
    ASSERT_EQ(3, myobj.EmptyFunc());
}
