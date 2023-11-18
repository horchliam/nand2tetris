// #include <iostream>
#include "Parser.hpp"

using namespace std;

int main()
{

    string testString = "../add/Add.asm";

    Parser p(testString);

    while(p.getHasMoreCommands()) {
        p.advance();
        cout << p.getCurrentLine() << endl;
    }
    
    return 0;
}