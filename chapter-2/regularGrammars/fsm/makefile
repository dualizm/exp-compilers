CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c99
LDFLAGS := -shared

SRC_DIR := .
LIB_DIR := ../lib

FSM_SRC := $(wildcard $(SRC_DIR)/fsm.c)
FSM_OBJ := $(patsubst $(SRC_DIR)/%.c, $(LIB_DIR)/%.o, $(FSM_SRC))
FSM_SO := $(LIB_DIR)/libfsm.so
FSM_A := $(LIB_DIR)/libfsm.a

all: $(FSM_SO) $(FSM_A)

$(FSM_SO): $(FSM_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(FSM_A): $(FSM_OBJ)
	ar rcs $@ $^

$(LIB_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -rf $(FSM_SO) $(FSM_A) $(LIB_DIR)/*.o

.PHONY: all clean
