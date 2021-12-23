/* Your code here! */
#include "dsets.h"
#include <iostream>


void DisjointSets::addelements(int num) {
    while (num != 0) {
        sets.push_back(-1);
        num--;
    }
}

int DisjointSets::find(int elem) {
    //returns the index of the root of the tree
    //traverse up the tree until you reach a negtive 1
    /*
    int curr = sets[elem];
    while(curr != -1) {
        curr = sets[curr];
    }
    return curr;
    */
    //they also want us to compress the tree(use recursion)
    //base case = if it is a root (has a negative number)
    int s = sets[elem];
    if (s < 0) {
        return elem;
    }
    int ret = find(s);
    sets[elem] = ret;
    return ret;

}

void DisjointSets::setunion(int a, int b) {
    //remember to update size
// first find the root of each argument 
    int first = find(a);
    int second = find(b);
    int fsize = -1* sets[first];
    int ssize = -1* sets[second];
    if (first == second) {
        return;
    }
    if (fsize > ssize) {
        //first is greater than second, so second should point to firsy
        sets[first] -= ssize;
        sets[second] = first;
    }
    else if (ssize > fsize) {
        sets[second] -= fsize;
        sets[first] = second;
    }
    else {
        //second arg points to first arg
        sets[first] -= ssize;
        sets[second] = first;
    }
}

int DisjointSets::size(int elem) {
    //first find the root of the tree for which it is in
    int index = find(elem);
    //the size should be stored at this place as a negative 
    int ret = -1* (sets[index]);
    return ret;
}



