/* cipher.c - Takes in a file containing some message as input, and applies
 * a cipher to encode the message. Cipher is determined as an argument to the
 * program. Ciphers for use are;
 * Caesar cipher, Mono-alphabetic substitution cipher, Vigenere cipher, rail_fence
 * cipher, and baconian cipher.The argument passed in will represent a key also,
 * if applicable
 *
 * Written by Daniel Constantinidis
 * 6/6/18
 */
#include "cipher.h"

//Usage
//./cipher <filename> <ciphertype> <argument>

int main(int argc, char *argv[]) {

    FILE *fp = fopen(argv[1], "r");
    char line[BUFFER];
    int c = count(fp);
    int rem = 0; //Remainder variable for the vigenere cipher key
    int bac = 0; //Controls where the printing will happen

    while (fgets(line, BUFFER, fp) != NULL) {
      int length = strlen(line);
      if (argv[2][0] == 'c') {
          caesar(line, atoi(argv[3]), length);
      } else if (argv[2][0] == 's') {
          substitution(line, argv[3], length);
      } else if (argv[2][0] == 'v') {
          rem = vigenere(line,argv[3],rem, length);
      } else if (argv[2][0] == 'r') {
          rail_fence(fp, atoi(argv[3]), c);
          bac = 1;
      } else if (argv[2][0] == 'b') {
          bacon(line, length);
          bac = 1;
      }
      if (bac != 1) printf("%s", line);
    }
    rewind(fp);
    fclose(fp);
}

//Takes a file pointer, and an integer s and encodes the file using a caesar
//cipher with shift s.
void caesar(char line[BUFFER], int shift, int length) {
      int i = 0;
      while (i < length) {
        if (isalpha(line[i])) {
            if (!isupper(line[i])) line[i] = (line[i] - 'a' + shift) % 26 + 'a';
            if (isupper(line[i])) line[i] = (line[i] - 'A' + shift) % 26 + 'A';
        }
        i ++;
      }
  }

//Map each character in the line to the replacement character by checking
//the corresponding index in the substitution array
void substitution(char line[BUFFER], char subs[25], int length) {
    int i = 0;
    while (i < length) {
        if (isalpha(line[i])) {
            if (!isupper(line[i])) line[i] = subs[line[i] - 'a'];
            if (isupper(line[i])) line[i] = subs[line[i] - 'A'] - ('a' - 'A');
        }
        i ++;
    }
}
//vigenere cipher with a key, returns integer 'rem' which dictates where in the key
//we are up to so to continue the sequence on the next line.
int vigenere(char line[BUFFER], char key[BUFFER], int rem, int length){

  int i = 0;
  int j = rem;
  int shift = 0;

  while (i < length) {
    if (!isupper(key[j])) {
       shift = key[j] - 'a';
     } else if (isupper(key[j])) {
       shift = key[j] - 'A';
    }
    if (isalpha(line[i])) {
        if (!isupper(line[i])) line[i] = (line[i] - 'a' + shift) % 26 + 'a';
        if (isupper(line[i])) line[i] = (line[i] - 'A' + shift) % 26 + 'A';
    }
    i ++;
    j = (j + 1) % strlen(key);
  }
  return j;
}

//Rails dictates how 'down' our fence will go, and x represents the length
//of the fence, which is how many letters in our text.
void rail_fence(FILE*fp, int rails, int x) {

    char fence[x][rails];
    char line[BUFFER];
    int i = 0, j = 0;
    for (int b = 0; b < rails; b ++) {
      for (int a = 0; a < x; a ++) {
        fence[a][b] = '.';
      }
    }
    int flag = 0;
    char c;
    while (i < x ) {
        c = fgetc(fp);
        if (c == '\n') continue;
        if (c == EOF) break;
        if (!isalpha(c)) continue;
        fence[i][j] = c;
        i ++;
        if (j == rails - 1) flag = 1;
        if (j == 0) flag = 0;
        if(flag == 0) j ++;
        if (flag == 1) j --;
    }
    //Prints out the 'fence' to visualise the cipher
    /*for (int a = 0; a < rails; a ++) {
      for (int b = 0; b < x; b ++) {
        if (fence[b][a] == '\n') continue;
        if (fence[b][a] == ' ') {printf("_ "); continue;}
        printf("%c ", fence[b][a]);
      }
      printf("\n");
    }*/
    for (int a = 0; a < rails; a ++) {
      for (int b = 0; b < x; b ++) {
        if (fence[b][a] == '\n') continue;
         if (isalpha(fence[b][a])) printf("%c", fence[b][a]);
      }
    }
    printf("\n");
}
//Count the number of characters in the file
int count(FILE* fp) {

  char c;
  int count = 0;
  while (c != EOF) {
    c = fgetc(fp);
    count ++;
  }
  rewind(fp);
  return count;
}
//Encode the text using the baconian cipher
void bacon(char line[BUFFER], int length) {

  int i = 0;
  int index = 0;
  while (i < length) {
      if (isalpha(line[i])) {
          if (!isupper(line[i])) index = line[i] - 'a';
          if (isupper(line[i])) index = line[i] - 'A';
          printf("%s", table[index]);
      }
      if (line[i] == '\n') printf("\n");
      i ++;
  }
}
