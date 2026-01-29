# ProfMark_Down Development Guide

This document describes how to get set up to contribute to the development of **ProfMark_Down**.

## Setting up your development environment

The easiest way to get started is to use **GitHub Codespaces**. Starting on the page of any branch on the GitHub website, select the green `<> Code` dropdown, navigate to the `Codespaces tab, and create a new codespace. 
You should then be able to write code and run the program in the cloud.

Alternatively, if you want to develop on your local machine, make sure you have **C++11** or higher installed on your system and run
```
git clone https://github.com/alankwak/ProfMark_Down
```
to clone the repository.

## Project structure

### Directory structure

All source code for the project is in the `src/` folder. This is where you should make the majority of your contributions. The `tests/` folder contains placeholder Markdown and HTML files used to test that content is correctly transferred from .md to .html.

### Code

The code revolves around an `HTMLConverter` class, which has functions that handle the conversions of each feature. Some features are similar enough that they can be handled through one function, such as bold and italics, while others are different enough to warrant their own functions. The class also holds maps to easily get the starting and ending HTML tags for the corresponding Markdown symbols. Converting a document from markdown to HTML is as easy as specifying the file paths of the input markdown file and the output HTML file in the class's constructor.

## Adding new features

You can make changes to or add new code once you have the repository set up for development. 
Once you have tested your code and are ready to make a contribution, make a pull request to the main branch of this repository.
Repository owners will review each pull request and either approve or close it.

## Testing conventions

This project uses the C++ "Catch" testing framework (version v2.7.0). More information about the framework can be found [here](https://github.com/catchorg/Catch2).
In general, though, tests follow this general format:

```
TEST_CASE("Feature")
{
  SECTION("Sub-feature")
  {
  // test setup
  // ...
  REQUIRE("Test condition");
  }
  ...
}
```

Please make sure all tests pass before submitting a pull request.

