#include "DocumentGenerator.hpp"
#include <chrono>
using namespace std::chrono;

const string PUNCTUATION = ".!,?";
const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";
const string WHITESPACE = " \t\r\n\v\f";

/**
 * Helper functions used to clean and tokenize input file
 */
vector<string> * tokenize(const string & line) {
    vector<string> * words = new vector<string>();
    vector<char> word;
    bool endwithPunc;
    for (unsigned char c : line) {
        endwithPunc = PUNCTUATION.find(c) != string::npos;
        if (UNWANTED_CHARACTERS.find(c) == string::npos) {
            if (WHITESPACE.find(c) == string::npos &&
                endwithPunc == false) {
                word.push_back(c);
            } else if (word.size() > 0) {
                words->push_back(string(word.begin(), word.end()));
                word.clear();
            }
            if (endwithPunc) {
                // insert punc as a word
                word.push_back(c);
                words->push_back(string(word.begin(), word.end()));
                word.clear();
            }
        }
    }
    if (word.size() > 0) {
        words->push_back(string(word.begin(), word.end()));
    }
    return words;
}
vector<string> * getWords(const string & documentsDirectory) {
    vector<string> * words = new vector<string>();
    ifstream infile;

    // read files from directory
    DIR * dir = opendir(documentsDirectory.c_str());
    struct dirent * entry;
    string filename;

    while ((entry = readdir(dir))) {
        filename = entry->d_name;
        if (filename != "." && filename != "..") {

            infile.open(documentsDirectory + "/" + filename);
            if (!infile) {
                cerr << "Couldn't open file: " << documentsDirectory +
                        + "/" + filename << endl;
                exit(1);
            }

            string line;
            while(getline(infile, line)) {
                vector<string> * wordsInLine = tokenize(line);
                words->insert(words->end(), wordsInLine->begin(),
                               wordsInLine->end());
                delete wordsInLine;
            }
            infile.close();
            words->push_back("|");
        }
    }
    closedir(dir);
    return words;
}

DocumentGenerator::DocumentGenerator(const string & documentsDirectory) {
    srand (time(0));

    // string vector used to build datastructure
    vector<string> * words = getWords(documentsDirectory);

    if (words->size() == 0) {
        delete words;
        return;
    }

    /* Build datastructure
     * build ab unordered_map<string, unordered_map<string, int> *>
     * u_m(current strings, unordered_map of (next strings, frequencies))
     */
    ds = new unordered_map<string, vector<string> *>();;

    unordered_map<string, vector<string> *>::const_iterator iter;
    unordered_map<string, int>::const_iterator inneriter;
    string currword;
    string nextword;
    vector<string> * sv;

    // read pairs of word and its next word: i, i+1
    for (unsigned int i = 0; i < words->size() - 1; i++) {
        currword = words->at(i);
        nextword = words->at(i+1);

        if (nextword != "|" && currword != "|"){
            // word not exist in hashtable, create new
            if (ds->count(currword) == 0) {
                sv = new vector<string>();
                ds->insert(make_pair(currword, sv));
            }
            sv = ds->at(currword);
            sv->push_back(nextword);
        }
    }

    // delete words vector after construction is done
    delete words;
}

string DocumentGenerator::generateNextWord(const string & prevWord) {
    // assume that prevWord is always a word that's present
    // get the iterator to that words's key and value pair in ds
    vector<string> * sv = ds->at(prevWord);
    // get the words and their count
    // ctarray[n] = ctarray[n-1] + ctarray[n-2] + ... + ctarray[0]
    /*while (nextmapiter != nextmapend){
        totalct += nextmapiter->second;
        nextmapiter++;
    }*/
    /* generate secret number between 1 and count */
    int randomNum = rand() % sv->size();
    //cout << randomNum << endl;

    return sv->at(randomNum);
}

string DocumentGenerator::generateDocument(const int numWords) {
    ostringstream s;
    string nextword = ".";
    bool start = true;
    for (int i = 0; i < numWords; i ++) {
        nextword = generateNextWord(nextword);
        //Don't insert spaces in front of punctuation marks
        //Don't insert a space at the start of the document
        if (!((nextword.size() == 1
                && PUNCTUATION.find(nextword.at(0)) != string::npos)
                || start)) {
            s << " ";
        }
        s << nextword;
        start = false;
    }
    return s.str();
}

DocumentGenerator::~DocumentGenerator() {
    // delete all the * unordered_map in the ds
    unordered_map<string, vector<string> *>::const_iterator dgit =
      ds->begin();
    unordered_map<string, vector<string> *>::const_iterator dgend =
      ds->end();
    while (dgit != dgend) {
        delete dgit->second;
        dgit ++;
    }

    // delete ds
    delete ds;
}
