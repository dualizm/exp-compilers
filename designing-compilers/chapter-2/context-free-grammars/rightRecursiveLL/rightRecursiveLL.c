#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void error(char *msg);
void read(void);
void start_read(void);
bool is_alphabet(void);
void E(void);
void T(void);
void M(void);

/*
  G15: E -> T A
       A -> _|_ | + TA | - TA
       T -> M B
       B -> _|_ | * MB | / MB
       M -> a | b | c | ( E )
*/

#define EOT '\0'

char current;
int pos;

void error(char *msg) {
  printf("%*s^\n", pos, "");
  printf("Syntax error: %s\n", msg);
  exit(EXIT_FAILURE);
}

void read(void) {
  do {
    pos++;
    if (current != '\n') {
      scanf("%c", &current);
    } else {
      scanf("%*s");
      current = EOT;
    }
  } while ( current == ' ');
}

void start_read(void) {
  printf("Enter an arithmetic expression using \"+ - * / a b c\":\n>");
  pos = 0;
  read();
}

bool is_alphabet(void) {
  return 
        current == 'a' 
    ||  current == 'b'
    ||  current == 'c';
}

void E(void) {
  T();

  while (current == '-' || current == '+') {
    read();
    T();
  }
}

void T(void) {
  M();

  while (current == '*' || current == '/') {
    read();
    M();
  }

}

void M(void) {
  if(is_alphabet()) {
    read();
  } else if (current == '(') {
    read();
    E();
    if (current == ')') {
      read();
    } else {
      error("There is no closing bracket");
    }
  } else {
    error("Expected a, b, c or '('");
  }
}

int main(void) {
  start_read();

  E();
  if (current == EOT) {
    error("wait end text");
  } else {
    printf("Successful!\n");
  }

  return EXIT_SUCCESS;
}
