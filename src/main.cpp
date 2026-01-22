#include <iostream>
#include <fstream>
#include <sstream>
#include "HTMLConverter.hpp"
#include "catch.hpp"
using namespace std;

void clearFile(string filePath);
void writeToFile(string filePath, string content);
string getFileContent(string filePath);

// int main() {
//     HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
//     return 0;
// }

TEST_CASE("ph")
{
    clearFile("./tests/MarkdownFile.md");
    clearFile("./tests/HTMLFile.html");
    
    SECTION("Transfer text")
    {
        string md = "This is a sentence.\nThis is another sentence";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        cout << getFileContent("./tests/HTMLFile.html");
    }

    SECTION("Bold")
    {
        string md = "This is some **bold** text.";

    }
}

void clearFile(string filePath) {
    ofstream file(filePath);
    if(!file) {
        cout << "Error opening file: " << filePath << endl;
    }
    file.close();
}

void writeToFile(string filePath, string content) {
    ofstream file(filePath);
    if(!file) {
        cout << "Error opening file: " << filePath << endl;
        return;
    }
    file << content;
    file.close();
}

string getFileContent(string filePath) {
    ifstream file(filePath);
    if(!file) {
        cout << "Error opening file: " << filePath << endl;
        return "Error opening file";
    }
    ostringstream ss;
    ss << file.rdbuf();
    file.close();

    return ss.str();
}