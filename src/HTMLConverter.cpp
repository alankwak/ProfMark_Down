#include <iostream>
#include <fstream>
#include <stack>
#include "HTMLConverter.hpp"
using namespace std;

HTMLConverter::HTMLConverter(string inPutFile, string outPutFile){
    string s = "### This **is** a *header* and this is some `code`.";
    cout << parseInline(s) << endl;
    readInFile(inPutFile, outPutFile);
}

//read in file
void HTMLConverter::readInFile(string inPut, string outPath){
    ifstream inPutFile(inPut);
    ofstream outPutFile(outPath);


    if(!inPutFile.is_open()) {
        cerr << "Error: could not open file: " << inPut << endl;
    }

    // set up bools

    string line;
    while(getline(inPutFile, line)){
        //where we do things

        parseMultiline(line);

        parseInline(line);

        outPutFile << line;
    }

    inPutFile.close();
    outPutFile.close();

}

void HTMLConverter::parseMultiline(string& line) {

}

string HTMLConverter::parseInline(string& line) {
    stack<string> symbolStack;
    string newLine;

    int startingIndex = 0;

    for(string& symbol : markdownStart) {
        if(symbol.length() <= line.length() && line.substr(0, symbol.length()) == symbol) {
            newLine += htmlStart[symbol];
            symbolStack.push(symbol);
            startingIndex = symbol.length();
            break;
        }
    }

    for(int i = startingIndex; i < line.length(); i++) {
        bool found = false;
        for(string& symbol : markdownAnywhere) {
            if(i + symbol.length() <= line.length() && line.substr(i, symbol.length()) == symbol) {
                if(!symbolStack.empty() && symbolStack.top() == symbol) {
                    // ending symbol
                    newLine += htmlEnd[symbol];
                    symbolStack.pop();
                } else {
                    // starting symbol
                    newLine += htmlStart[symbol];
                    symbolStack.push(symbol);
                }
                i += symbol.length()-1;
                found = true;
                break;
            }
        }

        if(!found) {
            newLine += line[i];
        }
    }

    while(!symbolStack.empty()) {
        newLine += htmlEnd[symbolStack.top()];
        symbolStack.pop();
    }

    return newLine;
}