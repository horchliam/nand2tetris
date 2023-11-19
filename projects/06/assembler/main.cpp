// #include <iostream>
#include "Parser.hpp"

using namespace std;

int main()
{

    string testString = "../rect/Rect.asm";

    Parser p(testString);

    while(p.getHasMoreCommands()) {
        p.advance();
        if(!p.jumpM().empty()) {
            cout << p.jumpM() << endl;
        }
    }
    
    return 0;
}