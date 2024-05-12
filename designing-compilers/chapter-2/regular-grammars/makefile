
# projects

PRJ_FSM := fsm
PRJ_BINCODE := smBinCode
PRJ_A12 := smA12
PRJ_PASS_CHECKER := smPasswordChecker
PRJ_NUMBERS := smNumbers
PRJ_SIMPLE_NUMBERS := smSimpleNumbers

all: makeDirs $(PRJ_FSM) $(PRJ_BINCODE) $(PRJ_A12) $(PRJ_PASS_CHECKER) $(PRJ_NUMBERS) $(PRJ_SIMPLE_NUMBERS)

makeDirs:
	mkdir -p bin lib

$(PRJ_FSM):
	cd $(PRJ_FSM) && $(MAKE)

$(PRJ_BINCODE):
	cd $(PRJ_BINCODE) && $(MAKE)

$(PRJ_A12):
	cd $(PRJ_A12) && $(MAKE)

$(PRJ_PASS_CHECKER):
	cd $(PRJ_PASS_CHECKER) && $(MAKE)

$(PRJ_NUMBERS):
	cd $(PRJ_NUMBERS) && $(MAKE)

$(PRJ_SIMPLE_NUMBERS):
	cd $(PRJ_SIMPLE_NUMBERS) && $(MAKE)

.PHONY: all $(PRJ_FSM) $(PRJ_BINCODE) $(PRJ_A12) $(PRJ_PASS_CHECKER) $(PRJ_NUMBERS) $(PRJ_SIMPLE_NUMBERS)
