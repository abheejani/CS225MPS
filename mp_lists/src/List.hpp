/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  ListNode * currNode = head_;
  ListNode * temp;

  while(currNode != NULL) {
    temp = currNode;
    currNode = currNode->next;
    delete temp;
  }
  length_ = 0;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * tempNode = new ListNode(ndata);
  if (tail_ == NULL) {
    tail_ = tempNode;
    head_ = tempNode;
    length_++;
    return;
  }

  tempNode -> next = head_;
  head_ -> prev = tempNode;

  head_ = tempNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * tempNode = new ListNode(ndata);

  if (tail_ == NULL) {
    head_ = tempNode;
    tail_ = tempNode;
    length_++;
    return;
  }

    tempNode->prev = tail_;
    tail_->next = tempNode;
    tail_ = tempNode;
    length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  if (start == NULL || splitPoint == 0) {
    return start;
  }

  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
    curr->prev->next = NULL;
    curr->prev = NULL;
    return curr;
  }

  return NULL;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  // @todo Graded in part 1
  int location = 1;
  
  if(head_ == NULL || head_ ->next == NULL) {
    return;
  }
  ListNode * currNode = head_;
  while(currNode->next != NULL && currNode->next != tail_) {
    ListNode * nextNode = currNode->next;

    if(location % 2 == 1) {
      currNode->next = nextNode->next;
      nextNode->next = NULL;
      nextNode->prev = tail_;
      tail_->next = nextNode;
      tail_ = nextNode;
    }
    else {
      currNode = nextNode;
    }
    location++;

  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if(startPoint == NULL || startPoint == endPoint) {
    return;
  }
  if(head_ == nullptr || tail_ == nullptr) return;

  ListNode * next = NULL;
  ListNode * currNode = startPoint;
  ListNode * myStart = startPoint;
  ListNode * beforeStart = startPoint->prev;
  ListNode * myEnd = endPoint;
  ListNode * afterEnd = endPoint->next;

  

  ListNode* stop = NULL;
  if(endPoint !=tail_){
      stop = endPoint->next;
  }
  
  while(currNode != endPoint) {
    ListNode * next = currNode->next;
    currNode->next = currNode->prev;
    currNode->prev = next;
    currNode = next;
  }

  ListNode * temp = NULL;

  temp = currNode->prev;
  currNode->prev = beforeStart;
  currNode->next = temp;

  endPoint = myStart;
  endPoint->next = afterEnd;

  if(beforeStart == NULL){
    head_ = currNode;
  }
  else{
    beforeStart->next = myEnd;
  }

  if(afterEnd == NULL){
    tail_ = endPoint;
  }
  else{
    afterEnd->prev = myStart;
  }

}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */

template <typename T>
void List<T>::reverseNth(int n) {
  if(n <= 0) {
    return;
  }

  ListNode *currHead = head_;
  ListNode *currTail = head_;

  while(currTail != NULL) {
    for(int i = 0; i < n-1 && currTail != tail_; i++) {
      currTail = currTail->next;
    }
    ListNode* nextHead = currTail->next;
    reverse(currHead, currTail);
    currHead = nextHead; 
    currTail = nextHead; 
  }
}



/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }

    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
// template <typename T>
// typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
//   /// @todo Graded in mp_lists part 2
//   if(first == NULL && second != NULL){return second;}
//   if(first != NULL && second == NULL){return first;}
//   if(first == NULL && second == NULL){return NULL;}

//   ListNode * smaller = NULL;
//   ListNode * bigger = NULL;
//   ListNode * ret = NULL;
//   ListNode * topNode;

//   if(first->data < second->data || first->data == second->data){
//     ret = first;
//     smaller = first;
//     bigger = second;
//   }
//   else{
//     ret = second;
//     smaller = second;
//     bigger = first;
//   }

//   ret = smaller;
//   topNode = ret;


//   while(smaller != NULL || bigger!= NULL){
//     if(smaller->next != NULL && smaller->next->data < bigger->data){
//       smaller = smaller->next;
//       ret->next = smaller;
//       smaller->prev = ret;
//       ret = ret->next;
//     }
//     else if (smaller->next != NULL && bigger->data < smaller->next->data){
//       ListNode * temp = smaller->next;
//       smaller = bigger;
//       bigger = temp;
//       ret->next = smaller;
//       smaller->prev = ret;
//       ret = ret->next;
//     }
//     else if(smaller->next == NULL){
//       ret->next = bigger;
//       bigger->prev = ret;
//       ret = ret->next;
//       break;
//     }
//   }
  
//   return topNode;
// }







template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  if (first == NULL) return second;
  if (second == NULL) return first;

  ListNode * smaller = first;
  ListNode * bigger = second;
  ListNode * ret = NULL;
  ListNode * topNode;

  if (first->data < second->data || first->data == second->data) {
    ret = first;
    smaller = first->next;
  }
  else {
    ret = second;
    bigger = second->next;
  }

  topNode = ret;

  while (smaller != NULL && bigger != NULL) {
    if (smaller->data < bigger->data || smaller->data == bigger->data) {
      ret->next = smaller;
      smaller->prev = ret;
      smaller = smaller->next;
    }
    else {
      ret->next = bigger;
      bigger->prev = ret;
      bigger = bigger->next;
    }
    ret = ret->next;
  }

  if (smaller == NULL && bigger != NULL) {
    ret->next = bigger;
    bigger->prev = ret;
  }
  else if (smaller != NULL && bigger == NULL) {
    ret->next = smaller;
    smaller->prev = ret;
  }

  return topNode;
}
















/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  if(chainLength == 1){
    return start;
  }

  ListNode* dusrasplit = split(start, chainLength/2);
  ListNode* dusrasplitsorted = mergesort(dusrasplit, chainLength - chainLength/2);
  ListNode* pehlasplitsorted = mergesort(start, chainLength/2);
  return merge(pehlasplitsorted, dusrasplitsorted);
}
