# Compilador e flags.
CC = gcc
CFLAGS = -g -Wall -Wextra -Iinclude -g

# Diretórios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = out
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/tp1.out

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

run: all
	./$(TARGET) $(FILE)