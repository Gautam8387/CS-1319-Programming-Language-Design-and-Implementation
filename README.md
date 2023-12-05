# CS-1319-Programming-Language-Design-and-Implementation

## Course Description
This course is an introduction to the design and implementation of programming languages. Topics include the six phases of a compiler, lexical analysis, parsing, symbol tables, type checking, code generation, and optimization.

The assignments cover these topics. They are steps to generate a compiler for a subset of the C language -- nanoC.

## Assignmen 1
This assignment is to understand the ```x86``` assembly language.

## Assignment 2
This assignment is to write a lexical analyzer for nanoC. The lexical analyzer is implemented using ```Lex```.

## Assignment 3
This assignment is to write a parser for nanoC. The parser is implemented using ```Bison```. Modified the lexer accordingly.

## Assignment 4
This assignment is to write a symbol table for nanoC. We also generate the intermediate (three address) code and Quads for nanoC. The symbol table and intermediate code is implemented using ```C```.

## Assignment 5
This assignment is to generate the target code translator from the TAC quad array (with the supporting symbol table, and other auxiliary data structures) to the assembly language of ```x86/IA-32/x86-64```. The translation is now machine-specific and your generated assembly code would be translated with the gcc assembler to produce the final executable codes for the ```nanoC``` program.