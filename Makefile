CC     := gcc
LDFLAGS := -lraylib -lm

ifeq ($(OS),Windows_NT)
	LDFLAGS += -lgdi32 -lwinmm
endif

GIT_VERSION := "$(shell git describe --abbrev=6 --always --tags)"
CFLAGS := -Iinclude -DVERSION=\"$(GIT_VERSION)\" $(LDFLAGS) -g

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

$(BIN_DIR)/jds: $(OBJS)
	@echo "Linking..."
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Build successful!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p obj/ bin/

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -rf obj/ bin/
	@echo "Cleaned."

$(BIN_DIR)/$(BIN_NAME): | $(BIN_DIR)
