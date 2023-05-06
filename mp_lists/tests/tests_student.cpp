#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

// TEST_CASE("My Test Case", "") {
//     bool student_wrote_test_case = false;

//     REQUIRE( student_wrote_test_case );
// }

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.



// TEST_CASE("List::reverse middle", "[weight=5][part=2]") {
//   List<int> list;
//   for(int i=1; i < 9 ; i++){
//     list.insertBack(i);
//   }
//   List<int>::ListIterator start = list.begin();
//   List<int>::ListIterator end = list.begin();
//   for(int i =0; i <2; i++){
//      ++end; //gets us to 3rd element
//   }
//   //list.insertBack(start.getPosition()->data);
//   list.reverse(start.getPosition(), *end.getPosition());

//   stringstream s1; 
//   stringstream s2;

//   list.print(s1);

//   REQUIRE( "< 9 8 7 6 5 4 3 2 1 >" == s1.str() );
// }

// TEST_CASE("List::reverseNth my test", "[weight=5][part=2]") {
//     List<int> list;
//     for(int i = 1; i <=9;i++){
//         list.insertBack(i);
//     }
//     stringstream s1;
//     stringstream s2;
//     list.print(s1);
//     list.reverseNth(3);
//     list.print(s2);
//     // REQUIRE( "< 1 2 3 >" == s1.str() );
//     // REQUIRE( "< 3 2 1 >" == s2.str() );
//     REQUIRE( "< 3 2 1 6 5 4 9 8 7 >" == s2.str() );
// }















// #include <catch2/catch_test_macros.hpp>
// #include "tests_helper.h"

// #include <algorithm>
// #include <iostream>
// #include <string>
// #include <vector>

// #include "cs225/PNG.h"
// #include "cs225/HSLAPixel.h"

// #include "List.h"

// using namespace cs225;

// // You may write your own test cases in this file to test your code.
// // Test cases in this file are not graded.

// TEST_CASE("List::reverse short", "[weight=5][part=2]") {
//   List<int> list;
//   for(int i=1; i < 10 ; i++){
//     list.insertBack(i);
//   }
//     list.reverse();

//   stringstream s1; 
//   stringstream s2;

//   list.print(s1);

//   REQUIRE( "< 9 8 7 6 5 4 3 2 1 >" == s1.str() );
// }



// TEST_CASE("List::reverse middle", "[weight=5][part=2]") {
//   List<int> list;
//   for(int i=1; i < 9 ; i++){
//     list.insertBack(i);
//   }
//   List<int>::ListIterator start = list.begin();
//   List<int>::ListIterator end = list.begin();
//   for(int i =0; i <2; i++){
//      ++end; //gets us to 3rd element
//   }
//   //list.insertBack(start.getPosition()->data);
//   list.reverse(start.getPosition(), *end.getPosition());

//   stringstream s1; 
//   stringstream s2;

//   list.print(s1);

//   REQUIRE( "< 9 8 7 6 5 4 3 2 1 >" == s1.str() );
// }

// TEST_CASE("List::reverseNth my test", "[weight=5][part=2]") {
//     List<int> list;
//     for(int i = 1; i <=9;i++){
//         list.insertBack(i);
//     }
//     stringstream s1;
//     stringstream s2;
//     list.print(s1);
//     list.reverseNth(3);
//     list.print(s2);
//     // REQUIRE( "< 1 2 3 >" == s1.str() );
//     // REQUIRE( "< 3 2 1 >" == s2.str() );
//     REQUIRE( "< 3 2 1 6 5 4 9 8 7 >" == s2.str() );
// }


// #include <catch2/catch_test_macros.hpp>
// #include "tests_helper.h"

// #include <algorithm>
// #include <iostream>
// #include <string>
// #include <vector>

// #include "cs225/PNG.h"
// #include "cs225/HSLAPixel.h"

// #include "List.h"

// using namespace cs225;

// // You may write your own test cases in this file to test your code.
// // Test cases in this file are not graded.

// TEST_CASE("List::merge short", "[weight=5][part=2]") {
//     std::cout<< "GOING INTO TEST CASE" << std::endl;

// List<int> list1;
// List<int> list2;
// list1.insertBack(1);
// list1.insertBack(3);
// list1.insertBack(4);
// list1.insertBack(6);

// list2.insertBack(2);
// list2.insertBack(5);
// list2.insertBack(7);
// list2.insertBack(9);
// list2.insertBack(10);

// cout<<"First list: "<<endl;

// for (auto it = list1.begin(); it != list1.end(); it++) {
//     cout << *it << " ";
// }

// cout<<endl;
// cout<<"Second list: "<<endl;

// for (auto it = list2.begin(); it != list2.end(); it++) {
//     cout << *it << " ";
// }

// list1.mergeWith(list2);

// cout<<endl;
// cout<<"Final list: "<<endl;

// for (auto it = list1.begin(); it != list1.end(); it++) {
//     cout << *it << " ";
// }
// cout << '\n';

// }