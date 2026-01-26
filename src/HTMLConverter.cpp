#include <iostream>
#include <fstream>
#include "HTMLConverter.hpp"
using namespace std;

HTMLConverter::HTMLConverter(string inPutFile, string outPutFile){
    //
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

        cout << line << endl;

        outPutFile << line;
    }

    inPutFile.close();
    outPutFile.close();

}

void HTMLConverter::parseMultiline(string& line) {

    // Itterating through and grabbing indexs of markdown symbols
    for (int i = 0; i < line.length(); i++) {
        for (int j = 0; j < multiLine.size(); j++) {
            // Individualizes each vector entry for simplified searching
            string markDown = multiLine[j];

            if (line.substr(i, markDown.size()) == markDown) {

                // Decide whether this is a start or end tag
                string replacement;
                if (symbolCount[markDown] % 2 == 0) {
                    replacement = htmlStart[markDown];
                } else {
                    replacement = htmlEnd[markDown];
                }

                // Replace markdown with HTML
                line.replace(i, markDown.size(), replacement);

                // Update counter
                symbolCount[markDown] += 1;

                // Move symbolCount forward to avoid re-processing previously added HTML
                i += replacement.length() - 1;
                break;
            }
        }
    }
}

void HTMLConverter::parseInline(string& line) {
    
}