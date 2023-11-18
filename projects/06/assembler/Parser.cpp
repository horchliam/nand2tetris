#include "Parser.hpp"

using namespace std;

Parser::Parser(string& x) {
  fin.open(x);

  if (fin.fail()) {
    cout << x << " not found." << endl;
    exit(1);
  }

  commandTable['@'] = 'A';
  commandTable['A'] = 'C';
  commandTable['D'] = 'C';
  commandTable['M'] = 'C';
  commandTable['0'] = 'C';
  commandTable['1'] = 'C';
  commandTable['-'] = 'C';
  commandTable['!'] = 'C';
  commandTable['('] = 'L';
}

bool Parser::getHasMoreCommands() {
  return hasMoreCommands;
}

void Parser::advance() {
  string currentLine;
  signed long commentPos;
  bool commandFound = false;

  while(!commandFound && getline(fin, currentLine)) {

    currentLine.erase(remove_if(currentLine.begin(), currentLine.end(), ::isspace), currentLine.end());

    commentPos = currentLine.find("//");
    if (commentPos != string::npos) {
      currentLine.erase(commentPos, currentLine.length() - commentPos);
    }

    commandFound = !currentLine.empty();
  }

  hasMoreCommands = commandFound;
  currentCommand = currentLine;
}

char Parser::commandType() {
  return 'x';
}

string Parser::symbol() {
  return "Not yet implemented";
}

string Parser::destM() {
  return "Not yet implemented";
}

string Parser::compM() {
  return "Not yet implemented";
}

string Parser::jumpM() {
  return "Not yet implemented";
}

string Parser::getCurrentLine() {
  return currentCommand;
}