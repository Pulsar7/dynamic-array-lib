# **************************************************************************** #
#                               PROJECT CONFIG                                 #
# **************************************************************************** #

NAME        := dynamic-array-lib.a
TEST_BIN    := test_runner

CC          := gcc
AR          := ar
RM          := rm -rf

SRC_DIR     := src
TEST_DIR    := tests
INC_DIR     := includes

BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/obj
BIN_DIR     := $(BUILD_DIR)/bin

# **************************************************************************** #
#                               BUILD SETTINGS                                 #
# **************************************************************************** #

CPPFLAGS    := -I$(INC_DIR)
CFLAGS      := -Wall -Wextra -Werror
DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O2

MODE ?= debug

ifeq ($(MODE),debug)
	CFLAGS += $(DEBUG_FLAGS)
else
	CFLAGS += $(RELEASE_FLAGS)
endif

# **************************************************************************** #
#                                  SOURCES                                     #
# **************************************************************************** #

SRC_FILES   := $(wildcard $(SRC_DIR)/*.c)
TEST_FILES  := $(wildcard $(TEST_DIR)/*.c)

SRC_OBJS    := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/src/%.o,$(SRC_FILES))
TEST_OBJS   := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/tests/%.o,$(TEST_FILES))

DEPS        := $(SRC_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(BUILD_DIR)/$(NAME)

# Create necessary directories automatically
$(OBJ_DIR)/src:
	@mkdir -p $@

$(OBJ_DIR)/tests:
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@

# Compile source files
$(OBJ_DIR)/src/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/src
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# Compile test files
$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)/tests
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# Static library
$(BUILD_DIR)/$(NAME): $(SRC_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(AR) rcs $@ $^

# Build test binary
$(BIN_DIR)/$(TEST_BIN): $(BUILD_DIR)/$(NAME) $(TEST_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJS) $< -o $@

# Run tests
test: $(BIN_DIR)/$(TEST_BIN)
	./$(BIN_DIR)/$(TEST_BIN)

# **************************************************************************** #
#                                CLEAN RULES                                   #
# **************************************************************************** #

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(BUILD_DIR)

re: fclean all

debug:
	$(MAKE) MODE=debug re

release:
	$(MAKE) MODE=release re

-include $(DEPS)

.PHONY: all clean fclean re test debug release