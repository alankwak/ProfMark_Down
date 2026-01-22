#define CATCH_CONFIG_NO_POSIX_SIGNALS
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <fstream>
#include <sstream>
#include "HTMLConverter.hpp"
#include "catch.hpp"
using namespace std;

void clearFile(string filePath);
void writeToFile(string filePath, string content);
string getFileContent(string filePath);

TEST_CASE("ph")
{
    clearFile("./tests/MarkdownFile.md");
    clearFile("./tests/HTMLFile.html");
    
    SECTION("Transfer text")
    {
        string md = "This is a sentence.\nThis is another sentence";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "This is a sentence.This is another sentence";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
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