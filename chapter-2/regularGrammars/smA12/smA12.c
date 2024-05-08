#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// state     |   symbol  |
// 	         |  a  |  b  |
// -----------------------
// N	       |  B  |  E  |
// B         |  B  |  B  |
// E         |  E  |  E  |

typedef enum {
  N = 'N',
  B = 'B',
  E = 'E'
} jumpTable;

jumpTable transition(jumpTable state, char input) {
  if (state == N) {
    if (input == 'a') {
      return B;
    } else if (input == 'b') {
      return E;
    }
    
  } else if (state == B) {
    if(input == 'a' || input == 'b' ) {
      return B;
    }
  } 

  return E;
}

bool isAlpha(char input) {
  return input == 'a' || input == 'b';
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("Enter input argument!");
    return EXIT_SUCCESS;
  }

  if (argc > 2) {
    puts("Too many arguments!");
    return EXIT_SUCCESS;
  }

  jumpTable state = N;
  bool status = true;
  char const *in = argv[1];
  while (*in) {
    status = isAlpha(*in);
    if (status == false) {
      printf("Invalid input detected: %c\n", *in);
      return EXIT_SUCCESS;
    }

    state = transition(state, *in);
    if (state == E) {
      printf("Invalid input detected: %c\n", *in);
      return EXIT_SUCCESS;
    }

    printf("Input: %c, New state: %c\n", *in, state);
    in++;
  }

  puts("Input correct!");
  return EXIT_SUCCESS;
}
