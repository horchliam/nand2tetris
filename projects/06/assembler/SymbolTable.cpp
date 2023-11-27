#include "SymbolTable.hpp"

SymbolTable::SymbolTable() {
    symbols["SP"] = 0;
    symbols["LCL"] = 1;
    symbols["ARG"] = 2;
    symbols["THIS"] = 3;
    symbols["THAT"] = 4;
    symbols["R0"] = 0;
    symbols["R1"] = 1;
    symbols["R2"] = 2;
    symbols["R3"] = 3;
    symbols["R4"] = 4;
    symbols["R5"] = 5;
    symbols["R6"] = 6;
    symbols["R7"] = 7;
    symbols["R8"] = 8;
    symbols["R9"] = 9;
    symbols["R10"] = 10;
    symbols["R11"] = 11;
    symbols["R12"] = 12;
    symbols["R13"] = 13;
    symbols["R14"] = 14;
    symbols["R15"] = 15;
    symbols["SCREEN"] = 16384;
    symbols["KBD"] = 24576;
}

void SymbolTable::addEntry(string symbol, int address) {
    symbols[symbol] = address;
}

bool SymbolTable::contains(string symbol) {
    return symbols.count(symbol);
}

int SymbolTable::getAdress(string symbol) {
    return symbols[symbol];
}