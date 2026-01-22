#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HTMLConverter{
    public:
    HTMLConverter(string inPutFile, string outPutFile);
    void readInFile(string inPut, string outPath);
    private:
    struct CaseConverter {
        vector <string> markdown;
        vector <string> htmlStart;
        vector <string> htmlEnd;
    };
};