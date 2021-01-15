Nicolas Ayala
nmayala@ucsc.edu

FILES PRESENT
-------------
Makefile - makes the program

stack.h - header file for stack structure

stack.c - code file for stack structure

pathfinder.c - code file with main and functionality

DESING.pdf - Design of program and answers to Pre-Lab question

WRITEUP.pdf - My thoughts on the questions

HOW TO BUILD PROGRAM
--------------------
Enter the command 'make' while in this directory

Makefile
--------
the command 'make' will build the program
	as will 'make pathfinder' and 'make all'

the command 'make clean' will delete object and executable files

the command 'make infer' will run infer on the code

stack.h and stack.c
-------------------
A stack, items of stack are uint32_t and default capacity is 26.
When capacity is reached, capacity doubles.

pathfinder.c
------------
Takes the following flags: -i <path_file> -u -d -m
	-i <path_file> specifies the file that encodes the graph of the maze
	-u means the graph is undirected
	-d means the graph is directed
	-m means the adjacency matrix will be printed
-u and -d are incompatible with eatchother 
A path file must be specified

This program uses a Depth First Search to find a path to get through the maze.

MAKE INFER COMPLAINTS
---------------------
make infer has two complaints for my program,
	One being a memmory leak in my stack constructor.
         this is excusable because the memmory is freed in the destructor.
	The other is a resource leak when I open the file
	 this is excusable because the file is closed after being read into the adjacency matrix.
 
