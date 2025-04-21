SOURCE_DIR = src
BIN_DIR = bin
EXE = $(BIN_DIR)/main.exe


all: gen exec

gen:
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	gcc $(SOURCE_DIR)/*.c -o $(EXE)


exec:
	@echo "starting..."
	$(EXE)
