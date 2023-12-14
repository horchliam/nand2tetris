#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <iostream>
#include <string>
#include <map>
#include "Parser.h"

using namespace std;

class CodeWriter {
    public:
    CodeWriter(ostream& out) : out(out) { 
        segments["constant"] = "@SP";

        eqCounter = 0;
        ltCounter = 0;
        gtCounter = 0;
    };
    void setFileName(string& in) { this->curFileName = in; };
    void writeArithmetic(string command);
    void writePushPop(CommandType command, string segment, int index);
    void saySomething() { out << "Hi fella!"; };
    private:
    ostream& out;
    string curFileName;
    map<string, string> segments;
    int eqCounter, ltCounter, gtCounter;
};
#endif