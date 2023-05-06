/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
using namespace std;

V2D file_to_V2D(const std::string& filename) {
    std::ifstream fileRow(filename);
    std::ifstream fileCol(filename);

    int rowCount = 0;
    int colCount = 0;

    // calculating the number of rows and columns
    std::string line;
    std::string first_line;

    while(getline(fileRow, line)){
        rowCount++;
    }
    // Creating the return vector
    V2D retVector;
    std::ifstream file(filename);

    // interate through the rows and columns to populate the 2D vector
    while (!file.eof()) {
        for(int i = 0; i < rowCount; i++){
            colCount = 0;
            std::vector<std::string> myRow;
            std::string currLine;
            getline(file, line);
            std::stringstream iss(line);
            std::getline(fileCol, first_line);
            for(char c : first_line){
                if(c == ',')
                colCount++;
            }
            colCount++; 
            for(int j = 0; j < colCount; j++){
                std::string myValue;
                getline(iss, myValue, ',');
                std::string pushVal = trim(myValue);
                myRow.push_back(pushVal);
            }
            retVector.push_back(myRow);
        }
    }
    return retVector;
}

 V2D clean(const V2D& cv, const V2D& student) {
    std::unordered_map<std::string, std::vector<std::string>> keyStudentValueClasses;
    V2D retVec;

    // copying cv into retVec because we can't alter cv
    retVec.resize(cv.size());
    for(size_t i = 0; i < cv.size(); i++){
        for(size_t j = 0; j < cv[i].size(); j++){
            retVec[i].push_back(cv[i][j]);
        }
    }

    // populating keyStudentValueClasses map
    for(size_t i = 0; i < student.size(); i++){
        std::string currStudent = student[i][0];
        std::vector<std::string> currClasses;
        for(size_t j = 1; j < student[i].size(); j++){
            currClasses.push_back(student[i][j]);
        }
        keyStudentValueClasses[currStudent] = currClasses;
        currClasses.clear();
    }

    // removing imaginary students from class roster
    for(size_t i = 0; i < retVec.size(); i++){
        for(size_t j = 1; j < retVec[i].size(); j++){
             if (keyStudentValueClasses.find(retVec[i][j]) == keyStudentValueClasses.end()){
                retVec[i].erase(retVec[i].begin() + j);
             }
        }
    }

    // If a class claims a student whose not actually in that class, remove that student 
    for(size_t i = 0; i < retVec.size(); i++){
        for(size_t j = 1; j < retVec[i].size(); j++){
            std::string myStudent = retVec[i][j];
            std::string currClass = retVec[i][0];
            std::vector<std::string> currStudentClasses = keyStudentValueClasses[myStudent];
            bool classFound = false;
            for(size_t k = 0; k < currStudentClasses.size(); k++){
                if(currStudentClasses[k] == currClass)
                    classFound = true;
            }
            if (!(classFound)){
                retVec[i].erase(retVec[i].begin() + j);
            }

        }
    }

    // remove empty classes from roster
    for(size_t i = 0; i < retVec.size(); i++){
        if(retVec[i].size() == 1 || retVec[i].size() == 0){
            retVec.erase(retVec.begin() + i);
        }
    }

    // return reworked roster 
    return retVec;
}


V2D schedule(const V2D& courses, const std::vector<std::string>& timeslots) {
    V2D nonValidVec;
    std::vector<std::string> nonValidRow;
    nonValidRow.push_back("-1");
    nonValidVec.push_back(nonValidRow);

    std::unordered_map<std::string, int> keyStudentValueOccurance;

    // populate keyStudentValueOccurance
    for (size_t i = 0; i < courses.size(); i++) {
        for (size_t j = 1; j < courses[i].size(); j++) {
            std::string currStudent = courses[i][j];
            if (keyStudentValueOccurance.find(currStudent) == keyStudentValueOccurance.end()) {
                keyStudentValueOccurance[currStudent] = 1;
            }
            else {
                keyStudentValueOccurance[currStudent] += 1;
            }
        }
    }

    // if any student appears more than the number of timeslots, return nonValid
    for (auto it = keyStudentValueOccurance.begin(); it != keyStudentValueOccurance.end(); it++) {
        size_t length = timeslots.size();
        int mysize = length;
        if ((it->second) > mysize) {
            return nonValidVec;
        }
    }

    // populate a keyStudentValueClasses map
    std::unordered_map<std::string, std::vector<std::string>> keyStudentValueClasses;
    for (auto it = keyStudentValueOccurance.begin(); it != keyStudentValueOccurance.end(); it++) {
        std::string currStudent = it->first;
        std::vector<std::string> studentClasses;
        for (size_t i = 0; i < courses.size(); i++) {
            for (size_t j = 1; j < courses[i].size(); j++) {
                std::string currClass = courses[i][0];
                if (courses[i][j] == currStudent) {
                    studentClasses.push_back(currClass);
                    break;
                }
            }
        }
        keyStudentValueClasses[currStudent] = studentClasses;
    }

    V2D validVec;

    // populate the validVec with the timeslots first
    for (size_t i = 0; i < timeslots.size(); i++) {
        std::vector<std::string> newValidRow;
        newValidRow.push_back(timeslots[i]);
        validVec.push_back(newValidRow);
    }

    // building the validVec
    std::vector<std::string> visitedClass;
    for(auto it = keyStudentValueClasses.begin(); it != keyStudentValueClasses.end(); it++){ // go thru all students
    std::string currKid = it->first;
        for(size_t i = 0; i < (it->second).size(); i++){ // go thru each class for each student 
            bool canPlace = false;
            if(visitedClass.size() == courses.size()){
                canPlace = true; 
                break;
            }
            std::string currClass = (it->second)[i];

            bool visitedClassFlag = false;
            for(size_t z = 0; z < visitedClass.size(); z++){ // if you've already visited this class, break from it
                if(currClass == visitedClass[z]){
                    visitedClassFlag = true;
                }
            }
            if(visitedClassFlag){continue;}

            // iterate through validVec
            for(size_t j = 0; j < validVec.size(); j++){ // go through each time slot
                if(!classOverlap(keyStudentValueClasses, currKid, validVec[j])){ // if the same student doesn't have another class scheduled for this timeslot
                    validVec[j].push_back(currClass); // add that class to this timeslot
                    visitedClass.push_back(currClass); // make this class offically scheduled 
                    bool thisCausesConflict = false;
                    // check all the students to see if this causes conflicts. (funny business snippet)
                        // if it does cause conflicts, this causesConflict is set to high
                    // if doescauseconflict is set to high, we remove the class from validVec and visitedClass and continue
                    for(auto it = keyStudentValueClasses.begin(); it != keyStudentValueClasses.end(); it++){
                        std::string currKid = it->first;
                            for(size_t i = 0; i < validVec.size(); i++){
                                if(countClasses(keyStudentValueClasses, currKid, validVec[i]) > 1){
                                    thisCausesConflict = true;
                                }
                        }
                    }

                    if(thisCausesConflict){
                        validVec[j].pop_back();
                        visitedClass.pop_back();
                        continue; // go to the next time slot to check
                    }
                    canPlace = true;
                    break; // move onto the next class
                }   
            }
            if(!canPlace) {
                return nonValidVec; // if every timeslot contains classes this kid already has, which shouldn't be possible, return the invalid vector
            }
        }
    } 

    // return validVec
    return validVec;
}

bool classOverlap(std::unordered_map<std::string, std::vector<std::string>> keyStudentValueClasses, const std::string currKid, const std::vector<std::string> currTimeslot){
    bool doesClassOverlap = false;
    for(size_t i = 0; i < currTimeslot.size(); i++){
        std::string currClass = currTimeslot[i];
        for(size_t j = 0; j < keyStudentValueClasses[currKid].size(); j++){
            if(keyStudentValueClasses[currKid][j] == currClass)
            doesClassOverlap = true;
        }
    }
    return doesClassOverlap;
}

int  countClasses(std::unordered_map<std::string, std::vector<std::string>> keyStudentValueClasses, const std::string currKid, const std::vector<std::string> currTimeslot){
    int numOfClasses = 0;
    for(size_t i = 0; i < currTimeslot.size(); i++){
        std::string currClass = currTimeslot[i];
        for(size_t j = 0; j < keyStudentValueClasses[currKid].size(); j++){
            if(keyStudentValueClasses[currKid][j] == currClass){numOfClasses++;}
        }
    }
    return numOfClasses;
}
