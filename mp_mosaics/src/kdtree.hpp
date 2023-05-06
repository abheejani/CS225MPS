// /**
//  * @file kdtree.cpp
//  * Implementation of KDTree class.
//  */

#include <utility>
#include <algorithm>
#include <deque>
#include <cmath>
#include <iostream>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
  /**
   * @todo Implement this function!
   */

  if(curDim<0){
    return false;
  }
  else if(curDim > Dim){
    return false;
  }
  else if(first[curDim] == second[curDim]){
    return first < second;
  }
  else{
  return first[curDim] < second[curDim];
  }
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
  int distance1 = 0;
  int distance2 = 0;

  for(int i = 0; i < Dim; i++){
    distance1 += ( (currentBest[i]-target[i]) * (currentBest[i]-target[i]) );
  }
  for(int i = 0; i < Dim; i++){
    distance2 += ( (potential[i]-target[i]) * (potential[i]-target[i]) );
  }

  if(distance1 == distance2){
    return potential < currentBest;
  }

  return  distance2 < distance1;
}


// /////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints) 
{
  if (newPoints.size() == 0 || Dim == 0) {
      root = NULL;
      return;
  }
  vector<Point<Dim>> myPoints(newPoints.size());
  size = newPoints.size();
  for (size_t i = 0; i < newPoints.size(); i++) {
    myPoints[i] = newPoints[i];
  }
  root = buildTree(myPoints, 0, myPoints.size() - 1, 0);
 }

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int left, int right, int depth)
{
  if (left > right) {
    return nullptr;
  }

  int mid = (left + right) / 2;
  int nextDim = (depth + 1) % Dim;

  auto cmp = [depth](Point<Dim> first, Point<Dim> second) {
  return smallerDimVal(first, second, depth);
 };

  select(points.begin() + left, points.begin() + right + 1, points.begin() + mid, cmp);

  KDTreeNode* node = new KDTreeNode(points[mid]);

  node->left = buildTree(points, left, mid-1, nextDim);
  node->right = buildTree(points, mid+1, right, nextDim);

  return node;
}


// //////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = other.size;
  copy(this->root, other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  if(rhs != this) {
    destroy(root);
  } 
  copy(this->root, rhs.root);
  this->size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  destroy(root);
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* node) {
  if (node == nullptr)
      return;
  if(node->left != nullptr)
    destroy(node->left);
  if(node->right != nullptr)
    destroy(node->right);
  delete node;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode* orig, KDTreeNode* otherNode) {
  if (otherNode == NULL) {
    return;
  }
  orig = new KDTreeNode(otherNode->point);
  copy(orig->left, otherNode->left);
  copy(orig->right, otherNode->right);
}

// //////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////


template <typename RandIter, typename Comparator>
RandIter partition(RandIter start, RandIter end, RandIter k, Comparator cmp) {
  RandIter left = start;
  RandIter right = end;
  RandIter pivotIndex = k;

  auto pivotValue = *pivotIndex;

  auto temp = *pivotIndex;
  *pivotIndex = *right;
  *right = temp;

  RandIter storeIndex = left;

  for (RandIter i = left; i != right; i++) {
    if (cmp(*i, pivotValue)) {
      auto temp2 = *storeIndex;
      *storeIndex = *i;
      *i = temp2;

      storeIndex++;
    }
  }

  auto temp3 = *right;
  *right = *storeIndex;
  *storeIndex = temp3;

  return storeIndex;
}


template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp) {
  RandIter left = start;
  RandIter right = end - 1;

  if (*left == *right) {
    return;
  }

  RandIter pivotIndex = left;

  pivotIndex = partition(left, right, pivotIndex, cmp);

  if (k == pivotIndex) {
    return;
  } 
  else if (k < pivotIndex){
    return select(start, pivotIndex, k, cmp);
  } 
  else {
    return select(pivotIndex + 1, end, k, cmp);
  }
}

// //////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {
    return NearestHelper(query, this->root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::NearestHelper(const Point<Dim>& query, KDTreeNode* curRoot, int curDim) const {

  Point<Dim> tempNearest;

  int nextDim2 = (curDim+1)%Dim;
   
  if(curRoot->right == nullptr && curRoot->left == nullptr){
    return curRoot->point;
  }

  if(smallerDimVal(query, curRoot->point, curDim) && curRoot->left != NULL){
    tempNearest = NearestHelper(query, curRoot->left, nextDim2);
  }
 
  else{
    tempNearest = NearestHelper(query, curRoot->right, nextDim2);
  }

  if(shouldReplace(query, tempNearest, curRoot->point)){     
  tempNearest = curRoot->point;
  }

  int radius = 0;
  for (int i = 0; i< Dim; i++){
    radius += (tempNearest[i] - query[i]) * (tempNearest[i] - query[i]);
  }

  double splitDist = (curRoot->point[curDim]- query[curDim]) * (curRoot->point[curDim]- query[curDim]);

  if(radius>=splitDist){
    Point<Dim> nearest = tempNearest;
    if(smallerDimVal(query, curRoot->point, curDim) && curRoot->left != NULL && curRoot->right != NULL){
      nearest = NearestHelper(query, curRoot->right, nextDim2);        
    }
    else if(curRoot->left != NULL){
      nearest = NearestHelper(query, curRoot->left, nextDim2);
    }
    if(shouldReplace(query, tempNearest, nearest)){
      tempNearest = nearest;
    }  
  }
  return tempNearest;
}