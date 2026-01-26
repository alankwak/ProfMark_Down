#include <iostream>
#include <fstream>
#include <regex>
#include <stack>
#include "HTMLConverter.hpp"
using namespace std;

HTMLConverter::HTMLConverter(string inPutFile, string outPutFile){
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

        line = parseInline(line);

        outPutFile << line;
    }

    inPutFile.close();
    outPutFile.close();

}

void HTMLConverter::parseMultiline(string& line) {
    unordered_map <string, int> symbolCount;

    // Itterating through and grabbing indexs of markdown symbols
    for (int i = 0; i < line.length(); i++) {
        for (int j = 0; j < multiLine.size(); j++) {
            // Individualizes each vector entry for simplified searching
            string markDown = multiLine[j];

            if (line.substr(i, markDown.size()) == markDown) {

                // Decide whether this is a start or end tag
                bool isStart = (symbolCount[markDown] % 2 == 0);
                string replacement = isStart ? htmlStart[markDown] : htmlEnd[markDown];

                // Replace markdown with HTML
                line.replace(i, markDown.size(), replacement);

                // Update counter
                symbolCount[markDown]++;

                // Move symbolCount forward to avoid re-processing previously added HTML
                i += replacement.length() - 1;
                break;
            }
        }
    }
}

string HTMLConverter::parseInline(string& line) {
    stack<string> symbolStack;
    string newLine;

    int startingIndex = 0;

    for(string& symbol : markdownStart) {
        if(symbol.length() <= line.length() && line.substr(0, symbol.length()) == symbol) {
            newLine += htmlStart[symbol];
            symbolStack.push(htmlEnd[symbol]);
            startingIndex = symbol.length();
            break;
        }
    }

    for(int i = startingIndex; i < line.length(); i++) {
        bool found = false;
        for(string& symbol : markdownAnywhere) {
            if(i + symbol.length() <= line.length() && line.substr(i, symbol.length()) == symbol) {
                if(!symbolStack.empty() && symbolStack.top() == htmlEnd[symbol]) {
                    // ending symbol
                    newLine += htmlEnd[symbol];
                    symbolStack.pop();
                } else {
                    // starting symbol
                    newLine += htmlStart[symbol];
                    symbolStack.push(htmlEnd[symbol]);
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
        newLine += symbolStack.top();
        symbolStack.pop();
    }

    return newLine;
}
 string HTMLConverter::specialCases(string& line) {
    regex image()
 }