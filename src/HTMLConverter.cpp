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

    outPutFile << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n\t<meta charset=\"UTF-8\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\t<title>ProfMarkDown</title>\n</head>\n<body>\n";

    if(!inPutFile.is_open()) {
        cerr << "Error: could not open file: " << inPut << endl;
    }

    bool inCode = false;
    int lineCounter = 0;
    string line;
    while(getline(inPutFile, line)){
        //where we do things

        programOutputParse(line);

        line = handleCodeBlock(line, inCode);

        if(inCode) {
            highlightCase(line);
            if(isInRanges(lineCounter) || highlightSingle.count(lineCounter)) {
                line.insert(0, "<mark>");
                line += "</mark>";
            }
            lineCounter++;
        } else {
            highlightRanges.clear();
            highlightSingle.clear();
            lineCounter = 0;
            parseMultiline(line);
            parsePara(line);
            line = parseInline(line);
        }

        lists(line);

        outPutFile << line;
    }

    outPutFile << "</body>\n</html>";

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

void HTMLConverter::parsePara(string& line){
    //finds out if the line is empty
    if(line == "" or line == "\n"){
        //if paraCount is even add end html tag (start counter at 1) otherwise add start tag
        if(paraCount % 2 == 0){
            line += "</p>";
        }else{
            line += "<p>";
        }
        //add one to para count
        paraCount++;
    }
}

string HTMLConverter::handleCodeBlock(string& line, bool& inCode) {
    string newLine;
    // check if line starts with ```
    if(line.length() >= 3 && line.substr(0, 3) == "```") {
        if(!inCode) {
            newLine += "<pre><code>";
            regex pattern(R"(\s([^=\s]+)=\"([^=\s]+)\")");
            sregex_iterator iter(line.begin(), line.end(), pattern);
            sregex_iterator end;

            while(iter != end) {
                smatch match = *iter;
                
                string setting = match[1];
                string option = match[2];

                if(setting == "file") {
                    newLine += "\n<span class=\"file-name\">";
                    newLine += match[2];
                    newLine += "</span>";
                } else if(setting == "highlight") {
                    getHighlighting(option);
                    // for(auto& n : highlightRanges) {
                    //     cout << n;
                    // }
                    // cout << endl;
                    // for(auto& n : highlightSingle) {
                    //     cout << n;
                    // }
                    // cout << endl;
                }

                // cout << "Setting: " << match[1] << endl;
                // cout << "Option: " << match[2] << endl;
                
                iter++;
            }
        } else {
            newLine += "</code></pre>";
        }
        
        inCode = !inCode;
        return newLine;
    }
    return line;
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

    specialCases(newLine);

    return newLine;
}

void HTMLConverter::lists(string& line){
//finds if line starts with dash if no dash found see if inlist and if true add end tag and assign inListUn to false
    if (line.rfind("- ", 0) == 0) {
        //if not in list yet do starting tag and assign inListUn to true otherwise add list tags to line
        if (!inListUn) {
            line = "<ul><li>" + line.substr(2) + "</li>";
            inListUn = true;
        } else {
            line = "<li>" + line.substr(2) + "</li>";
        }
    } else {
        if (inListUn) {
            line = "</ul>" + line;
            inListUn = false;
        }
    }

    if(line[0] > 49 && line[0] < 57 && line[1] == '.'){
        if(inListOrd == true){
            line = "<li>" + line.substr(3) + "</li>";
        }
    }else{
        if(inListOrd){
            line = "</ol>" + line;
            inListOrd = false; 
        }
    }

    if(line.rfind("1. ", 0) == 0){
        if(!inListOrd){
            line = "<ol><li>" + line.substr(3) + "</li>";
            inListOrd = true;
        }
    }
}

 void HTMLConverter::specialCases(string& line) {
    //Handle image case
    line = regex_replace(line, regex(R"(!\[([^\]]*)\]\(([^\)]+)\))"), "<img src=\"$2\" alt=\"$1\">");
    //Hand link case
    line = regex_replace(line, regex(R"(\[([^\]]+)\]\(([^)]+)\))"), "<a href=\"$2\" target=\"_blank\" rel=\"noopener noreferrer\">$1</a>");
}
void HTMLConverter::highlightCase(string& line) {
    //Handle highlight case
    line = regex_replace(line, regex(R"(\[<((?:(?!\[<|>\]).)*)>\])"), "<span style=\"background-color: green\">$1</span>");   
}
void HTMLConverter::programOutputParse(string& line){
    if(line.rfind("```program-output", 0) == 0){
        inProgOutput = true;
        line = "<pre style = \"background-color: black; color: white; min-height: 150px; padding: 5px; overflow-y: auto\">program-output:\n" + line.substr(17);
    }
    if(line.rfind("```", 0) == 0 && inProgOutput){
        line = line.substr(3) + "</pre>";
        inProgOutput = false;
    }
}
void HTMLConverter::getHighlighting(string highlighting) {
    int pos = 0;
    int len = highlighting.length();

    while(pos < len) {
        auto nextComma = highlighting.find(',', pos);

        int segmentLen;
        if(nextComma < 0 || nextComma > len) {
            segmentLen = len - pos;
        } else {
            segmentLen = nextComma - pos;
        }

        string segment = highlighting.substr(pos, segmentLen);

        auto dash = segment.find('-');

        if(dash >= 0 && dash < segment.length()) {
            int start = stoi(segment.substr(0, dash));
            int end = stoi(segment.substr(dash + 1));

            highlightRanges.push_back(start);
            highlightRanges.push_back(end);
        } else {
            highlightSingle.insert(stoi(segment));
        }
        if(nextComma == string::npos) break;
        pos = nextComma + 1;
    }
}

bool HTMLConverter::isInRanges(int lineNumber) {
    for(int i = 0; i < highlightRanges.size(); i += 2) {
        if(lineNumber >= highlightRanges[i] && lineNumber <= highlightRanges[i+1]) {
            return true;
        }
    }
    return false;
}