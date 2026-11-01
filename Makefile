
ALL = src/* ./*.c
SRC = src/*.c

FLAGS = -I src

all: 4dttt

4dttt: $(ALL)
	clang $(SRC) 4dttt.c $(FLAGS) -o 4dttt
