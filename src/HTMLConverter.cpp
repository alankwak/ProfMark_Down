#include <iostream>
#include <fstream>
#include "HTMLConverter.hpp"
using namespace std;

HTMLConverter::HTMLConverter(string inPutFile, string outPutFile){
    //
    CaseConverter cases;
    cases.markdown = {"*", "**", "![", "]" "[", "#", "##", "###", "####", "#####", "######", "\n\n", "\n---\n"};
    cases.htmlStart = {"<i>", "<strong>", "<img src = ",  "alt = ", "a href = ", "<h1>", "<h2>", "<h3>", "<h4>", "<h5>", "<h6>", "<p>", "<hr>"};
    cases.htmlEnd = {"</i>", "</strong>", "/>", "</a>", "</h1>", "</h2>", "</h3>", "</h4>", "</h5>", "</h6>", "</p>", "</hr>"};
   
    readInFile(inPutFile, outPutFile);
}

//read in file
void HTMLConverter::readInFile(string inPut, string outPath){
    ifstream inPutFile(inPut);
    ofstream outPutFile(outPath);


    if(!inPutFile.is_open()) {
        cerr << "Error: could not open file: " << inPut << endl;
    }

    string line;
    while(getline(inPutFile, line)){
        //where we do things
        cout << line << endl;

        outPutFile << line;
    }

    inPutFile.close();
    outPutFile.close();

}