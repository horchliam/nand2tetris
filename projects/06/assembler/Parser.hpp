#ifndef HACK_ASSEMBLER_PARSER_H
#define HACK_ASSEMBLER_PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Parser {
    public:
    // Given a file name, initialize the parser
    Parser(string& x);

    bool getHasMoreCommands();

    void advance();

    char commandType();

    string symbol();

    string destM();

    string compM();

    string jumpM();

    string getCurrentLine();

    private:
    bool hasMoreCommands = true;
    ifstream fin;
    map<char, char> commandTable;
    string currentCommand;
};

#endif