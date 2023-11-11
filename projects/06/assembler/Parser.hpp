#ifndef HACK_ASSEMBLER_PARSER_H
#define HACK_ASSEMBLER_PARSER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Parser {
    public:
    // Given a file name, initialize the parser
    Parser(string& x);

    bool hasMoreCommands();

    void printHelloFileName();

    private:
    string filename;
    ifstream fin;
};

#endif