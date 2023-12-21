#include <iostream>
#include <sstream>

#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

int main(int argc, char *argv[]) {
    string inputFileName, outputFileName;
    ofstream fout;

    if (argc < 1) {
        cout << "Please provide an input file name!" << endl;
    } else {
        inputFileName = argv[1];
        outputFileName = inputFileName.substr(0, inputFileName.length() - 2) + "asm";
    }

    fout.open(outputFileName);

    Parser p(inputFileName);
    CodeWriter c(fout);

    stringstream test(inputFileName);
    string segment;

    while(getline(test, segment, '\\')) {}

    c.setFileName(segment.substr(0, segment.length() - 3));

    while(true) {
        p.advance();

        cout << p.getCurrentLine() << "\t\t" << p.getArg1() << endl;

        if (!p.hasMoreCommands()) {
            break;
        }

        if(p.currentCommandType() == c_push || p.currentCommandType() == c_pop) {
            c.writePushPop(p.currentCommandType(), p.getArg1(), stoi(p.getArg2()));
        } else if(p.currentCommandType() == c_arithmetic) {
            c.writeArithmetic(p.getArg1());
        } else if(p.currentCommandType() == c_if) {
            c.writeIf(p.getArg1());
        } else if(p.currentCommandType() == c_label) {
            c.writeLabel(p.getArg1());
        } else if(p.currentCommandType() == c_goto) {
            c.writeGoto(p.getArg1());
        }
    }
    
    fout.close();
    return 0;
}