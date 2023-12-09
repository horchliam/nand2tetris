#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Parser {
    public:
    Parser(string& in); // in is a reference to a string object

    bool hasMoreCommands();

    void advance();

    string getCurrentLine();
    private:
    ifstream fin;
    string currentLine = "";
    bool moreCommands = true;
};