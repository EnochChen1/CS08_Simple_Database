#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "..\..\includes\sql\sql.h"
#include "..\..\includes\table\table.h"
using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool sql_advanced(bool debug = false) {
  SQL temp("message.txt");
  // vectorstr infix = {"dep", "<", "Joe", "or", "year", "<", "Mama", "and", "year", "<", "69420", "or", "salary", "<", "265000"};
  // //dep < Joe or year < Mama and year < 69420 or salary < 265000
  // Queue<Token *> _infix_queue = conversion_to_queue_from_infix(infix); //gets an infix vector str

  //   ShuntingYard sy(_infix_queue); //creates shuntingyard object

  //   Queue<Token *> postfix = sy.postfix(); //then converts infix to postfix
  //   Queue<Token *>::Iterator it = postfix.begin();
  //   // for(; it != postfix.end(); it++) {
  //   //     cout << (*it)->token_str();
  //   // }
  //   // cout << endl;
  //   RPN reversed(postfix);  //rpn constructor
    

  return true;
}

// TEST(TEST_STUB, TestStub) {
  
//   //EXPECT_EQ(0, <your individual test functions are called here>);

// }

TEST(sql, SQsL) {
  EXPECT_EQ(1, sql_advanced(false));
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

