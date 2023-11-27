#include <string>
#include <map>

using namespace std;

class SymbolTable {
    public:
    SymbolTable();
    void addEntry(string symbol, int address);
    bool contains(string symbol);
    int getAdress(string symbol);
    private:
    map<string, int> symbols;
    int freeAdress = 0;
};