#include "fsm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(ARRAY) \
  sizeof(ARRAY) / sizeof(ARRAY[0])

// S -> +A | -A | nB
// A -> nB
// B -> nB | e

static char alphabetSigns[] = "+-";
static char alphabetNumbers[] = "1234567890";

static char *states[] = { "S", "A", "B" };
static char start_state[] = "S";
static char *finite_states[] = { "B" };

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("Error: too few arguments");
    return EXIT_FAILURE;
  }

  if (argc > 2) {
    puts("Error: too many arguments");
    return EXIT_FAILURE;
  }

  char *input = argv[1];
  size_t input_len = strlen(input);

  char *alphabet = malloc(sizeof *alphabet *
    (ARRAY_SIZE(alphabetSigns) - 1 +
    ARRAY_SIZE(alphabetNumbers) - 1) + 1);

  strcat(alphabet, alphabetSigns);
  strcat(alphabet, alphabetNumbers);

  size_t transitions_len = ARRAY_SIZE(alphabetSigns) +
                           (ARRAY_SIZE(alphabetNumbers) * 3);
  struct transition *transitions = malloc(sizeof *transitions * transitions_len);
  struct transition *it = transitions;
  fsm_transitions_by_alphabet(it, "S", alphabetSigns, "A");
  it += ARRAY_SIZE(alphabetSigns) - 1;

  fsm_transitions_by_alphabet(it, "S", alphabetNumbers, "B");
  it += ARRAY_SIZE(alphabetNumbers) - 1;

  fsm_transitions_by_alphabet(it, "A", alphabetNumbers, "B");
  it += ARRAY_SIZE(alphabetNumbers) - 1;
  
  fsm_transitions_by_alphabet(it, "B", alphabetNumbers, "B");
  it += ARRAY_SIZE(alphabetNumbers) - 1;


  struct fsm *fsm = fsm_init(alphabet, states, ARRAY_SIZE(states), start_state,
                              finite_states, ARRAY_SIZE(finite_states),
                              transitions, transitions_len);
  fsm_status status = fsm_validate_input(fsm, input, input_len);

  const char *input_result = NULL;
  switch(status) {
    case FSM_SUCCESS: input_result = "was successful"; break;
    case FSM_FAILURE_TRANSITION: input_result = "an existing transition was not found"; break;
    case FSM_FAILURE_UNKNOWN_SYMBOL: input_result = "an unknown character was found in the string"; break;
    case FSM_NOT_FINITE_STATE: input_result = "the machine is not in one of the finite states"; break;
  }

  printf("%s: \"%s\" %s\n",
          status == FSM_SUCCESS ? "Result for the string" : "Error",
          input,
          input_result);

  free(fsm);
  free(transitions);
  free(alphabet);

  return EXIT_SUCCESS;
}

