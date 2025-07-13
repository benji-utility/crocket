GCC := gcc

GCC_FLAGS := -g -I./src

SRC := src
BUILD := build
OBJ := $(BUILD)/obj

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

STATIC_LIB := $(BUILD)/libcrocket.a

all: clean $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	ar rcs $@ $^

$(OBJ)/%.o: $(SRC)/%.c
	$(GCC) $(GCC_FLAGS) -c $< -o $@

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
	if not exist "$(OBJ)" mkdir "$(OBJ)"
else
	mkdir -p $(BUILD)
	mkdir -p $(OBJ)
endif