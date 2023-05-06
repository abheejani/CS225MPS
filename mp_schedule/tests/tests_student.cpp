#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "schedule.h"
#include "tests_util.h"

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {
    const V2D roster = {
        {"Math101", "John", "Mike", "Sarah", "Jessica", "Mary"},
        {"CS101", "David", "Amy", "Mary", "Jessica", "Tom"},
        {"History101", "Kim", "Nancy", "David", "Tom", "John"},
        {"Biology101", "Samantha", "Mike", "Amy", "Kim", "Sarah"},
        {"Chemistry101", "Sarah", "Nancy", "David", "Jessica", "Mike"}
    };

    std::vector<std::string> timeslots = {"9AM", "10AM", "11AM", "1PM", "2PM"};

    V2D out = schedule(roster, timeslots);

    verifySchedule(roster, out, 5);
}

TEST_CASE("schedule() Test Case 2", "[weight=2]") {
    const V2D roster = {
        {"Math101", "John", "Mike", "Sarah", "Jessica", "Mary"},
        {"CS101", "David", "Amy", "Mary", "Jessica", "Tom"},
        {"History101", "Kim", "Nancy", "David", "Tom", "John"},
        {"Biology101", "Samantha", "Mike", "Amy", "Kim", "Sarah"},
        {"Chemistry101", "Sarah", "Nancy", "David", "Jessica", "Mike"}
    };

    std::vector<std::string> timeslots = {"9AM", "10AM", "11AM", "1PM", "2PM", "3PM"};

    V2D out = schedule(roster, timeslots);

    verifySchedule(roster, out, 6);
}


