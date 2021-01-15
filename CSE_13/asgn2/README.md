Nicolas Ayala
nmayala@ucsc.edu

FILES PRESENT
-------------
DESIGN.pdf - answers to pre labs and design of program

math.c - C code for program, implementation of sin, cos, tan, and exp

MakeFile - Make file for math program

WRITEUP.pdf - Analysis of difference between implementations in math and library implementations

HOW TO BUILD PROGRAM
--------------------
Enter the command 'make' in the directory of this readme

Makefile
--------
the command 'make' will build the program

the command 'make clean' will delete object and executable files

the command 'make infer' will run infer on the c code

math.c
------
Takes the option flags -s -c -t -e -a
	-s displays my implementation and the 
	  libraries implementation of sine in the range(-2pi,2pi)
	-c displays my implementation and the 
	  libraries implementation of cosine in the range(-2pi,2pi)
	-t displays my implementation and the 
	  libraries implementation of tangent in the range(-pi+0.001, pi-0.001)
	-e displays my implementation and the 
	  libraries implementation of exponent in the range(0,10) 
	-a displays all the above
 
