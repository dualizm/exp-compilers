#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void reset_text(void);
void read(void);
bool is_sign(char ch);
bool is_digit(char ch);
void error(char *msg);
void polynom(void);
void addend(void);
void power(void);
void number(void);

#define EOT '\0'

char Cur;
int Pos;

bool is_sign(char ch) {
  return ch == '+' || ch == '-';
}

bool is_digit(char ch) {
  return
       ch == '0'
    || ch == '1'
    || ch == '2'
    || ch == '3'
    || ch == '4'
    || ch == '5'
    || ch == '6'
    || ch == '7'
    || ch == '8'
    || ch == '9';
}

void error(char *msg) {
  printf("%*s^\n", Pos, "");
  printf("Syntax error: %s\n", msg);
  exit(EXIT_FAILURE);
}

void reset_text(void) {
  printf("Enter a polynomial in X with integer coefficients.\n>");
  Pos = 0;
  read();
}

void read(void) {
  do {
    Pos = Pos + 1;
    if (Cur != '\n') {
      scanf("%c", &Cur); 
    } else {
      scanf("%*s");
      Cur = EOT;
    }
  } while (Cur == ' ');
}

void polynom(void) {
  if (is_sign(Cur)) {
    read();
  }

  addend();
  while (is_sign(Cur)) {
    read();
    addend();
  }
}

void addend(void) {
  if (Cur == 'x') {
    read();
    power();
  } else {
    number();
    if (Cur == 'x') {
      read();
      power();
    } else {
      error("Undefined symbol.");
    }
  }
}

void power(void) {
  if (Cur == '^') {
    read();
    number();
  }
}

void number(void) {
  if (is_digit(Cur)) {
    read();
  } else {
    error("The number does not begin with a digit.");
  }

  while(is_digit(Cur)) {
    read();
  }
}

int main(void) {
  reset_text();

  polynom();
  if (Cur == EOT) {
    error("wait end text");
  } else {
    printf("Successful!\n");
  }

  return EXIT_SUCCESS;
}
