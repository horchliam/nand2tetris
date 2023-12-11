#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

enum CommandType { c_arithmetic, c_push, c_pop, c_label, c_goto, c_if, c_function, c_return, c_call, c_undefined };

class Parser {
    public:
    Parser(string& in); // in is a reference to a string object

    bool hasMoreCommands();

    void advance();

    CommandType currentCommandType();

    string getArg1();

    string getArg2();

    string getCurrentLine();
    private:
    ifstream fin;
    string currentLine = "";
    bool moreCommands = true;
    map<string, CommandType> commandTable;
};
#endif