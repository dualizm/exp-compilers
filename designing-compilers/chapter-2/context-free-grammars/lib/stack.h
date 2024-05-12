#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SUCCESS 0
#define STACK_ERR_ALLOC -1
#define STACK_ERR_EMPTY -2

#define DEF_STACK(TYPE) \
  struct stack_ ## TYPE ## _node {\
    TYPE data;\
    struct stack_ ## TYPE ## _node *next;\
  };\
\
  typedef struct {\
    struct stack_ ## TYPE ## _node *head;\
  } Stack_ ## TYPE;\
\
  int stack_ ## TYPE ## _init(Stack_ ## TYPE *s) {\
    s->head = NULL;\
    return STACK_SUCCESS;\
  }\
\
bool stack_ ## TYPE ## _is_empty(Stack_ ## TYPE *s) {\
  return s->head == NULL;\
}\
TYPE stack_ ## TYPE ## _pop(Stack_ ## TYPE *s) {\
  if(s == NULL || s->head == NULL) {\
    exit(EXIT_FAILURE);\
  }\
\
  TYPE data;\
  if (s->head->next == NULL) {\
    data = s->head->data;\
    free(s->head);\
    s->head = NULL;\
  } else {\
    struct stack_ ## TYPE ## _node *node = s->head;\
    s->head = s->head->next;\
    free(node);\
  }\
\
  return data;\
}\
int stack_ ## TYPE ## _free(Stack_ ## TYPE *s) {\
  if(s == NULL) return STACK_ERR_EMPTY;\
\
  while(!stack_ ## TYPE ## _is_empty(s)) {\
    stack_ ## TYPE ## _pop(s);\
  }\
  return STACK_SUCCESS;\
}\
int stack_ ## TYPE ## _push(Stack_ ## TYPE *s, TYPE data) {\
  if(s == NULL) return STACK_ERR_EMPTY;\
\
  struct stack_ ## TYPE ## _node *node = malloc(sizeof *node);\
  if(node == NULL) return STACK_ERR_ALLOC;\
\
  node->data = data;\
  node->next = s->head;\
  s->head = node;\
\
  return STACK_SUCCESS;\
}

#endif /* STACK_H */
