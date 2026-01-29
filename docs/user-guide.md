# USER GUIDE:

To use the program, pass the path to your Markdown file to the HTMLConverter constructor as the first parameter. 
As the second parameter, enter the file path where you want the converted HTML saved.
When you run the code, it will translate your Markdown into HTML and write it to your HTML file. 

## What is ProfMarkDown?

ProfMarkDown is an extension of traditional Markdown. Markdown uses specific formatting conventions to convert text into HTML elements and styles. For example, surrounding text with \*\*two asterisks\*\* will result in the text showing up **bold**. ProfMarkDown implements many of the same formatting conventions as Markdown, but also extends code block functionality and makes certain elements easier to write. For example, a code block can usually be created in Markdown using three backticks to start and three more to end it. ProfMarkDown keeps this syntax but adds arguments placed after the first three backticks. One such argument is `file="{filename}"`, which creates a file name at the start of the code block to represent the file the code is in.
