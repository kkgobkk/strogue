CC = gcc
CFLAGS = -Wall
LIBS = -lncurses

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/player.o $(BUILD_DIR)/entities.o $(BUILD_DIR)/console.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -c $< -I$(SRC_DIR) -o $@

clean:
	rm -rf bin build

clear: clean

run:
	./$(BIN_DIR)/main
