/**
 *  CPP implementation of CSE 100 PA2 C++ Autocomplete
*/

#include "Autocomplete.hpp"

/*
 * Implementation of the Autocomplete constructor
 */
Autocomplete::Autocomplete(const vector<string> & corpus) {
    tst = new TernaryTrie();
    if (corpus.size() == 0) {
        return;
    }
    // insert corpus into the TernayTrie
    vector<string>::const_iterator cit = corpus.begin();
    vector<string>::const_iterator cend = corpus.end();
    // insert all strings with iterator
    for (; cit != cend; ++cit) {
        tst->insert(*cit);
    }
}

/*
 * Implementation of the predictCompleions method
 */
vector<string> Autocomplete::predictCompletions(const string & prefix) const {
    // Get pirority queue returned by DFS of ternary trie
    vector<string> result;
    TSTNode * node = tst->find(prefix);
    if (node == 0) {
        return result;
    }
    result = tst->dfs(node);
    return result; 
}

/*
 * Implementation of the destructor
 */
Autocomplete::~Autocomplete() {
    // delete trie object's nodes
    // trie would automatically destruct
    delete tst;
}
