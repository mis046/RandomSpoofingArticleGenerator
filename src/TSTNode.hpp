#ifndef BSTNODE_HPP
#define BSTNODE_HPP

#include <string>

using namespace std;

class TSTNode {
   public:
    // initialize
    TSTNode(const unsigned char & c) : character(c) { 
        left = middle = right = parent = 0; 
    }

    TSTNode * left;
    TSTNode * right;
    TSTNode * middle;
    TSTNode * parent;

    const unsigned char character;
    
    string s;
    int wordNum = 0;
    
};
#endif  // TSTNODE_HPP
