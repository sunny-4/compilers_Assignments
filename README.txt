Name: Mamilla Aniruddh Reddy
Roll Number: 23110195
Email: your.email@iitgn.ac.in
Programming Language Used (Part 3): C


TOKENIZER README
================

COMPILATION
-----------
To compile the tokenizer program, use the following command:

    gcc tokenizer.c -o tokenizer

This will create an executable file named 'tokenizer.exe' (on Windows) or 'tokenizer' (on Unix-like systems).


USAGE
-----
To run the tokenizer, use input/output redirection:

    tokenizer < inputfile > outputfile

Where:
- inputfile  : The source file to be tokenized
- outputfile : The output file where tokens will be written


EXAMPLE
-------
    gcc tokenizer.c -o tokenizer
    tokenizer < source.txt > tokens.txt

This will read from 'source.txt' and write the tokenized output to 'tokens.txt'.


NOTES
-----
- Ensure tokenizer.c exists in the current directory before compiling
- The program reads from standard input and writes to standard output
- Use redirection operators (< and >) to specify input and output files

Known Issues/Limitations:

The issue is that we have not included a sufficient number of keywords eg: for is identified as indentifier , and the buffer size is also limiting our implementation.