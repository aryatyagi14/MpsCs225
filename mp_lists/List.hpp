/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
  //allocate space??
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
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  //shouldnt end return 1 past the last element? -yes so just NULL? 
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  //remove all memory allocated for ListNode objects
  //loop till you get to tail node and delete prev and next ptrs
  ListNode* current = head_;
  while (current != NULL) {
    ListNode* tmp = current -> next;
    delete current;
    current = tmp;
    }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if ( head_ != NULL) {
    head_ -> prev = newNode;
  }
  head_ = newNode;
  
  if (tail_ == NULL) {
    tail_ = newNode;
  }
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
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  
  if (head_ == NULL) {
    head_ = newNode;
  }
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  tail_ = newNode;
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
  /// @todo Graded in MP3.1
  //failed edge cases
  if (start == NULL) {
    return NULL;
  }
  if (splitPoint < 1) {
    return start;
  }
  if (splitPoint > length_) {
    return head_;
  }
  ListNode * curr = start; //head of new list

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  //at this point the curr = the head of the new list 

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  //we have a list of nodes, which we want to rotate
  if (length_< 3) {
    return;
  }
  ListNode* curr = head_;
  int remainder = length_ % 3; //we leave this many elements at the end of the list alone
  int i = 0;
  if (remainder == 0 && length_ >= 3) {
    tail_ = tail_ -> prev -> prev;
  }
  //deletes nodes out of list (the second and the third)//does make newhead??
  while (i < length_ - remainder && curr != NULL) {
    std::cout << to_string(i) << std::endl;
    if ((i+1) % 3 == 0 ) {
      std::cout << to_string(length_) << std::endl; // going in here right amount of times
      //we are pointing at node 3 in a 1 2 3 group
      //save new nodes we are gonna change
      ListNode*& twoPrev = curr -> prev -> prev;
      ListNode*& onePrev = curr -> prev->prev->prev;
      ListNode*& oneNext = curr -> prev->prev->next;
      ListNode*& threeNext = curr -> next;
      
      
      if(onePrev != NULL) {
        ListNode*& veryBeg = curr -> prev -> prev -> prev -> next;
        veryBeg = curr -> prev;
      }
      
      //save old nodes we need to set it to later
      ListNode* oneOldPrev = onePrev;
      ListNode* twoOldNext = curr;
      ListNode* threeOldNext = threeNext;
      ListNode* twoOldPrev = twoPrev;
      if (curr -> next != NULL) {
        ListNode*& fourPrev = curr -> next ->prev;
        fourPrev = twoOldPrev;
      }
      //chnaging this like
      twoPrev = oneOldPrev;
      onePrev = twoOldNext;
      oneNext = threeOldNext;
      threeNext = twoOldPrev;

      if(i == 2) {
        head_ = curr -> prev;
      }
      curr = curr -> next;
    }
    if (curr != NULL) {
        curr = curr -> next;
    }
    i++;
  }
  std::cout << "HERE" << std::endl;
  
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
  /// @todo Graded in MP3.2
  //flip next and previous 
  if(startPoint == endPoint) {
    return;
  }
  if(startPoint == NULL) {
    return;
  }
  if(endPoint == NULL) {
    return;
  }
  //chnage head and tail pointers
  ListNode* curr = startPoint;
  ListNode* temp = NULL;
  ListNode* verybeg = startPoint -> prev;
  ListNode* veryend = endPoint -> next;
  ListNode* end = endPoint;
  //chnages very first to be the very last

//flips the next and previous
  while(curr != veryend) {
    temp = curr ->prev;
    //swap next and previous nodes
    curr -> prev = curr -> next;
    //make curr one next (instead of moving down the list we move up(prev))
    curr -> next = temp;
    curr = curr -> prev;
  }
  //make the passes in ending node the front of the list reversed 
  if (!(veryend != NULL )) {
    startPoint -> next = NULL;
  } else {
    startPoint -> next = veryend;
    veryend -> prev = startPoint;
  }
  if ((verybeg != NULL)) {
    verybeg -> next = endPoint;
    endPoint -> prev = verybeg;
  } else {
    endPoint -> prev = NULL;
  }
  temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;

  if(!(head_ != endPoint)) {
    head_ = startPoint;
  }

  if(!(tail_ != startPoint)) {
    tail_ = endPoint;
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
  /// @todo Graded in MP3.2
  //do nothing if it doesnt want anything reveresed
  if (n <= 1) {
    return;
  }
  //iiiiiiiif n>              length then that meaaaans we have to reverse whole array
  if (n >= length_) {
    reverse(head_, tail_);
    return;
  }

  ListNode* head = head_;
  ListNode* curr = head;
  for (int i = 0; i < length_; i +=n) {
    head = curr;
    for(int j = 0; j < n -1; j++) {
      if(curr != tail_) {
        curr = curr -> next;
      }
    }
    reverse(head, curr);
    curr = curr -> next;
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
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(second == NULL || first == NULL) {
    return NULL;
  }
  if(second == NULL && first != NULL) {
    return first;
  }
  if(first == NULL && second != NULL) {
    return second;
  }
  ListNode* temp = NULL;
  ListNode* curr = NULL;
  if((second -> data < first -> data)) {
    curr = second;
    second = second -> next;
  } else {
    curr = first;
    first = first -> next;
  }
  temp = curr;
  while(second != NULL && first != NULL) {
    if((second -> data < first -> data)) {
      temp -> next = second;
      second -> prev = temp;
      second = second -> next; 
    } else {
      temp -> next = first;
      first -> prev = temp;
      first = first -> next;
    }
    temp = temp -> next;
  }

  if ((first != NULL) && !(second != NULL)) {
    temp -> next = first;
    first -> prev = temp;
    temp = temp -> next;
    first = first -> next;

  }
  if (!(first != NULL) && !(second == NULL)) {
    temp -> next = second;
    second -> prev = temp;
    temp = temp -> next;
    second = second -> next;
  }
  return curr;
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
  /// @todo Graded in MP3.2
  if (start == NULL || start -> next == NULL) {
    return start;
  }
  //divide list into 2 then merge those sorted lists
  int remainder = chainLength % 2;
  int secondLength = (chainLength/2) + remainder;
  ListNode* secondhalf = split(start, chainLength / 2); //gets head of second half of the list
  ListNode* fh = mergesort(start, chainLength/2);
  ListNode* sh = mergesort(secondhalf, secondLength);
  //after getting back the two sorted lists, merge them together
  return merge(fh, sh);
}
