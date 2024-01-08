#include <iostream>
#include <sstream>

#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

int main(int argc, char *argv[]) {
    string inputFileName, outputFileName;
    ofstream fout;

    if (argc < 2) {
        cout << "Please provide an input file name and output file name at least!" << endl;
        return -1;
    }

    outputFileName = argv[1];

    fout.open(outputFileName);

    CodeWriter c(fout);
    c.writeInit();

    for(int i = 2; i < argc ; i++) {
        inputFileName = argv[i];

        Parser p(inputFileName);

        stringstream test(inputFileName);
        string segment;

        while(getline(test, segment, '\\')) {}

        c.setFileName(segment.substr(0, segment.length() - 3));

        while(true) {
            p.advance();

            // cout << p.getCurrentLine() << "\t\t" << p.getArg1() << "\t\t" << p.getArg2() << endl;

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
            } else if(p.currentCommandType() == c_function) {
                c.writeFuntion(p.getArg1(), stoi(p.getArg2()));
            } else if(p.currentCommandType() == c_return) {
                c.writeReturn();
            } else if(p.currentCommandType() == c_call) {
                c.writeCall(p.getArg1(), stoi(p.getArg2()));
            }
        }
    }
    
    fout.close();
    return 0;
}