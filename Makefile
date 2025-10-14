GXX := gcc

GXX_FLAGS := -g -Wno-discarded-qualifiers

SRC := src
BUILD := build
OBJ := $(BUILD)/obj

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TEST_DIR := tests
TEST_OBJ := $(OBJ)/$(TEST_DIR)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJ)/%.o, $(TEST_SRCS))
TEST_BIN := $(patsubst $(TEST_DIR)/%.c, $(BUILD)/%, $(TEST_SRCS))

ifeq ($(OS), Windows_NT)
	LINKED_LIBS := -lWs2_32
else
	LINKED_LIBS :=
endif

LIB := $(BUILD)/libcrocket.a

.PHONY: all clean mkbuild

all: mkbuild $(LIB) $(TEST_BIN)

$(OBJ)/%.o: $(SRC)/%.c
	$(GXX) $(GXX_FLAGS) -c $< -o $@

$(TEST_OBJ)/%.o: $(TEST_DIR)/%.c
	$(GXX) $(GXX_FLAGS) -c $< -o $@

$(LIB): $(OBJS)
	ar rcs $@ $(OBJS)

$(BUILD)/%: $(TEST_OBJ)/%.o $(LIB)
	$(GXX) $(GXX_FLAGS) -o $@ $< -L$(BUILD) -lcrocket $(LINKED_LIBS)

mkbuild:
ifeq ($(OS), Windows_NT)
	if not exist "$(BUILD)" mkdir "$(BUILD)"
	if not exist "$(OBJ)" mkdir "$(OBJ)"
	if not exist "$(TEST_OBJ)" mkdir "$(TEST_OBJ)"
else
	mkdir -p $(BUILD) $(OBJ) $(TEST_OBJ)
endif

clean: mkbuild
ifeq ($(OS), Windows_NT)
	del /Q /S $(BUILD)\*
else
	rm -rf $(BUILD)/*
endif
