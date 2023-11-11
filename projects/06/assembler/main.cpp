// #include <iostream>
#include "Parser.hpp"

using namespace std;

int main()
{

    string testString = "./test.txt";

    Parser p(testString);

    p.printHelloFileName();
}