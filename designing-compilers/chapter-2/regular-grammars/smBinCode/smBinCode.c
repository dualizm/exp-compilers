#include "fsm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(ARRAY) \
  sizeof(ARRAY) / sizeof(ARRAY[0])

static struct transition transitions[] = {
  {"q0", '0', "q1"},
  {"q0", '1', "q1"},
  {"q1", '0', "q1"},
  {"q1", '1', "q1"},
};

static char alphabet[] = "01";
static char *states[] = { "q0", "q1" };
static char start_state[] = "q0";
static char *finite_states[] = { "q1" };

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
  struct fsm *fsm = fsm_init(alphabet, states, ARRAY_SIZE(states), start_state, 
                              finite_states, ARRAY_SIZE(finite_states), 
                              transitions, ARRAY_SIZE(transitions));
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

  return EXIT_SUCCESS;
}
