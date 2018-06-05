# cipher-fun
A few cipher encryption algorithms I have implemented as part of a University security course project including a Caesar Cipher crack
# Overview
I took a course at the University of New South Wales in Sydney - COMP6441 Security Engineering and Cyber Security. As part of this course was a 'Something Awesome' project which required us to pick our own assignment, and challenge ourselves to complete a project throughout the semester.
My project was to implement a few cipher algorithms from history.
# Ciphers
Implemented in the C programming language, the ciphers are;
Caesar Cipher
Mono-alphabetic Substitution cipher
Railfence cipher
Vigenere cipher
Baconian cipher

I also wrote a program that is able to break the Caesar cipher using the cumulative chi-squared test statistic.
# Usage
Make sure with the crack.c program to compile with the -lm flag, in order for the power function to work.
cipher.c ./cipher <filename> <ciphertype> <argument>
crack.c ./crack <filename> <ciphertype> <argument>
for cipher type, just name the ciphers e.g. "caesar", "subsitution", "railfence" etc...
