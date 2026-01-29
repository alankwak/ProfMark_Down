#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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
        string highlightLines(vector<int>& lower, vector<int>& upper);
        vector<int> highlightRanges;
        unordered_set<int> highlightSingle;
        bool isInRanges(int lineNumber);

        void parseMultiline(string& line);
        void lists(string& line);
        int paraCount = 1;
        void parsePara(string& line);
        string parseInline(string& line);
        bool inListOrd = false;
        bool inListUn = false;
        int ordList = 1;
        bool inProgOutput = false;
        void programOutputParse(string& line);

        void getHighlighting(string highlighting);
        void specialCases(string& line);
        void highlightCase(string& line);
};