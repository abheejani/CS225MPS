#include "dsets.h"

void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i++) 
        myVec.push_back(-1);
}

int DisjointSets::find(int elem){
    if (myVec[elem] < 0){ // if something is negative, nothing exists at a spot
        return elem;
    }
        
    int myRoot = find(myVec[elem]);
    myVec[elem] = myRoot;
    return myRoot;
}

void DisjointSets::setunion(int a, int b){
	if (find(a) == find(b)){
        return;
    } 
	else if (myVec[find(a)] < myVec[find(b)]) { // it can be less than 
        int myTempSize = myVec[find(a)] + myVec[find(b)];
		myVec[find(b)] = find(a); 
		myVec[find(a)] = myTempSize; 
	} 
    else{ // it can also be equal (same condition as less than)
        int myTempSize = myVec[find(a)] + myVec[find(b)];
        myVec[find(b)] = find(a); 
		myVec[find(a)] = myTempSize; 
    }
}

int DisjointSets::size(int elem){
    int myRoot = find(elem);
    return -myVec[myRoot];
}
