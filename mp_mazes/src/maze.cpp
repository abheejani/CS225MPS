/* Your code here! */
#include "maze.h"
using namespace cs225;
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Constructor
SquareMaze::SquareMaze(){
}

// makeMaze
void SquareMaze::makeMaze(int width, int height){
    myWidth = width;
    myHeight = height;
    myCells.clear();
    djSet.addelements(width*height);

    myCells.resize(myWidth * myHeight);

    while(djSet.size(0) != myWidth*myHeight){
        int randDir = std::rand() % 2;
        int randX = std::rand() % myWidth;
        int randY = std::rand() % myHeight;
        if((randDir == 0 && randX != myWidth-1) || (randDir == 1 && randY != myHeight-1)){ // If not at border
            if(randDir == 0 && djSet.find(randY * myWidth + randX) != djSet.find(randY * myWidth + (randX+1))){ // if disjoint sets and going right
                setWall(randX, randY, 0, false);
                //myCells.at(randY * myWidth + randX).rightWall = false;
                djSet.setunion(randY * myWidth + randX, randY * myWidth + (randX+1));
            }
            if(randDir == 1 && djSet.find(randY * myWidth + randX) != djSet.find((randY+1) * myWidth + randX)){ // if disjoint set and going down
                setWall(randX, randY, 1, false);
                //myCells.at(randY * myWidth + randX).bottomWall = false;
                djSet.setunion(randY * myWidth + randX, (randY+1) * myWidth + randX);
            } 
        }
    }
}

// canTravel
bool SquareMaze::canTravel(int x, int y, int dir) const{
    if(dir == 0){
        if(x >= (myWidth-1)){// trying to go right but ur at the rightmost
            return false;
        }
        if(myCells.at(y * myWidth + x).rightWall != false){ // trying to go right but you have right wall
            return false;
        }
    }
    else if(dir == 1){
        if(y >= (myHeight-1)){ // trying to go down but you are downmost
            return false;
        }
        if(myCells.at(y * myWidth + x).bottomWall != false){ // trying to go down but you have downwall
            return false;
        }
    }
    else if(dir == 2){
        if(x <= 0){ // trying to go left but you are leftmost
            return false;
        }
        if(myCells.at(y * myWidth + (x-1)).rightWall != false){ // trying to go left but ur left dude has rightwall
            return false;
        }
    }
    else if(dir == 3){
        if(y <= 0){ // trying to go up but you are upmost
            return false;
        }
        if(myCells.at( (y-1)* myWidth + x).bottomWall != false){ // trying to go up but ur up dude has downwall
            return false;
        }
    }
    return true;
}

// setWall
void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir == 0){ 
        myCells.at(y * myHeight + x).rightWall = exists;
    }
    else if(dir == 1){ 
        myCells.at(y * myHeight + x).bottomWall = exists;
    }
}

// solveMaze
std::vector<int> SquareMaze::solveMaze(){
    std::vector<int> solution;
    // Iterate through the entire struct to basically make a vector of indeces
    for(int i = 0; i < myWidth*myHeight; i++){
        myCells.at(i).index = i;
    }

    myCells.at(0).distance = 0; // MAKING SURE MY FIRST VALUE FOR DIST IS 0
    myQueue.push(myCells.at(0).index); // pushing all indexes onto the queue
    

    while(!myQueue.empty()){
        int countDistance = myQueue.front();
        int currX = myQueue.front() % myWidth;
        int currY = myQueue.front() / myWidth;

        if(canTravel(currX, currY, 0)){
            if(myCells.at(currY * myWidth + (currX+1) ).distance == -1){
                myQueue.push(myCells.at(currY * myWidth + (currX+1)).index);
                myCells.at(currY * myWidth + (currX+1)).distance = myCells.at(currY * myWidth + (currX)).distance + 1;
            }
        }
        if(canTravel(currX, currY, 1)){
            if(myCells.at( (currY+1) * myWidth + currX).distance == -1){
                myQueue.push(myCells.at( (currY+1) * myWidth + currX).index);
                myCells.at( (currY+1) * myWidth + currX).distance = myCells.at( (currY) * myWidth + currX).distance + 1;
            }
        }
        if(canTravel(currX, currY, 2)){
            if(myCells.at(currY * myWidth + (currX-1) ).distance == -1){
                myQueue.push(myCells.at(currY * myWidth + (currX-1)).index);
                myCells.at(currY * myWidth + (currX-1)).distance = myCells.at(currY * myWidth + (currX)).distance + 1;
            }
        }
        if(canTravel(currX, currY, 3)){
            if(myCells.at( (currY-1) * myWidth + currX).distance == -1){
                myQueue.push(myCells.at( (currY-1) * myWidth + currX).index);
                myCells.at( (currY-1) * myWidth + currX).distance = myCells.at( (currY) * myWidth + currX).distance + 1;
            }
        }
        myQueue.pop();
    }

    int longest = 0;
    int x;
    for(int i = 0; i < myWidth; i++) {
        if(myCells.at( (myHeight-1)*myWidth + i).distance > longest){
            longest = myCells.at( (myHeight-1)*myWidth + i).distance;
            x = i;
        }
        if(myCells.at( (myHeight-1)*myWidth + i).distance == longest){
            continue;
        }
    }

    int currX = x;
    int currY = myHeight-1;

    while(longest != 0){
        if(canTravel(currX, currY, 0)){
            if(myCells.at(currY * myWidth + (currX+1) ).distance == myCells.at(currY * myWidth + (currX) ).distance - 1){
                solution.push_back(2);
                currX++;
            }
        }
        if(canTravel(currX, currY, 1)){
            if(myCells.at( (currY+1) * myWidth + currX).distance == myCells.at(currY * myWidth + (currX) ).distance - 1){
                solution.push_back(3);
                currY++;
            }
        }
        if(canTravel(currX, currY, 2)){
            if(myCells.at(currY * myWidth + (currX-1) ).distance == myCells.at(currY * myWidth + (currX) ).distance - 1){
                solution.push_back(0);
                currX--;
            }
        }
        if(canTravel(currX, currY, 3)){
            if(myCells.at( (currY-1) * myWidth + currX).distance == myCells.at(currY * myWidth + (currX) ).distance - 1){
                solution.push_back(1);
                currY--;
            }
        }
        longest--;
    }
    std::reverse(solution.begin(), solution.end());
    return solution;
}

// drawMaze
PNG* SquareMaze::drawMaze() const {
    // make the newImage
    cs225::PNG* newImage = new PNG(myWidth*10+1, myHeight*10+1);
    cs225::HSLAPixel blackPixel(0, 0, 0);

    // blacken top row and left column
    for(int i = 0; i < myWidth*10+1; i++)
        newImage->getPixel(0, i) = blackPixel;

    for(int i = 0; i < myHeight*10+1; i++){
        if(i < 1 || i > 9){
            newImage->getPixel(i, 0) = blackPixel;
        }
    }

    for(int coord = 0; coord < myWidth*myHeight; coord++){
        int x = coord % myWidth;
        int y = coord / myWidth;

        if(myCells.at(coord).rightWall == true){
            for(int k = 0; k <= 10; k++){
                newImage->getPixel( (x+1)*10 , y*10+k ) = blackPixel;
            }
        }
        if(myCells.at(coord).bottomWall == true){
            for(int k = 0; k <= 10; k++){
                newImage->getPixel( x*10+k , (y+1)*10 ) = blackPixel;
            }
        }
    }
    return newImage;
}

/**
    * This function calls drawMaze, then solveMaze; it modifies the PNG
    * from drawMaze to show the solution vector and the exit.
    *
    * Start at pixel (5,5). Each direction in the solution vector
    * corresponds to a trail of 11 red pixels in the given direction. If the
    * first step is downward, color pixels (5,5) through (5,15) red. (Red is
    * 0,1,0.5,1 in HSLA). Then if the second step is right, color pixels (5,15)
    * through (15,15) red. Then if the third step is up, color pixels
    * (15,15) through (15,5) red. Continue in this manner until you get to
    * the end of the solution vector, so that your output looks analogous
    * the above picture.
    *
    * Make the exit by undoing the bottom wall of the destination square:
    * call the destination maze coordinates (x,y), and whiten the pixels
    * with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
    *
    * @return a PNG of the solved SquareMaze
    */


PNG* SquareMaze::drawMazeWithSolution(){ 
    cs225::PNG* myImage = drawMaze();
    std::vector<int> mySolvedMaze = solveMaze();
    cs225::HSLAPixel red(0,1,0.5,1);
    
    int currX = 5;
    int currY = 5;

    for(size_t i = 0; i < mySolvedMaze.size(); i++){
        if(mySolvedMaze.at(i) == 0){
            for(int j = 0; j <= 10; j++){
                myImage->getPixel(currX+j, currY) = red;
            }
            currX += 10;
        }
        if(mySolvedMaze.at(i) == 1){
            for(int j = 0; j <= 10; j++){
                myImage->getPixel(currX, currY+j) = red;
            }
            currY += 10;
        }
        if(mySolvedMaze.at(i) == 2){
            for(int j = 0; j <= 10; j++){
                myImage->getPixel(currX-j, currY) = red;
            }
            currX -= 10;
        }
        if(mySolvedMaze.at(i) == 3){
            for(int j = 0; j <= 10; j++){
                myImage->getPixel(currX, currY-j) = red;
            }
            currY -= 10;
        }
    }

    int tempX = currX/10;
    int tempY = currY/10;
    for(int k = 1; k < 10; k++){
        myImage->getPixel(tempX*10+k,(tempY+1)*10).l = 1;
    }
    return myImage;
}
