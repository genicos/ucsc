FILES PRESENT
-------------
Makefile - makes program, cleans directory, runs infer

sequence.c - c code for main functionality of program

sieve.c - c code for sieve of eratosthenes

bv.c - c code for bit vector

sieve.h - header file for sieve

bv.h - header file for bit vector

DESIGN.pdf - design of program

HOW TO BUILD
------------
In this directory, enter command "make" to build program to the executable
	sequence

Makefile
--------
Makefile supports the following commands
'make' - builds executable
'make clean' - removes executable and object files
'make infer' - runs infer on all .c files

sequence.c
----------
N is 1000 as default
Program sieves all primes up to N
The program takes the following option flags
	-s , specifies that the primes will be printed and noted if they are 
		fibonnaci, lucas, or mersenne primes
	-p , specifies that the primes that are palindromes in base 2, 10, 11, 14
		will be printed
	-n <value> , specifies N

sieve.c
-------
Sieve of eratosthenes implemented by Darrel Long, with a small tweak

bv.c
----
A bit vector implementation will the ability to set bits, clear bits,
	set all bits, clear all bits, and return a bit.

INFER COMPLAINTS
----------------
Running infer on the code creates one complaint.
	a MEMORY LEAK in bv.c, this is excusable because all bit vectors are 
		freed at a later point in the code.

