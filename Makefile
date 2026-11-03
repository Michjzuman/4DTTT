
ALL = src/* ./*.c
SRC = src/*.c

FLAGS = -I src

all: 4dttt

4dttt: $(ALL)
	clang $(SRC) main.c $(FLAGS) -o 4dttt

debug: $(ALL)
	clang $(SRC) main.c $(FLAGS) -o 4dttt -g -O0
