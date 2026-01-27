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
        vector <string> markdownStart = {"###### ", "##### ", "#### ", "### ", "## ", "# ",  "---", "\n\n"};
        vector <string> markdownAnywhere = {"`"};
        vector <string> multiLine = {"**", "*", "\n\n"};
        unordered_map <string, int> symbolCount = {{"**" , 0}, {"*", 0 }};
        unordered_map <string, string> htmlStart = {
            {"*", "<em>"}, 
            {"**", "<strong>"}, 
            {"# ","<h1>"}, 
            {"## ", "<h2>"}, 
            {"### ", "<h3>"}, 
            {"#### ", "<h4>"}, 
            {"##### ", "<h5>"}, 
            {"###### ", "<h6>"}, 
            {"\n\n", "<p>"}, 
            {"---", "<hr/>"},
            {"`", "<code>"}
        };
        unordered_map <string, string> htmlEnd = {
            {"*", "</em>"}, 
            {"**", "</strong>"}, 
            {"# ","</h1>"}, 
            {"## ", "</h2>"}, 
            {"### ", "</h3>"}, 
            {"#### ", "</h4>"}, 
            {"##### ", "</h5>"}, 
            {"###### ", "</h6>"}, 
            {"\n\n", "</p>"}, 
            {"---", ""},
            {"`", "</code>"}
        };

        string handleCodeBlock(string& line, bool& inCode);
        void parseMultiline(string& line);
        bool inList = false;
        void lists(string& line);
        int paraCount = 1;
        void parsePara(string& line);
        string parseInline(string& line);
        bool inListOrd = false;
        bool inListUn = false;
        int ordList = 1;

        void specialCases(string& line);
};