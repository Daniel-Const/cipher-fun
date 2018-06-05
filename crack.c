/* crack.c - Takes a file containing cipher text from a caesar cipher as input
 * prints out the original text before encrygcc
 * Uses the cumulative chi-squared test statistic based on the frequencies of
 * letters in the English alphabet. This is calculated for each possible caesar cipher
 * shift, and the shift with the lowest value is taken as the plaintext
 * 
 * Written by Daniel Constantinidis
 * 6/6/18
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cipher.h"

//Usage;
//./crack <filename> <ciphertype> <argument>

void caesarCrack(FILE *fp);
void baconCrack(FILE *fp);

void calcFreq(FILE *fp, double freq[26], int shift, int count);
double calcChi(double freq[26], double expected[26]);
void encodeCaesar(FILE *fp, int shift);
int countFile(FILE *fp);

int main(int argc, char *argv[]) {

    FILE *fp = fopen(argv[1], "r");

    if (argv[2][0] == 'c') {
        caesarCrack(fp);
    }

    fclose(fp);
}

//Breaks the caesar cipher using the cumulative chi-squared test statistic
//Prints out the plain text which provides the smallest value.
void caesarCrack(FILE *fp) {

  double freq[26];
  for (int i = 0; i < 26; i ++) freq[i] = 0;
  //Average frequencies for each letter in the English alphabet
  //Index represents the letter corresponding to the frequency
  double expected[26] = {0.08, 0.015, 0.03, 0.04, 0.128, 0.02, 0.018, 0.06, 0.068,
     0.005, 0.009, 0.039, 0.023, 0.065, 0.075, 0.02, 0.002, 0.057, 0.06, 0.09, 0.03, 0.01
    , 0.023, 0.003, 0.015, 0.001};
  //Represents the chi_stat calculation for every possible shift
  double chi_stat[26];
  int count = countFile(fp);
  for (int i = 0; i < 26; i ++) {
    calcFreq(fp, freq, i, count);
    rewind(fp);
    chi_stat[i] = calcChi(freq, expected);
  }
  //Find the lowest chi stat, and then apply caeasar shif to that.
  int min = 0;
  for (int i = 0; i < 26; i ++) {
    if (chi_stat[i] < chi_stat[min]) min = i;
    printf("%d - %lf \n",i, chi_stat[i]);
  }
  encodeCaesar(fp, min);
  printf("min is %d\n", min);
}

//Encodes the data with the caesar shift. Is done for all possible shifts
void encodeCaesar(FILE *fp, int shift) {
  char line[BUFFER];
  while (fgets(line, BUFFER, fp) != NULL) {

    for (int i = 0; i < strlen(line); i ++) {
      if (isalpha(line[i])) {
        if (!isupper(line[i])) printf("%c", (line[i] - 'a' + shift) % 26 + 'a') ;
        if (isupper(line[i])) printf("%c", (line[i] - 'A' + shift) % 26 + 'A') ;
      } else {
        printf("%c", line[i]);
      }
    }
  }
}
//Counts the number of characters in a file
int countFile(FILE *fp) {
  char c;
  int count = 0;
  while (c != EOF) {
    c = fgetc(fp);
    count ++;
  }
  rewind(fp);
  return count;
}

//Calculate the frequency of letters in the text
//apply the shift at the same time as frequency calculation
void calcFreq(FILE *fp, double freq[26], int shift, int count) {

  char line[BUFFER];
  while (fgets(line, BUFFER, fp) != NULL) {

    for (int i = 0; i < strlen(line); i ++) {
      if (isalpha(line[i])) {
        if (!isupper(line[i])) freq[(line[i] - 'a' + shift) % 26] ++ ;
        if (isupper(line[i])) line[(line[i] - 'A' + shift) % 26] ++;
      }
    }
  }
  for (int i = 0; i < 26; i ++) {
    freq[i] = freq[i] / (double)count;
  }
}

//Calculates the cumulative chi-squared statistic for the given caesar shift
double calcChi(double freq[26], double expected[26]) {

  double sum = 0;
  for (int i = 0; i < 26; i ++) {
    sum += (pow((freq[i] - expected[i]),  2) / expected[i]);
  }
  return sum;
}
