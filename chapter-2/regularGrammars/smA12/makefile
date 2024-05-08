CC := gcc
CFLAGS := -Wall -Wextra -std=c99

SRC_DIR := .
BIN_DIR := ../bin

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:.c=.o)
EXEC := $(BIN_DIR)/smA12.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ): $(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
