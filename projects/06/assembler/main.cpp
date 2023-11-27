#include "Parser.hpp"
#include "Code.hpp"
#include "SymbolTable.hpp"
#include <string>
#include <bitset>
#include <iostream>
#include <fstream>

using namespace std;

/* Helper functions
*/
string convertToAInstruction(string in);

int main()
{
    ofstream outfile("test.hack");
    string testString = "../pong/Pong.asm";
    Parser p(testString);
    SymbolTable s;
    int curRom = 0;

    while(true) {
        p.advance();

        if(!p.getHasMoreCommands()) {
            break;
        }

        if(p.commandType() == 'A' || p.commandType() == 'C') {
            curRom++;
        }

        if(p.commandType() == 'L' && !s.contains(p.symbol())) {
            s.addEntry(p.symbol(), curRom);
        }
    }

    Parser p2(testString);
    Code c;
    int freeMemory = 16;

    while(true) {
        p2.advance();

        if(!p2.getHasMoreCommands()) {
            break;
        }

        cout << p2.getCurrentLine() << endl;

        if(p2.commandType() == 'A') {
            if(p2.symbol().find_first_not_of("0123456789") == string::npos) {
                outfile << convertToAInstruction(p2.symbol()) << endl;
            } else {
                if(!s.contains(p2.symbol())) {
                    s.addEntry(p2.symbol(), freeMemory);
                    freeMemory++;
                }

                outfile << convertToAInstruction(to_string(s.getAdress(p2.symbol()))) << endl;
            }
        } else if(p2.commandType() == 'C') {
            outfile << "111" << c.comp(p2.compM()) << c.dest(p2.destM()) << c.jump(p2.jumpM()) << endl;
        }
    }
    
    outfile.close();

    return 0;
}

// Given the value, convert to a binary A instruction
string convertToAInstruction(string in) {
    string binary = bitset<16>(stoi(in)).to_string();
    binary[0] = '0';
    return binary;
}