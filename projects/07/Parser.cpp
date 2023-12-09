#include "Parser.h"

using namespace std;

Parser::Parser(string& in) {
    fin.open(in);

    if (fin.fail()) {
        cout << in << " not found." << endl;
        exit(1);
    }
}

bool Parser::hasMoreCommands() {
    return moreCommands;
}

void Parser::advance() {
    string temp;
    signed long commentPos;
    bool commandFound = false;

    while(!commandFound && getline(fin, temp)) {
        commentPos = temp.find("//");
        
        if (commentPos != string::npos) {
            temp.erase(commentPos, temp.length() - commentPos); 
        }

        commandFound = !temp.empty();
    }

    moreCommands = commandFound;
    currentLine = temp;
}

string Parser::getCurrentLine() {
    return currentLine;
}