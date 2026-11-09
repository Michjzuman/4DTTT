NAME = 4dttt

ENGINE = src/engine/*.c

FLAGS = -I src/engine

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	FLAGS += -g -O0 -D DEBUG
endif

all: tui

TUI_FLAGS = $(FLAGS) -l ncurses -I src/tui
TUI_SRC = $(ENGINE) src/tui/*.c

tui: $(ALL)
	clang $(TUI_SRC) $(TUI_FLAGS) -o $(NAME)


