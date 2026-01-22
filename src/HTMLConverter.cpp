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
    vector < vector <int> > indexVals;
    //itterating through and grabbing indexs of markdown symbols
    for(int i = 0; i < line.length(); i++){
        for(int j = 0 ; j < multiLine.size() ; j++){
            if(line.substr(i, multiLine[j].size()) == multiLine[j]){
                vector <int> 
                indexVals.push_back({i, i + multiLine[j].size()});
            }
        }
    }
}

void HTMLConverter::parseInline(string& line) {
    
}