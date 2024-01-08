#include "JackTokenizer.h"

JackTokenizer::JackTokenizer(string fileName) {
    fin.open(fileName);

    if (fin.fail()) {
        cout << fileName << " not found." << endl;
        exit(1);
    }

    fout.open("Tokenizer.test");

    getline(fin, curLine);
    curLineIndex = 0;

    fout << "START" << endl;
}

bool JackTokenizer::hasMoreTokens() {
    return !fin.eof();
}

void JackTokenizer::advance() {
    if(curLineIndex >= curLine.length() - 1) {
        getline(fin, curLine);
        curLineIndex = 0;
    }

    string tempToken = "";

    for(int i = curLineIndex; i < curLine.length(); i++) {
        curLineIndex = i;

        if(curLine[i] == ' ' && tempToken != "") {
            curToken = tempToken;
            fout << curToken << endl;
            break;
        } else if(curLine[i] != ' ') {
            tempToken += curLine[i];
        }
    }

    if(curLineIndex == curLine.length() - 1) { 
        curToken = tempToken;
        fout << curToken << endl;
    }
}