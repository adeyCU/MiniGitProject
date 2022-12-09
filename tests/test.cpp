// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_x, TestInsert){
    
    
    string result;
    string expected;
       
    int len = 5;
    
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    
    result = test_insert(commits, len, tabSize);
    
    expected = "0|| science(1,4,)\n1|| \n2|| \n3|| \n4|| difficult(3,)-->fun(2,)-->computer(0,)\n";
    cout << "Result: " << endl << result << endl;
    cout << "Expected: " << endl << expected << endl;
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
    len=1;
    string commits1[] = {"testing"};
    tabSize = 3;
    
    result = test_insert(commits1, len, tabSize);
    
    expected = "0|| \n1|| testing(0,)\n2|| \n";
    cout << "Result: " << endl << result << endl;
    cout << "Expected: " << endl << expected << endl;
    
    ASSERT_EQ(expected,result);
    add_points_to_grade(5);
    
    len=0;
    string commits2[] = {};
    tabSize = 2;
    
    result = test_insert(commits2, len, tabSize);
    
    expected = "0|| \n1|| \n";
    cout << "Result: " << endl << result << endl;
    cout << "Expected: " << endl << expected << endl;
    
    ASSERT_EQ(expected,result);
    add_points_to_grade(5);

}

//NOTES

TEST_F(test_x, TestSearch){
    
    
    string result;
    string expected;
    string key = "science";
       
    int len = 5;
    
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    
    result = test_search(commits, len, tabSize, key);
    
    expected = "1\n4\n";
    cout << "Key: " << key << endl;
    cout << "Print: " << endl << test_insert(commits, len, tabSize) << endl;
    cout << "Result: " << endl << result << endl;
    cout << "Expected: " << endl << expected << endl;
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    len = 10;
    
    key = "Gamma";
    string commits1[] = {"Alpha","Bravo","Gamma","Delta","Epsilon","Zeta","Eta","Theta","Iota","Gamma"};
    tabSize = 6;
    
    result = test_search(commits1, len, tabSize, key);
    
    expected = "2\n9\n";
    cout << "Key: " << key << endl;
    cout << "Print: " << endl << test_insert(commits1, len, tabSize) << endl;
    cout << "Result: " << endl << result << endl;
    cout << "Expected: " << endl << expected << endl;
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    len = 0;
    key = "N/A";
    string commits2[] = {};
    tabSize = 3;
    
    result = test_search(commits2,len,tabSize,key);
    
    expected = "";
    cout << "Key: " << key << endl;
    cout << "Print: " << endl << test_insert(commits1, len, tabSize) << endl;
    cout << "Result: " << endl << result << endl;
    cout << "Expected: " << endl << expected << endl;
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);

}

//TODO add more tests for insert. Design tests for search from hashTable.
