#include "Parser.h"

using namespace std;

Parser::Parser(string& in) {
    fin.open(in);

    if (fin.fail()) {
        cout << in << " not found." << endl;
        exit(1);
    }

    commandTable["add"] = c_arithmetic;
    commandTable["sub"] = c_arithmetic;
    commandTable["neg"] = c_arithmetic;
    commandTable["eq"] = c_arithmetic;
    commandTable["gt"] = c_arithmetic;
    commandTable["lt"] = c_arithmetic;
    commandTable["and"] = c_arithmetic;
    commandTable["or"] = c_arithmetic;
    commandTable["not"] = c_arithmetic;
    commandTable["push"] = c_push;
    commandTable["pop"] = c_pop;
    commandTable["label"] = c_label;
    commandTable["goto"] = c_goto;
    commandTable["if-goto"] = c_if;
    commandTable["function"] = c_function;
    commandTable["call"] = c_call;
    commandTable["return"] = c_return;
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

CommandType Parser::currentCommandType() {
    signed long spacePos = currentLine.find(" ");
    string command;

    if(spacePos != string::npos) {
        command = currentLine.substr(0, spacePos);
    } else {
        command = currentLine;
    }
        
    if(commandTable.find(command) != commandTable.end()) {
        return commandTable[command];
    }

    return c_undefined;
}

// If a second space is not present, this method would not work
string Parser::getArg1() {
    if(currentCommandType() == c_arithmetic) {
        return currentLine;
    }

    int firstSpace = 0, secondSpace = 0;

    for(int i = 0; i < currentLine.length(); i++) {
        if(currentLine[i] == ' ') {
            if(firstSpace == 0) {
                firstSpace = i;
            } else {
                secondSpace = i;
                break;
            }
        }
    }

    if(firstSpace != 0 && secondSpace != 0) {
        return currentLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);
    } 
        
    return "NO FIRST ARG FOUND";
}

//
string Parser::getArg2() {
    int firstSpace = 0, secondSpace = 0;

    for(int i = 0; i < currentLine.length(); i++) {
        if(currentLine[i] == ' ') {
            if(firstSpace == 0) {
                firstSpace = i;
            } else {
                secondSpace = i;
                break;
            }
        }
    }

    if(secondSpace != 0) {
        return currentLine.substr(secondSpace + 1, currentLine.length() - secondSpace - 1);
    } 
        
    return "NO SECOND ARG FOUND";
}

string Parser::getCurrentLine() {
    return currentLine;
}
