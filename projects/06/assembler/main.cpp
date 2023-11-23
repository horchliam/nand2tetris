#include "Parser.hpp"
#include "Code.hpp"

using namespace std;

int main()
{

    string testString = "../rect/Rect.asm";

    Parser p(testString);

    Code c;

    while(p.getHasMoreCommands()) {
        p.advance();
        cout << p.getCurrentLine() << " command type: " << p.commandType() << " comp: " << p.compM() << " dest: " << p.destM() << " symbol: " << p.symbol() << endl;
    }
    
    return 0;
}