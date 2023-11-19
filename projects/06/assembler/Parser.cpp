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
  if(commandTable.find(currentCommand[0]) != commandTable.end()) {
    return commandTable[currentCommand[0]];
  }

  cout << "Invalid command" << endl;
  return 'X';
}

string Parser::symbol() {
  if(commandType() == 'A' || commandType() == 'L') {
    string result = currentCommand;

    result.erase(remove(result.begin(), result.end(), '@'), result.end());
    result.erase(remove(result.begin(), result.end(), '('), result.end());
    result.erase(remove(result.begin(), result.end(), ')'), result.end());

    return result;
  }

  cout << "No symbol in current command" << endl;
  return "";
}

string Parser::destM() {
  return "Not yet implemented";
}

string Parser::compM() {
  return "Not yet implemented";
}

string Parser::jumpM() {
  signed long semiPos = currentCommand.find(';');

  if(semiPos != string::npos) {
    return currentCommand.substr(semiPos, currentCommand.length());
  }

  cout << "No jump command found" << endl; 
  return "";
}

string Parser::getCurrentLine() {
  return currentCommand;
}