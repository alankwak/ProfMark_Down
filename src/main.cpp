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

    SECTION("multiLineBold")
    {
        string md = "**This is a sentence.\nThis is another sentence**";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "<strong>This is a sentence.This is another sentence</strong>";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }
   SECTION("multiLinePara")
    {
        string md = "This is a sentence.\n\nThis is another sentence\n\n";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "This is a sentence.<p>This is another sentence</p>";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    } 

    SECTION("multiLineItalic"){
        string md = "This *is a sentence.\nThis is another *sentence";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "This <i>is a sentence.This is another </i>sentence";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }

    SECTION("MultiLineBoth"){
        string md = "***This *is a sentence.\nThis is another *sentence***";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "<strong><i>This </i>is a sentence.This is another <i>sentence</strong></i>";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }
}

void clearFile(string filePath) {
    ofstream file(filePath);
    if(!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
    }
    file.close();
}

void writeToFile(string filePath, string content) {
    ofstream file(filePath);
    if(!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }
    file << content;
    file.close();
}

string getFileContent(string filePath) {
    ifstream file(filePath);
    if(!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return "Error opening file";
    }
    ostringstream ss;
    ss << file.rdbuf();
    file.close();

    return ss.str();
}