GXX := gcc

GXX_FLAGS := -g -Wno-discarded-qualifiers

SRC := src
TESTS := tests
BUILD := build

SRCS := $(wildcard $(SRC)/*.c)
TESTS_SRCS := $(wildcard $(TESTS)/*.c)

OBJS := $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

TESTS_LINKED_LIBS := -lWs2_32

# STATIC_LIB := $(BUILD)/libcrocket.a

# all: clean $(STATIC_LIB)
all: clean

# $(STATIC_LIB): $(OBJS)
# 	ar rcs $@ $^

$(OBJ)/%.o: $(SRC)/%.c
	$(GXX) $(GXX_FLAGS) -c $< -o $@

ifeq ($(OS), Windows_NT)
.SILENT: clean
endif

.PHONY: clean mkbuild

clean: mkbuild
ifeq ($(OS), Windows_NT)
	del /Q /S $(BUILD)\*
else
	find $(BUILD) -maxdepth 1 -type f -exec rm {} \;
	rm -rf $(OBJ)/*
endif

mkbuild:
ifeq ($(OS), Windows_NT)
	if not exist "$(BUILD)" mkdir "$(BUILD)"
else
	mkdir -p $(BUILD)
	mkdir -p $(OBJ)
endif

test: clean
	$(GXX) $(GXX_FLAGS) $(SRCS) $(TESTS_SRCS) -o $(BUILD)/tests $(TESTS_LINKED_LIBS)