// #include <cmath>
// #include <iterator>
// #include <iostream>

// #include "cs225/HSLAPixel.h"
// #include "cs225/PNG.h"
// #include "Point.h"

// #include "ImageTraversal.h"

// namespace Traversals {
//   /**
//   * Calculates a metric for the difference between two pixels, used to
//   * calculate if a pixel is within a tolerance.
//   *
//   * @param p1 First pixel
//   * @param p2 Second pixel
//   * @return the difference between two HSLAPixels
//   */
//   double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
//     double h = fabs(p1.h - p2.h);
//     double s = p1.s - p2.s;
//     double l = p1.l - p2.l;

//     // Handle the case where we found the bigger angle between two hues:
//     if (h > 180) { h = 360 - h; }
//     h /= 360;

//     return sqrt( (h*h) + (s*s) + (l*l) );
//   }
  
//   /**
//   * Adds a Point for the bfs traversal to visit at some point in the future.
//   * @param work_list the structure which stores the list of points which need to be visited by the traversal
//   * @param point the point to be added
//   */
//   void bfs_add(std::deque<Point> & work_list, const Point & point) {
//     /** @todo [Part 1] */
//     work_list.push_back(point);
//   }

//   /**
//   * Adds a Point for the dfs traversal to visit at some point in the future.
//   * @param work_list the structure which stores the list of points which need to be visited by the traversal
//   * @param point the point to be added
//   */
//   void dfs_add(std::deque<Point> & work_list, const Point & point) {
//     /** @todo [Part 1] */
//     work_list.push_back(point);
//   }

//   /**
//   * Removes and returns the current Point in the bfs traversal
//   * @param work_list the structure which stores the list of points which need to be visited by the traversal
//   */
//   Point bfs_pop(std::deque<Point> & work_list) {
//     /** @todo [Part 1] */
//     Point b4pop = work_list.front(); // FIFO... first in, first out
//     work_list.pop_front();
//     return b4pop;
//   }

//   /**
//   * Removes and returns the current Point in the dfs traversal
//   * @param work_list the structure which stores the list of points which need to be visited by the traversal
//   */
//   Point dfs_pop(std::deque<Point> & work_list) {
//     /** @todo [Part 1] */
//     Point b4pop = work_list.back();
//     work_list.pop_back(); // LIFO... last in, first out
//     return b4pop;
//   }

//   /**
//   * Initializes a ImageTraversal on a given `png` image,
//   * starting at `start`, and with a given `tolerance`.
//   * @param png The image this traversal is going to traverse
//   * @param start The start point of this traversal
//   * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
//   * it will not be included in this traversal
//   * @param traversal_add a function pointer to an implemented function which takes in a reference to the work list
//   * and the point to be added
//   * @param traversal_pop a function pointer to an implemented function which takes in a reference to the work list
//   * and returns the next point to be processed in the traversal
//   */
//   ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop) {  
//     /** @todo [Part 1] */
//     start_point = start;
//     input_image = png;
//     tolerance_ = tolerance;
//     traversal_add_ = traversal_add;
//     traversal_pop_ = traversal_pop;
//   }
  
//   /**
//   * Returns an iterator for the traversal starting at the first point.
//   */
//   ImageTraversal::Iterator ImageTraversal::begin() {
//     /** @todo [Part 1] */
//     Iterator myInstance(input_image, start_point, tolerance_, traversal_add_, traversal_pop_);
//     return myInstance;
//   }

//   /**
//   * Returns an iterator for the traversal one past the end of the traversal.
//   */
//   ImageTraversal::Iterator ImageTraversal::end() { 
//     /** @todo [Part 1] */
//     return Iterator();
//   }

//   /**
//   * Default iterator constructor.
//   */
//   ImageTraversal::Iterator::Iterator() {
//     current_point = Point(-999,-999); // some end condition current_point
//   }

//   ImageTraversal::Iterator::Iterator(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop){
//     start_point = start;
//     current_point = start_point;
//     input_image = png;
//     tolerance_ = tolerance;
//     traversal_add_ = traversal_add;
//     traversal_pop_ = traversal_pop;

//     // traversal_add_(work_list, start_point); // passing in start_point to prevent const error
//   }


//   /**
//   * Iterator increment opreator.
//   *
//   * Advances the traversal of the image.
//   */
//   ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
//     /** @todo [Part 1] */

//     visited_list.push_back(current_point);

//     Point left_neighbour = Point(current_point.x - 1, current_point.y);
//     Point right_neighbour = Point(current_point.x + 1, current_point.y);
//     Point up_neighbour = Point(current_point.x, current_point.y - 1);
//     Point down_neighbour = Point(current_point.x, current_point.y + 1);

//     if (isValid(right_neighbour)){
//       traversal_add_(work_list, right_neighbour);
//     }

//     if (isValid(down_neighbour)){
//       traversal_add_(work_list, down_neighbour);
//     }
    
//     if (isValid(left_neighbour)){
//       traversal_add_(work_list, left_neighbour);
//     }

//     if (isValid(up_neighbour)){
//       traversal_add_(work_list, up_neighbour);
//     }

//     if (work_list.empty()){
//       current_point = Point(-999, -999); // set to end condition point
//     }

//     else current_point = traversal_pop_(work_list);


//     while (isVisited(current_point)){
//       if (!work_list.empty()){
//         current_point = traversal_pop_(work_list);
//       }
      
//       else current_point = Point(-999, -999);
//     }

//     return *this;
//   }

//   bool ImageTraversal::Iterator::isValid(const Point & point){
//     if (point.x < 0 || point.x >= input_image.width() || point.y < 0 || point.y >= input_image.height()) return false;

//     if (calculateDelta(input_image.getPixel(point.x, point.y), input_image.getPixel(start_point.x, start_point.y)) >= tolerance_) return false;

//     // for (auto it = visited_list.begin(); it != visited_list.end(); it++){
//     //   if (*it == point) return false;
//     // }

//     return true; 
//   }

//   bool ImageTraversal::Iterator::isVisited(const Point & point){
//         for (auto it = visited_list.begin(); it != visited_list.end(); it++){
//           if (*it == point) return true;
//         }
//       return false;
//   }

//   /**
//   * Iterator accessor opreator.
//   *
//   * Accesses the current Point in the ImageTraversal.
//   */
//   Point ImageTraversal::Iterator::operator*() {
//     /** @todo [Part 1] */
//     // Point tempCurrent = traversal_pop_(work_list);
//     // traversal_add_(work_list, tempCurrent);
//     // return tempCurrent;

//     return current_point;
//   }

//   /**
//   * Iterator inequality operator.
//   *
//   * Determines if two iterators are not equal.
//   */
//   bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
//     /** @todo [Part 1] */
//     return !(current_point == other.current_point);
//   }

// }