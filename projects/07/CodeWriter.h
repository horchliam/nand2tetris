#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <iostream>
#include <string>
#include "Parser.h"

using namespace std;

class CodeWriter {
    public:
    CodeWriter(ostream& out) : out(out) {};
    void setFileName(string& in) { this->curFileName = in; };
    void writeArithmetic(string& command);
    void writePushPop(CommandType command, string segment, int index);
    void saySomething() { out << "Hi fella!"; };
    private:
    ostream& out;
    string curFileName;
};
#endif