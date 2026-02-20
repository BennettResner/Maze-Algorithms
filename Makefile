CC      = cc
CFLAGS  = -Wall -Wextra -std=c11
BIN_DIR = bin
TARGET  = $(BIN_DIR)/maze
ERR_LOG = $(BIN_DIR)/error.log

# --- RAYLIB ---

RAYLIB_DIR    = /opt/homebrew
RAYLIB_INC    = -I$(RAYLIB_DIR)/include
RAYLIB_LFLAGS = -L$(RAYLIB_DIR)/lib -lraylib \
                -framework Cocoa \
                -framework IOKit \
                -framework CoreVideo \
                -framework OpenGL

SRCS = src/main.c \
       src/maze.c \
       src/utilities.c \
       src/generators/RecursiveDFS.c \
       src/searchers/BFS.c \
       src/render/render.c

$(TARGET): $(SRCS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(RAYLIB_INC) -o $(TARGET) $(SRCS) $(RAYLIB_LFLAGS) 2>>$(ERR_LOG)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# --- TESTS ---

TEST_SRCS    = tests/test_utilities.c \
               tests/test_maze.c \
               src/utilities.c \
               src/maze.c
TEST_BIN     = $(BIN_DIR)/test_runner
CRITERION    = /opt/homebrew/opt/criterion
TEST_CFLAGS  = $(CFLAGS) -I$(CRITERION)/include
TEST_LDFLAGS = -L$(CRITERION)/lib -lcriterion

test: $(TEST_SRCS) | $(BIN_DIR)
	$(CC) $(TEST_CFLAGS) $(TEST_SRCS) $(TEST_LDFLAGS) -o $(TEST_BIN) 2>>$(ERR_LOG)
	./$(TEST_BIN)

# --- CLEAN ---

clean:
	rm -rf $(BIN_DIR)

.PHONY: clean test
