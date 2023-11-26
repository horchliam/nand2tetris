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

  return "";
}

string Parser::destM() {
  if(commandType() != 'C') {
    cout << "Dest called on non C command" << endl;
    return "";
  }

  signed long equalPos = currentCommand.find('=');
  
  if(equalPos != string::npos) {
    return currentCommand.substr(0, equalPos);
  }

  return "";
}

string Parser::compM() {
  if(commandType() != 'C') {
    cout << "Comp called on non C command" << endl;
    return "";
  }

  signed long equalPos = currentCommand.find('=');
  signed long semiPos = currentCommand.find(';');

  if(equalPos != string::npos) {
    if(semiPos != string::npos) {
      return currentCommand.substr(equalPos + 1, semiPos - equalPos - 1);
    }

    return currentCommand.substr(equalPos + 1, currentCommand.length() - equalPos - 1);
  } else if(semiPos != string::npos) {
    return currentCommand.substr(0, semiPos);
  }

  return "";
}

string Parser::jumpM() {
  signed long semiPos = currentCommand.find(';');

  if(semiPos != string::npos) {
    return currentCommand.substr(semiPos + 1, currentCommand.length() - semiPos - 1);
  }

  return "";
}

string Parser::getCurrentLine() {
  return currentCommand;
}