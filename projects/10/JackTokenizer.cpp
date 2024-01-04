#include "JackTokenizer.h"

JackTokenizer::JackTokenizer(string fileName) {
    fin.open(fileName);

    if (fin.fail()) {
        cout << fileName << " not found." << endl;
        exit(1);
    }

    fout.open("Tokenizer.test");

    fout << "Hello World!" << endl;
}