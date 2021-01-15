Authored by Nicolas Ayala

An implementation of many common sorting algorithms

DEMO
----

For a demonstration, type the following commands

make
./sorting -A

This will dislpay the output of every sorting algorithm

FILES PRESENT
-------------
Makefile - commands for building program

sorting.c - c code for main function

bubble.h - header for bubble sort

bubble.c - c code for bubble sort

shell.h - header for shell sort

shell.c - c code for shell sort

quick.h - header for quick sort

quick.c - c code for quick sort

binary.h - header for binary insertion sort

binary.c - c code for binary insertion sort

merge.h - header for merge sort

merge.c - c code for merge sort

DESIGN.pdf - Answers to pre-lab questions and design of program

WRITEUP.pdf - Post coding analysis questions

BUILD, CLEAN, TEST
------------------

command 'make' will build entire program

command 'make clean' will delete object files and executable

command 'make infer' will run infer on code

command 'make valgrind' will run valgrind on code

TEST COMPLAINTS
---------------

valgrind and infer did not produce any complaints
