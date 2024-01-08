#include <iostream>

#include "JackTokenizer.h"

using namespace std;

int main(int argc, char *argv[]) {
    JackTokenizer j("Test.jack");

    int i = 0;

    while(j.hasMoreTokens()) {
        j.advance();
    }

    return 0;
}