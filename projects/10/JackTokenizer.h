#ifndef JACKTOKENIZER_H
#define JACKTOKENIZER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class JackTokenizer {
    public:
    JackTokenizer(string fileName);
    bool hasMoreTokens();
    void advance();
    private:
    ifstream fin;
    ofstream fout;
    string curToken;
    int curLineIndex;
    string curLine;
};
#endif