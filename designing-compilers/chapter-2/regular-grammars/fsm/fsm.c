#include "fsm.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FSM_LIMIT_CHARS 1024

static bool belong_alphabet(struct fsm *fsm, char symbol);
static bool change_state(struct fsm *fsm, char symbol);
static bool is_finite_state(struct fsm *fsm);
static struct transition* exist_transition(struct fsm *fsm, char symbol);

bool belong_alphabet(struct fsm *fsm, char symbol) {
  for(char *p = fsm->alphabet; *p; p++) {
    if(*p == symbol) {
      return true;
    }
  }

  return false;
}

struct transition* exist_transition(struct fsm *fsm, char symbol) {
  for(size_t i = 0; i < fsm->transitions_size; i++) {
    if(strncmp(fsm->transitions[i].state, fsm->current_state, FSM_LIMIT_CHARS) == 0 &&
        fsm->transitions[i].symbol == symbol) {
      return &fsm->transitions[i];
    }
  }

  return NULL;
}

bool change_state(struct fsm *fsm, char symbol) {
  struct transition *transition = exist_transition(fsm, symbol);
  if (!transition) return false;

  fsm->current_state = transition->next_state;

  return true;
}

bool is_finite_state(struct fsm *fsm) {
  for(size_t i = 0; i < fsm->finite_states_size; i++) {
    if(strncmp(fsm->finite_states[i], fsm->current_state, FSM_LIMIT_CHARS) == 0) {
      return true;
    }
  }

  return false;
}

struct fsm* fsm_init(char *alphabet,
  char **states, size_t states_size, char *start_state,
  char **finite_states, size_t finite_states_size,
  struct transition *transitions, size_t transitions_size) {

  struct fsm *ret = malloc(sizeof *ret);
  ret->alphabet = alphabet;
  ret->states = states;
  ret->states_size = states_size;
  ret->current_state = start_state;
  ret->finite_states = finite_states;
  ret->finite_states_size = finite_states_size;
  ret->transitions = transitions;
  ret->transitions_size = transitions_size;

  return ret;
}

fsm_status fsm_validate_input(struct fsm *fsm, char *input, size_t input_size) {
  for(size_t i = 0; i < input_size; i++) {
    bool symbol_status = belong_alphabet(fsm, input[i]);
    if (symbol_status == false) {
      return FSM_FAILURE_UNKNOWN_SYMBOL;
    }

    bool state_status = change_state(fsm, input[i]);
    if (state_status == false) {
      return FSM_FAILURE_TRANSITION;
    }

  }

  bool finite_status = is_finite_state(fsm);
  if (finite_status == false) {
    return FSM_NOT_FINITE_STATE;
  }

  return FSM_SUCCESS;
}

void fsm_transitions_by_alphabet(struct transition *to, char *state, char *alphabet, char *next_state) {
  size_t alphabet_size = strlen(alphabet);

  for (size_t i = 0; i < alphabet_size; i++) {
    to[i] = (struct transition){
      state,
      alphabet[i],
      next_state,
    };
  }
}
