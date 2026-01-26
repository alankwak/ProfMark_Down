#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class HTMLConverter{
    public:
    HTMLConverter(string inPutFile, string outPutFile);
    void readInFile(string inPut, string outPath);
    private:
        vector <string> markdownStart = {"###### ", "##### ", "#### ", "### ", "## ", "# ",  "\n---\n", "\n\n"};
        vector <string> markdownAnywhere = {"**", "*", "![", "]", "["};
        vector <string> multiLine = {"**", "*"};
        unordered_map <string, string> htmlStart = {{"*", "<i>"}, {"**", "<strong>"}, {"# ","<h1>"}, {"## ", "<h2>"}, {"### ", "<h3>"}, {"#### ", "<h4>"}, {"##### ", "<h5>"}, {"###### ", "<h6>"}, {"\n\n", "<p>"}, {"\n---\n", "<hr>"}};
        unordered_map <string, string> htmlEnd = {{"*", "</i>"}, {"**", "</strong>"}, {"# ","</h1>"}, {"## ", "</h2>"}, {"### ", "</h3>"}, {"#### ", "</h4>"}, {"##### ", "</h5>"}, {"###### ", "</h6>"}, {"\n\n", "</p>"}, {"\n---\n", "</hr>"}};
        unordered_map <string, int> symbolCount = {{"**", 0}, {"*", 0}};


        void parseMultiline(string& line);
        void parseInline(string& line);
};