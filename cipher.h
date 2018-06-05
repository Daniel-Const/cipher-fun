#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER 1000

void caesar(char line[BUFFER], int shift, int length);
void convertToAscii(char line[BUFFER], int length);
void convertToNumbers(char line[BUFFER]);
int punct(char c);
char punctreverse(int c);
void substitution(char line[BUFFER], char subs[25], int length);
int vigenere(char line[BUFFER], char key[BUFFER], int rem, int length);
void rail_fence(FILE* fp, int x, int y);
int count(FILE *fp);
void bacon(char line[BUFFER], int length);

const char* table[26] =
{
  "aaaaa",
  "aaaab",
  "aaaba",
  "aaabb",
  "aabaa",
  "aabab",
  "aabba",
  "aabbb",
  "abaaa",
  "abaab",
  "ababa",
  "ababb",
  "abbaa",
  "abbab",
  "abbba",
  "abbbb",
  "baaaa",
  "baaab",
  "baaba",
  "baabb",
  "babaa",
  "babab",
  "babba",
  "babbb",
  "bbaaa",
  "bbaab",
};
