CC := gcc
CFLAGS := -Wall -Werror -g
LDFLAGS :=
INCLUDES := -Iinclude

SRC_DIR := src
OBJ_DIR := obj

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: mush

$(OBJ_DIR):
	mkdir -p $@

mush: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) mush

.PHONY: all clean
