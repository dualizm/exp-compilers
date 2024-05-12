#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define NMAX 255
#define EOT '\n'

typedef struct {
  int n; 
  int a[NMAX];
} Poly;

void poly_init(Poly *p);
void mult_poly(Poly x, Poly y, Poly *z);
void clear_poly(Poly *p);
void write_poly(Poly *p);
void read_poly(Poly *p);

typedef struct {
  int pos;
  char cur;
} Context;

void ctx_init(Context *ctx);
void error(Context *ctx, const char *msg);
void read_char(Context *ctx);

void poly(Context *ctx, Poly *p);

void addend(Context *ctx, int *a, int *k);
bool is_digit(char ch);
void power(Context *ctx, int *p);
void number(Context *ctx, int *n);

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

void power(Context *ctx, int *p) {
  if (ctx->cur == '^') {
    read_char(ctx);
    number(ctx, p);
    if (*p > NMAX) {
      error(ctx, "To big power");
      *p = 0;
    }
  } else {
    *p = 1;
  }
}

void number(Context *ctx, int *a) {
  if(is_digit(ctx->cur)) {
    *a = ctx->cur - '0';
    read_char(ctx);
  } else {
    error(ctx, "Number must begin from digit.");
  }

  while(is_digit(ctx->cur)) {
    int d = ctx->cur - '0';
    if( *a <= (INT_MAX - d) / 10) {
      *a = *a * 10 + (ctx->cur - '0');
    } else {
        error(ctx, "Too big number");
    }
    read_char(ctx);
  }
}

void ctx_init(Context *ctx) {
  ctx->pos = 0;
  ctx->cur = '\0';
}

void poly_init(Poly *p) {
  p->n = 0;
  memset(p->a, 0, sizeof(*p->a) * NMAX);
}

void error(Context *ctx, const char *msg) {
  printf("%*s^\n", ctx->pos, "");
  printf("Syntax error: %s\n", msg);
  exit(EXIT_FAILURE);
}

void read_char(Context *ctx) {
  do {
    ctx->pos++;
    if (ctx->cur != EOT) {
      scanf("%c", &ctx->cur);
    } else {
      scanf("%*s");
      ctx->cur = EOT;
    }
  } while (ctx->cur == ' ');
}

void read_poly(Poly *p) {
  Context ctx;
  ctx_init(&ctx);
  read_char(&ctx);
  poly(&ctx, p);
  if (ctx.cur != EOT) {
    error(&ctx, "Wait end text");
  }
} 
void poly(Context *ctx, Poly *p) {
  int a = 0;
  int k = 0;
  char op = '\0';

  clear_poly(p);
  if (ctx->cur == '+' || ctx->cur == '-') {
    op = ctx->cur;
    read_char(ctx);
  } else {
    op = '+';
  }

  addend(ctx, &a, &k);
  if (op == '+') {
      p->a[k] = p->a[k] + a;
  } else {
      p->a[k] = p->a[k] - a;
  }

  while(ctx->cur == '+' || ctx->cur == '-') {
    op = ctx->cur;

    read_char(ctx);
    addend(ctx, &a, &k);
    if (op == '+') {
      p->a[k] = p->a[k] + a;
    } else {
      p->a[k] = p->a[k] - a;
    }
  }

  p->n = NMAX;
  while(p->n > 0 && p->a[p->n - 1] == 0) {
    p->n = p->n - 1;
  }
}

void addend(Context *ctx, int *a, int *k) {
  if (is_digit(ctx->cur)) {
    number(ctx, a);
    if (ctx->cur == 'x') {
      read_char(ctx);
      power(ctx, k);
    } else {
      *k = 0;
    }
  } else if (ctx->cur == 'x') {
    *a = 1;
    read_char(ctx);
    power(ctx, k);
  } else {
    error(ctx, "Wait number or 'x'");
  }
}

void write_poly(Poly *p) {
  for (int i = p->n; i > 0; i--) {
    if (p->a[i] > 0 && i != p->n) {
      printf(" + ");
    } else if (p->a[i] < 0 && i == p->n) {
      printf("-");
    } else if (p->a[i] < 0) {
      printf(" - ");
    }

    if ((abs(p->a[i]) > 1 || i == 0) &&
        (p->a[i] != 0 || p->n == 0)) {
      printf("%d", abs(p->a[i]));
    }

    if (i > 0 && p->a[i] != 0) {
      printf("x");
    }
    if (i > 1 && p->a[i] != 0) {
      printf("^%d", i);
    }
  }
}

void clear_poly(Poly *p) {
  p->n = 0;
  memset(p->a, 0, sizeof(*p->a) * NMAX);
}

void mult_poly(Poly x, Poly y, Poly *z) {
  clear_poly(z);
  for (int i = 0; i < x.n; i++) {
    for (int j = 0; j < y.n; j++) {
      z->a[i+j] += x.a[i] * y.a[j];
    }

    z->n = NMAX;
    while (z->n > 0 && z->a[z->n - 1] == 0) {
      z->n = z->n - 1;
    }
  }
}

int main(void) {
  Poly p1, p2, q;

  poly_init(&p1);
  poly_init(&p2);
  poly_init(&q);

  puts("Multiplication of polynomials");
  puts("-----------------------------");
  puts("The 1st polynomial:");
  read_poly(&p1);
  puts("The 2st polynomial:");
  read_poly(&p2);
  mult_poly(p1, p2, &q);
  puts("Product:");
  write_poly(&q);
  puts("");

  return EXIT_SUCCESS;
}
