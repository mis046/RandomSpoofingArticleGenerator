#include "../src/DocumentGenerator.hpp"

/* TEST the helper functions used to tokenize strings
const string PUNCTUATION = ".!,?";
const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";
const string WHITESPACE = " \t\r\n\v\f";
vector<string> * tokenize(const string & line)
vector<string> * getWords(const string & fileLocation)
*/
int main() {
  //TODO your tests here

  /* TEST the helper functions used to tokenize strings
  string documentsDirectory = "./example_dg_datasets/Trump/20170128.txt";
  vector<string> * words = getWords(documentsDirectory);
  for (int i = 0; i < (*words).size(); i++) {
      cout << (*words)[i] << ", ";
  }
  cout << endl;
  delete words;
  */
  cout << endl;
  /* Test small text constructor*/
  cout << "Testing constructor with samll text" << endl;
  DocumentGenerator * dgsmall = new DocumentGenerator("./small.txt");
  unordered_map<string, unordered_map<string, int> *>::const_iterator dgit =
    dgsmall->ds->begin();
  unordered_map<string, unordered_map<string, int> *>::const_iterator dgend =
    dgsmall->ds->end();
  unordered_map<string, int>::const_iterator innerit;
  unordered_map<string, int>::const_iterator innerend;
  while (dgit != dgend) {
      innerit = (dgit->second)->begin();
      innerend = (dgit->second)->end();
      cout << "Current word is: " << dgit->first << endl;
      while (innerit != innerend) {
          cout << innerit-> first <<
            "-" << innerit->second << "    ";
          innerit++;
      }
      cout << endl;
      dgit++;
  }
  cout << endl;

  /* Test small generateNextWord */
  cout << "Testing generateNextWord" << endl;
  cout << "think should be twice the time as like and ." << endl;
  string s;
  int thinkct = 0;
  int dotct = 0;
  int likect = 0;
  for (int i = 0; i < 10000; i ++) {
      s = dgsmall->generateNextWord("I");
      if (s == "think") {thinkct++;}
      if (s == ".") {dotct++;}
      if (s == "like") {likect++;}
  }
  cout << "think - " << thinkct << " , . - " <<
      dotct << " , like" << likect << endl;
  cout << endl;

  cout << "Testing generateDocument" << endl;
  string doc = dgsmall->generateDocument(20);
  cout << doc << endl;

  delete dgsmall;

  /* Test empty DocuementGenerator */
  /* cout << "Testing build with empty file" << endl;
  DocumentGenerator * dgempty = new DocumentGenerator("./empty.txt");
  cout << "Next word: " << dgempty->generateNextWord("I") << endl;
  cout << "Document: " << dgempty->generateDocument(10) << endl;
  cout << endl; */
}
