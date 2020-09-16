#include <vector>
#include <string>
#include "../src/Autocomplete.hpp"
#include <iostream>

using namespace std;

/**
 * Test Driver for the Autocomplete class
 */
int main() {
    
    /* Create a vector of some vectors */
    vector<string> corpus;
    
    cout << "Testing empty corpus ..." << endl;
    Autocomplete empty = Autocomplete(corpus);
    if ((empty.predictCompletions("Hi")).size() !=0) {
        cout << "FAIL, should return vector of size 0!" << endl;
    }

    for (int i = 0; i < 2; i ++) {
        corpus.push_back("Hi");
        corpus.push_back("Hello");
        corpus.push_back("Test");
        corpus.push_back("Hz");
        corpus.push_back("Hello");
        corpus.push_back("H");
        corpus.push_back("Hello");
        corpus.push_back("Hz");
        corpus.push_back("Hi");
    }
    cout << "initialzed corpus" << endl;

    /* Create an instance of Autocomplete class */
    Autocomplete ac = Autocomplete(corpus);
    cout << "successfully constructed ac object" << endl;

    cout << "testing prefix A" << endl;
    string prefix1 = "A";
    if ( 0 != (ac.predictCompletions( prefix1 )).size() ) {
        cout << "ERROR: should return vector of size 0" << endl;
        return -1;
    }
    
    cout << "testing prefix H" << endl;
    string prefix2 = "H";
    vector<string> v1 = ac.predictCompletions( prefix2 );
    if ( 4 != v1.size() ) {
        cout << "returned vector of prediction has size of " << v1.size()
            << endl;
        cout << "ERROR: should return vector of size 4" << endl;
        return -1;
    }

    cout << "testing output of H" << endl;
    vector<string> result = {"Hello", "Hi", "Hz", "H"};
    vector<string>::const_iterator corpusIt = result.begin();
    vector<string>::const_iterator vit1 = v1.begin();
    // compare result vector
    for (int i = 0; i < 3; i++) {
        if ((*corpusIt).compare(*vit1) != 0) {
            cout << "ERROR: wrong predict result, should be: " <<
                 *corpusIt << " , actually: " << *vit1 << endl;
        }
        ++vit1;
        ++corpusIt;
    }

    cout << "testing single word corpus ..." << endl;
    vector<string> single;
    single.push_back("Computer");
    Autocomplete acsingle = Autocomplete(single);
    vector<string> resultsi = acsingle.predictCompletions("Computer");
    if (resultsi.size() != 1 || resultsi[0] != "Computer") {
        cout << "FAIL: incorrect size or result" << resultsi.size()
             << ", " << resultsi[0] << endl;
    }
    resultsi = acsingle.predictCompletions("ComputerScience");
    if (resultsi.size() != 0) {
        cout << "FAIL: incorrect size of result" << resultsi.size()
             << endl;
    }

    cout << "testing corpus with 20+ different words start with A"
         << endl;
    vector<string> A;
    A.push_back("å");
    A.push_back("åpple");
    A.push_back("AppleJuice");
    A.push_back("ApplePie");
    A.push_back("App");
    A.push_back("Application");
    A.push_back("AppStore");
    A.push_back("Applet");
    A.push_back("AppleStore");
    A.push_back("AppleSoda");
    A.push_back("AppleFlavor");
    A.push_back("AppleBee");
    A.push_back("AppleComputer");
    A.push_back("AppleFair");
    A.push_back("AppleCompany");
    A.push_back("AppleWatch");
    A.push_back("AppleTv");
    A.push_back("AppleCare");
    Autocomplete apple = Autocomplete(A);
    vector<string> appleresult = apple.predictCompletions("å");
    vector<string>::const_iterator itapple = appleresult.begin();
    vector<string>::const_iterator enapple = appleresult.end();
    for (; itapple != enapple; ++itapple) {
        cout << *itapple << ", ";
    }
    cout << endl;
}
