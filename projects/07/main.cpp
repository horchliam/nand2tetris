#include <iostream>

#include "Parser.h"

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

    while(true) {
        p.advance();

        if (!p.hasMoreCommands()) {
            break;
        }

        cout << p.getCurrentLine() << "\t\t" << p.getArg1() << endl;
    }
    
    fout.close();
    return 0;
}