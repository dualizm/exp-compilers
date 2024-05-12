#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static char *input = NULL;
static char ch = '\0';

void error() {
  printf("Error!\n");
  exit(EXIT_FAILURE);
}

void read_next(void) {
  ch = *input;  
  input++;
}

bool is_eot(char ch) {
  return ch == '\0' || ch == '\n';
}

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

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("Error: too few arguments");
    return EXIT_FAILURE;
  }

  if (argc > 2) {
    puts("Error: too many arguments");
    return EXIT_FAILURE;
  }

  input = argv[1];
  read_next();

  if (is_sign(ch)) {
    read_next();
  }

  if (is_digit(ch)) {
    read_next();
  } else {
    error();
  }

  while (is_digit(ch)) {
    read_next();
  }
  
  if (!is_eot(ch)) {
    error();
  }

  printf("Successful input!\n");

  return EXIT_SUCCESS;
}
