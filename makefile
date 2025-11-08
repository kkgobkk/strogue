SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

all: $(BIN_DIR)/main

$(BIN_DIR)/main:
	@mkdir $(BIN_DIR)
	gcc $(SRC_DIR)/main.c $(SRC_DIR)/player.c $(SRC_DIR)/entities.c -lncurses -o $(BIN_DIR)/main
