/* Your code here! */
#pragma once
#include <vector>

class DisjointSets {
    // declare the 4 functions in part 1 
    public:
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
    //create the vector storage element
    private:
        std::vector<int> sets;
};