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
        segments["local"] = "@LCL";
        segments["argument"] = "@ARG";
        segments["this"] = "@THIS";
        segments["that"] = "@THAT";

        eqCounter = 0;
        ltCounter = 0;
        gtCounter = 0;
    };
    void setFileName(string in) { this->curFileName = in; };
    void writeArithmetic(string command);
    void writePushPop(CommandType command, string segment, int index);
    void writeLabel(string label);
    void writeIf(string label);
    void writeGoto(string label);
    void writeFuntion(string functionName, int locals);
    void writeReturn();
    void saySomething() { out << "Hi fella!"; };
    private:
    ostream& out;
    string curFileName;
    map<string, string> segments;
    int eqCounter, ltCounter, gtCounter;
};
#endif