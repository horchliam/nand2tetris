#include <string>
#include <map>
#include <iostream>

using namespace std;

class Code {
    public:
    Code();

    string dest(string input);

    string comp(string input);

    string jump(string input);
    private:
    map<string, string> jumpTable;
    map<string, string> compTable;
    map<string, string> destTable;
};