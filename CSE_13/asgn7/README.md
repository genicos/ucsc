Authored by Nicolas Ayala

A compression algorithm implementation.

DEMO
----

For a demonstration, run the following commands:

make
./encode -v -i bible.txt -o OUT
./decode -v -i OUT -o rec_bible.txt

This will compress the bible, a large file, in a short amount of time

FILES PRESENT
-------------

Makefile - commands for building and testing program

encode.c - c code for encoding program

decode.c - c code for decoding program

code.h - Macros for program

endian.h - endian functions

bit.h - bit length

io.c - c code for io functionality of program

io.h - header file for io functions

trie.c - c code for Trie ADT

trie.h - header file for Trie ADT

word.c - c code for Word and WordTable structure

word.h - header file for Word and WordTable structure

test.c - c code for Test harness

DESIGN.pdf - Design of program

BUILD, CLEAN, TEST
------------------

command 'make all' will build encode and decode

command 'make clean' will delete object, executable, and test files

command 'make infer' will run infer on encode and decode

command 'make testval' will run valgrind on test program

TEST COMPLAINTS
---------------
INFER COMPLAINTS
	2 MEMORY_LEAKS - Both blocks of memory are still accesable by existing structs
	2 RESOURCE_LEAKS - Both files are still acessable 
	1 NULL_DEREFERENCE - this pointer is meant to be NULL and is accociated with the STOP_CODE, it wont be used

VALGRIND COMPLAINTS
	encode and decode passes with bible.txt, 0 errors, all memory freed
	

