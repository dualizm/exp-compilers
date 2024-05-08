#ifndef FSM_H
#define FSM_H
#include <stddef.h>

typedef enum {
  FSM_SUCCESS = 0,
  FSM_FAILURE_TRANSITION = -1,
  FSM_FAILURE_UNKNOWN_SYMBOL = -2,
  FSM_NOT_FINITE_STATE = -3,
} fsm_status;

struct transition {
  char *state;
  char symbol;
  char *next_state;
};

struct fsm {
  char *alphabet;

  char **states;
  size_t states_size;

  char *current_state;

  char **finite_states;
  size_t finite_states_size;

  struct transition *transitions;
  size_t transitions_size;
};

struct fsm* fsm_init(char *alphabet,
  char **states, size_t states_size, char *start_state,
  char **finite_states, size_t finite_states_size,
  struct transition *transitions, size_t transitions_size);

fsm_status fsm_validate_input(struct fsm *fsm, char *input, size_t input_size);
void fsm_transitions_by_alphabet(struct transition *to, char *state, char *alphabet, char *next_state);

#endif /* FSM_H */
