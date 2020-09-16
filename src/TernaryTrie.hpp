#ifndef TernaryTrie_HPP 
#define TernaryTrie_HPP

#include "TSTNode.hpp"
#include <string>
#include <iostream>
#include <queue>
#include <utility>
#include <stack>

using namespace std;

class paircomp
{
    bool reverse;
   public:
    // return left > right
    paircomp(const bool& revparam=false)
        {reverse=revparam;}
    bool operator() (const pair<string, int> & lhs, 
        const pair<string, int> & rhs) const
    {
        if (lhs.second == rhs.second) {
            return rhs.first < lhs.first;
        }
        if (reverse) return (lhs.second>rhs.second);
        else return (lhs.second<rhs.second);
     }
};

class TernaryTrie {
   protected:
    /** Pointer to the root of this TST, or 0 if the TST is empty */
    TSTNode * root;

   public:

    /** Default constructor.
        Initialize an empty TST.
     */
    TernaryTrie() : root(0) {}

    /** Default destructor.
     *  Delete every node in this BST.
     */
    virtual ~TernaryTrie() {
        deleteAll(root);
    }

    /**
     * Return the top 10 predictions
     */
    virtual vector<string> dfs(TSTNode * root) const {
        vector<string> result;
        
        // run dfs on current root
        stack<TSTNode *> s;
        // using paircomp:
        typedef std::priority_queue<pair<string, int>, 
            std::vector<pair<string, int>>, paircomp> mypq;
        mypq pq;
        pair<string, int> p;
        TSTNode * curr;
        if (root == 0) {
            return result;
        }
        if (root->wordNum != 0) {
            p.first = root->s;
            p.second = root->wordNum;
            pq.push(p);
        }
        if (root->middle == 0) {
            result.push_back(pq.top().first);
            return result;
        }
        s.push(root->middle);
        while (! s.empty()) {
            curr = s.top();
            // check if current node is a word node:w
            if (curr->wordNum != 0) {
                // insert this node's word and count into queue
                p.first = curr->s;
                p.second = curr->wordNum;
                pq.push(p);
            }
            s.pop();
            
            if (curr->left != 0) {
                s.push(curr->left);
            }
            if (curr->middle != 0) {
                s.push(curr->middle);
            }
            if (curr->right != 0) {
                s.push(curr->right);
            }
        }

        for (int i = 0; i < 10; i ++) {
            if (! pq.empty()) {
                result.push_back(pq.top().first);
                pq.pop();
            }
        }
        return result;
    }

    /**
     * Return the final node of a string traverse
     */
    virtual TSTNode * find(const string & word) const {
        if (root == 0 || word == "") {
            return 0;
        }
        TSTNode * curr = root; 
        std::string::const_iterator wit = word.begin();
        std::string::const_iterator wend = word.end();
        unsigned char wordChar;
        unsigned char nodeChar;
        while (wit != wend) {
            wordChar = *wit;
            nodeChar = curr->character;
            if (wordChar < nodeChar) {
                if (curr->left == 0) {
                    return 0;
                }
                curr = curr->left;
            }
            else if (wordChar > nodeChar) {
                if (curr->right == 0) {
                    return 0;
                }
                curr = curr->right;
            }
            else {
                if (wit + 1 == wend) {
                    return curr;
                }
                if (curr->middle == 0) {
                    return 0;
                }
                curr = curr->middle;
                ++wit;
            }
        }
        return 0;
    }

    /** Given a reference to a Data item, insert a copy of it in this TST.
     *  Update the number count in node if duplicate
     *  Return the current count of this word
     *  Return -1 if fail
     */
    virtual int insert(const string & word) {
        
        // Initialze pointer to characters
        std::string::const_iterator sit = word.begin();
        std::string::const_iterator send = word.end();
        
        // return if word is empty
        if (sit == send) {
            return -1;
        }
        
        // Initialize root if tree is empty
        if (root == 0) {
            root = new TSTNode((unsigned char)*sit);
        }

        // initialize current node
        TSTNode * curr = root;

        // iterator through the rest of characters,
        // insert as new node if not exist,
        // traverse down if exist
        // end when all character are read
        while (sit != send) {
            if ((unsigned char)*sit < curr->character) {
                if (curr->left == 0) {
                    curr->left = new TSTNode((unsigned char)*sit);
                    curr->left->parent = curr;
                }
                curr = curr->left; // still same char
            }
            else if ((unsigned char)*sit > curr->character) {
                if (curr->right == 0) {
                    curr->right = new TSTNode((unsigned char)*sit);
                    curr->right->parent = curr;
                }
                curr = curr->right;
            }
            // if the character equals to current node
            else {
                // if character is the last character
                if (sit +  1 == send) {
                    // if currently 0, record word inserted
                    if (curr->wordNum == 0) {
                        curr->s = word;
                    }
                    // increase word number to mark word node
                    ++(curr->wordNum);
                    return curr->wordNum;
                }
                // character is not the end
                ++sit; // move to next character
                if (curr->middle == 0) {
                    // insert new node if no middle child
                    curr->middle = new TSTNode((unsigned char)*sit);
                    curr->middle->parent = curr;
                } 
                curr = curr->middle;
            } 
        }
        // not inserted
        return -1;
    }


    /** Return true if the TST is empty, else false.
     */
    bool empty() const {
        if (root != 0) {
            return false;
        }
        else {
            return true;
        }
    }

    /** Traversel and delete all nodes
     */
    static void deleteAll(TSTNode * root) {
        // delete all nodes
        if (root == 0) {
            return;
        }
        // base case: no child
        if (root->left == 0 && root->middle == 0 && root->right == 0) {
            delete root; // delete the root
            return;
        }
        // if left is not null, call on left subtree
        if (root->left != 0) {
            deleteAll(root->left);
        }
        if (root->middle != 0) {
            deleteAll(root->middle);
        }
        if (root->right != 0) {
            deleteAll(root->right);
        }
        delete root;
    }
};

#endif  // TernaryTrie 
