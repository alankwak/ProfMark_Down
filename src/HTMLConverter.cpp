#include <iostream>
#include <fstream>
#include "HTMLConverter.hpp"
using namespace std;

HTMLConverter::HTMLConverter(string inPutFile, string outPutFile){
    readInFile(inPutFile);
}

//read in file
void HTMLConverter::readInFile(string path){
    ifstream file(path);

    if(!file.is_open()) {
        cerr << "Error: could not open file: " << path << endl;
    }

    string line;
    while(getline(file, line)){
        //where we do things
        cout << line << endl;
    }
    file.close();

}