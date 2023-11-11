#include "Parser.hpp"

using namespace std;

Parser::Parser(string& x) {
  filename = x;
  fin.open(x);

  if (fin.fail()) {
    cout << x << " not found." << endl;
    exit(1);
  }
}

bool Parser::hasMoreCommands() {
  return true;
}

void Parser::printHelloFileName() {
  cout << "Hello " << filename << endl;
}