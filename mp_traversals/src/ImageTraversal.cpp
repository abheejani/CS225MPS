#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt( (h*h) + (s*s) + (l*l) );
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    // visited[point.x][point.y] = true;
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    //visited[point.x][point.y] = true;
    work_list.push_back(point);
  }

  /**
  * Removes and returns the current Point in the bfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    Point top = work_list.front();
    work_list.pop_front();
    return top;
    //return Point(0, 0);
  }

  /**
  * Removes and returns the current Point in the dfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    Point myPoint = work_list.back();
    work_list.pop_back();
    return myPoint;
    //return Point(0, 0);
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param traversal_add a function pointer to an implemented function which takes in a reference to the work list
  * and the point to be added
  * @param traversal_pop a function pointer to an implemented function which takes in a reference to the work list
  * and returns the next point to be processed in the traversal
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop){  
    /** @todo [Part 1] */
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    traversal_add_ = traversal_add;
    traversal_pop_ = traversal_pop;
  }

  ImageTraversal::Iterator::Iterator(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop){
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    traversal_add_ = traversal_add;
    traversal_pop_ = traversal_pop;
    currPoint = start;
    end_point = Point(-800, -800);
    visited.resize(png_.width(), std::vector<bool>(png_.height(), false));
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    //Iterator myIt(png_, start_, tolerance_, traversal_add_, traversal_pop_);
    ImageTraversal::Iterator myIt(png_, start_, tolerance_, traversal_add_, traversal_pop_);
    return myIt;
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return Iterator();
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    currPoint = Point(-800,-800);
  }


  /**
  * Iterator increment opreator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */

    //myList.push_back(currPoint);
    visited[currPoint.x][currPoint.y] = true;

    Point myUp = Point(currPoint.x, currPoint.y - 1);
    Point myDown = Point(currPoint.x, currPoint.y + 1);
    Point myLeft = Point(currPoint.x - 1, currPoint.y);
    Point myRight = Point(currPoint.x + 1, currPoint.y);
    

    if(withinBounds(myRight))
      traversal_add_(work_list, myRight);
    if(withinBounds(myDown))
      traversal_add_(work_list, myDown);
    if(withinBounds(myLeft))
      traversal_add_(work_list, myLeft);
    if(withinBounds(myUp))
      traversal_add_(work_list, myUp);
    if(work_list.empty() == true)
      currPoint = Point(-800,-800);
    else{
      currPoint = traversal_pop_(work_list);
    }
    
    while(visitedPoint(currPoint)){
      if (work_list.empty() == false){
        currPoint = traversal_pop_(work_list);
      }
      else{
        currPoint = Point(-800,-800);
      }

      if (currPoint == end_point) break;
    }
    return *this;
  }

  bool ImageTraversal::Iterator::withinBounds(const Point & myP){
    if(myP.x >= 0 && myP.x < png_.width() && myP.y >= 0 && myP.y < png_.height()){
      if(calculateDelta(png_.getPixel(myP.x, myP.y), png_.getPixel(start_.x, start_.y)) < tolerance_){
        return true;
      }
    }
    return false;
  }

  bool ImageTraversal::Iterator::visitedPoint(const Point & myP){
    // bool myflag = false;
    // for (auto it = myList.begin(); it != myList.end(); it++){
    //       if (*it == myP){
    //         myflag = true;
    //         break;
    //       }
    //     }
    //   return myflag;
    if(visited[myP.x][myP.y] == true){ // thats correct right?
      return true;
    }
    else{
      return false;
    }
   }

  /**
  * Iterator accessor opreator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return currPoint;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    if(!(currPoint == other.currPoint)){
      return true;
    }
    else return false;
  }
}