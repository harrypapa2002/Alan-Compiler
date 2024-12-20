#include <stdlib.h>
#include <stdio.h>

void writeInteger(int n) {
  printf("%d", n);
}

void writeByte(char c) {
  printf("%d", c);
}

void writeChar(char c) {
  printf("%c", c);
}

void writeString(char* s) {
  printf("%s", s);
}

int readInteger() {
  int n;
  scanf("%d", &n);
  return n;
}

char readByte() {
  char c;
  scanf("%hhd", &c);
  return c;
}

char readChar() {
  char c;
  scanf("%c", &c);
  return c;
}

void readString(int n, char* s) {
    
    for (int i = 0; i < n-1; i++) {
        s[i] = getchar();
        if (s[i] == '\n' || s[i] == EOF) {
            s[i] = '\0';
            return;
        }
    }
    s[n-1] = '\0';
    return;    
}

int extend(char b) {
  return (int)b;
}

char shrink(int i) {
  return (char)i;
}

int strlen(char* s) {
  int i = 0;
  while (s[i] != '\0') {
    i++;
  }
  return i;
}

int strcmp(char* s1, char* s2) {
  int i = 0;
  while (s1[i] != '\0' && s2[i] != '\0') {
    if (s1[i] != s2[i]) 
      return s1[i] - s2[i];
    i++;
  }
  if (s1[i] == '\0' && s2[i] == '\0') {
    return 0;
  } else if (s1[i] == '\0') {
    return -s1[i];  
  }
  return s2[i];
}

void strcpy(char* trg, char* src) {
  int i = 0;
  while (src[i] != '\0') {
    trg[i] = src[i];
    i++;
  }
  trg[i] = '\0';
}

void strcat(char* trg, char* src) {
  int i = 0;
  while (trg[i] != '\0') {
    i++;
  }
  int j = 0;
  while (src[j] != '\0') {
    trg[i] = src[j];
    i++;
    j++;
  }
  trg[i] = '\0';
}
