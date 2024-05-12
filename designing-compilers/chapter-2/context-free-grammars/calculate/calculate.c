#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  char ch;
  int counter;
  struct node *left;
  struct node *right;
};

void Calculate(struct node *t, int *result) {
  int x1, x2;

  if (t != NULL) {
    Calculate(t->left, &x1);
    Calculate(t->right, &x2);

    switch(t->ch) {
      case '+': *x = x1 + x2; break;
      case '-': *x = x1 - x2; break;
      case '*': *x = x1 * x2; break;
      case '/': *x = x1 / x2; break;
      case 'a': *x = 1.0; break;
      case 'b': *x = 1.0; break;
      case 'c': *x = 1.0; break;
    }
  }
}
