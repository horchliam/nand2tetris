#ifndef JACKTOKENIZER_H
#define JACKTOKENIZER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class JackTokenizer {
    public:
    JackTokenizer(string fileName);
    private:
    ifstream fin;
    ofstream fout;
};
#endif