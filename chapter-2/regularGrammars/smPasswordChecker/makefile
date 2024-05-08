CC := gcc
CFLAGS := -Wall -Wextra -std=c99
LDFLAGS := -L../lib
INC_DIR := -I../fsm

SRC_DIR := .
HDR_DIR := ../fsm
BIN_DIR := ../bin

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:.c=.o)
EXEC := $(BIN_DIR)/smPasswordChecker.out

all: $(EXEC)

$(EXEC): $(OBJ) ../lib/libfsm.a
	$(CC) $(CFLAGS) $(INC_DIR) $(LDFLAGS) -o $@ $^

$(OBJ): $(SRC_DIR)/%.o : $(SRC_DIR)/%.c $(HDR_DIR)/fsm.h
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
