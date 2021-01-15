Written by Nicolas Ayala

This project creates an executable that finds word in a text file and 
replaces them with others, making use of a bloom filter

DEMO
----

For a demonstration, type the following commands:

make
./newspeak -i bible.txt

This will run the program using the bible as input


FILES PRESENT
-------------
Makefile - commands for building and testing program

newspeak.c - c code for main function

bf.c - c code for bloom filter

bf.h - header file for bloom filter

bv.c - c code for bit vector

bv.h - header file for bit vector

gs.c - c code for GoodSpeak struct and functions

gs.h - header file for GoodSpeak struct

hash.c - c code for Hash table

hash.h - header filer for Hash table

ll.c - c code for linked list

ll.h - header file for linked list

parser.c - c code for regex text parser

parser.h - header file for regex text parser

speck.c - c code for SPECK, used as a hash function

speck.h - header file for hash function

badspeak.txt - Contains forbidden words

newspeak.txt - Contains translatable words and their translations

random.txt - A piece of text for testing

bible.txt - King James biblels

DESIGN.txt - Answers to pre-lab questions and design of program

WRITEUP.txt - Post coding analysis questions

BUILD, CLEAN, TEST
------------------

command 'make all' will build entire program

command 'make clean' will delete object and executable files

command 'make infer' will run infer on code

command 'make valgrind' will run valgrind on code

TEST COMPLAINTS
---------------
INFER COMPLAINTS
	3 memory leaks in gc.c/gs_create(), This function actually returns a
pointer to the newly allocated memory so it is not leaked.
	1 resource leak in newspeak.c/main(), The file is actually freed at 
the end of main so no leaks.

VALGRIND COMPLAINTS
	No valgrind complaints, passes when tested on bible

