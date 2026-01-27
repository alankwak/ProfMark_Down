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

TEST_CASE("Code blocks")
{
    SECTION("Test")
    {
        string md = "``` file=\"main.cpp\" highlight=\"1-5\" \n```";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "<code></code>";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }
}

TEST_CASE("Inline")
{
    SECTION("Transfer text")
    {
        string md = "This is a sentence.\nThis is another sentence";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "This is a sentence.This is another sentence";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }

    SECTION("Image")
    {
        string md = "This is an ![image](image/link.png).";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        string output = getFileContent("./tests/HTMLFile.html");

        string desiredOutput = "This is an <img src=\"image/link.png\" alt=\"image\">.";

        REQUIRE(output == desiredOutput);
    }

    SECTION("Link")
    {
        string md = "This is a [link](https://google.com).";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        string output = getFileContent("./tests/HTMLFile.html");

        string desiredOutput = "This is a <a href=\"https://google.com\">link</a>.";

        REQUIRE(output == desiredOutput);
    }

    SECTION("Highlight")
    {
        string md = "This is some [<highlighted text>], maybe in code.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        string output = getFileContent("./tests/HTMLFile.html");

        string desiredOutput = "This is some <mark>highlighted text</mark>, maybe in code.";

        REQUIRE(output == desiredOutput);
    }

    SECTION("Bold")
    {
        string md = "This is some **bold** text.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        string output = getFileContent("./tests/HTMLFile.html");

        string desiredOutput = "This is some <strong>bold</strong> text.";

        REQUIRE(output == desiredOutput);
    }

    SECTION("Italics")
    {
        string md = "This is some *italicized* text.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        string output = getFileContent("./tests/HTMLFile.html");

        string desiredOutput = "This is some <em>italicized</em> text.";

        REQUIRE(output == desiredOutput);
    }

    SECTION("Inline code")
    {
        string md = "This is some `inline code`.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        string output = getFileContent("./tests/HTMLFile.html");

        string desiredOutput = "This is some <code>inline code</code>.";

        REQUIRE(output == desiredOutput);
    }

    SECTION("Headers")
    {
        // h1
        string md = "# This is an h1.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        string output = getFileContent("./tests/HTMLFile.html");

        string desiredOutput = "<h1>This is an h1.</h1>";

        REQUIRE(output == desiredOutput);

        // h2
        md = "## This is an h2.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase2("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        output = getFileContent("./tests/HTMLFile.html");

        desiredOutput = "<h2>This is an h2.</h2>";

        REQUIRE(output == desiredOutput);

        // h3
        md = "### This is an h3.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase3("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        output = getFileContent("./tests/HTMLFile.html");

        desiredOutput = "<h3>This is an h3.</h3>";

        REQUIRE(output == desiredOutput);

        // h4
        md = "#### This is an h4.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase4("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        output = getFileContent("./tests/HTMLFile.html");

        desiredOutput = "<h4>This is an h4.</h4>";

        REQUIRE(output == desiredOutput);

        // h5
        md = "##### This is an h5.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase5("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        output = getFileContent("./tests/HTMLFile.html");

        desiredOutput = "<h5>This is an h5.</h5>";

        REQUIRE(output == desiredOutput);

        // h6
        md = "###### This is an h6.";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase6("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        output = getFileContent("./tests/HTMLFile.html");

        desiredOutput = "<h6>This is an h6.</h6>";

        REQUIRE(output == desiredOutput);
    }

    SECTION("Horizontal line")
    {
        string md = "---";

        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
        string output = getFileContent("./tests/HTMLFile.html");

        string desiredOutput = "<hr/>";

        REQUIRE(output == desiredOutput);
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

        string desiredOutput = "This <em>is a sentence.This is another </em>sentence";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }

    SECTION("MultiLineBoth"){
        string md = "***This *is a sentence.\nThis is another *sentence***";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "<strong><em>This </em>is a sentence.This is another <em>sentence</strong></em>";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }

    SECTION("UnorderedlistOfStuff"){
        string md = "- list \n- of \n- things \n over";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "<ul><li>list </li><li>of </li><li>things </li></ul> over";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }

    SECTION("OrderedlistOfStuff"){
        string md = "1. list \n2. of \n3. things \n over";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "<ol><li>list </li><li>of </li><li>things </li></ol> over";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }

    SECTION("ProgramOutputStyle"){
        string md = "``` program-outputthis is program outputs \non multiple lines \nthat should be white on a black background\n```";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "<pre style = \"background-color: black; color: white; min-height: 150px; padding: 5px; overflow-y: auto\">program-output:\nthis is program outputs on multiple lines that should be white on a black background</pre>";
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