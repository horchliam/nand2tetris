#include "Parser.hpp"
#include "Code.hpp"
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
    string testString = "../add/Add.asm";
    Parser p(testString);
    Code c;

    while(true) {
        p.advance();

        if(!p.getHasMoreCommands()) {
            break;
        }

        cout << p.getCurrentLine() << endl;
        
        if(p.commandType() == 'A') {
            outfile << convertToAInstruction(p.symbol()) << endl;
        } else if(p.commandType() == 'C') {
            outfile << "111" << c.comp(p.compM()) << c.dest(p.destM()) << c.jump(p.jumpM()) << endl;
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