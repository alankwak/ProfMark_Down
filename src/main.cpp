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

    // SECTION("Highlight")
    // {
    //     string md = "This is some [<highlighted>] text.";

    //     writeToFile("./tests/MarkdownFile.md", md);
    //     HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");
    //     string output = getFileContent("./tests/HTMLFile.html");

    //     string desiredOutput = "This is some <mark>highlighted</mark> text.";

    //     REQUIRE(output == desiredOutput);
    // }

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

    SECTION("UnorderedlistOfStuff"){
        string md = "\n - list \n - of \n - things \n over";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "<ul><li> - list </li><li> - of </li><li> - things </li?</ul> over";
        string output = getFileContent("./tests/HTMLFile.html");

        REQUIRE(output == desiredOutput);
    }

    SECTION("OrderedlistOfStuff"){
        string md = "\n 1. list \n 2. of \n 3. things \n over";
        writeToFile("./tests/MarkdownFile.md", md);
        HTMLConverter testCase("./tests/MarkdownFile.md", "./tests/HTMLFile.html");

        string desiredOutput = "<ul><li>list </li><li>of </li><li>things </li?</ul> over";
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