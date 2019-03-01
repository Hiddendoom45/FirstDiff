CC		:= gcc
C_FLAGS := -Wall -Wextra

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

DEF_FLAG := 

LIBRARIES	:=

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= firstdiff.exe
else
EXECUTABLE	:= firstdiff
endif

all: $(BIN)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) $(DEF_FLAG:%=-D%) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)


.PHONY: debug
debug: DEF_FLAG+= DEBUG
debug: $(BIN)/$(EXECUTABLE)
