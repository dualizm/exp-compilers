#include "fsm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(ARRAY) \
  sizeof(ARRAY) / sizeof(ARRAY[0])

static char alphabetChars[] = "abcdefghijklmnopqrstuvwxyz";
static char alphabetSpecial[] = "!@#$%^&*()";
static char alphabetNumbers[] = "1234567890";

static char *states[] = { "q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7", "q8", "q9", "q10" };
static char start_state[] = "q0";
static char *finite_states[] = { "q10" };

void target_transition(struct transition** it, char *target, char *a, char *b, char *c) {
  fsm_transitions_by_alphabet(*it, target, alphabetChars, a);
  *it += ARRAY_SIZE(alphabetChars) - 1;

  fsm_transitions_by_alphabet(*it, target, alphabetSpecial, b);
  *it += ARRAY_SIZE(alphabetSpecial) - 1;

  fsm_transitions_by_alphabet(*it, target, alphabetNumbers, c);
  *it += ARRAY_SIZE(alphabetNumbers) - 1;
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

  char *input = argv[1];
  size_t input_len = strlen(argv[1]);

  char *alphabet = malloc(sizeof *alphabet * 
    (ARRAY_SIZE(alphabetChars) - 1 + 
    ARRAY_SIZE(alphabetSpecial) - 1 +
    ARRAY_SIZE(alphabetNumbers) - 1) + 1);

  strcat(alphabet, alphabetChars);
  strcat(alphabet, alphabetSpecial);
  strcat(alphabet, alphabetNumbers);

  size_t transitions_len = (ARRAY_SIZE(alphabetChars) * 11) +
                           (ARRAY_SIZE(alphabetSpecial) * 11) +
                           (ARRAY_SIZE(alphabetNumbers) * 11);
  struct transition *transitions = malloc(sizeof *transitions * transitions_len);
  struct transition *it = transitions;
  target_transition(&it, "q0", "q1", "q4", "q7");
  target_transition(&it, "q1", "q1", "q2", "q3");
  target_transition(&it, "q2", "q2", "q2", "q10");
  target_transition(&it, "q3", "q3", "q10", "q3");
  target_transition(&it, "q4", "q5", "q4", "q6");
  target_transition(&it, "q5", "q5", "q5", "q10");
  target_transition(&it, "q6", "q10", "q6", "q6");
  target_transition(&it, "q7", "q8", "q9", "q7");
  target_transition(&it, "q8", "q8", "q10", "q8");
  target_transition(&it, "q9", "q10", "q9", "q9");
  target_transition(&it, "q10", "q10", "q10", "q10");

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
