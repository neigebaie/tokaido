define colorecho
      @tput setaf 3
      @echo $1
      @tput sgr0
endef

CFLAGS  = `sdl2-config --cflags` # -Wall -Wextra -mtune=native -no-pie
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf

TARGETS = tokaido

all: $(TARGETS)

tokaido: src/square_action.c src/input.c src/board.c src/utility.c src/gui.c src/main.c
	@cc $(CFLAGS) -o $@ $+ $(LDFLAGS)
	$(call colorecho,"$@ success. ./\"$@\" to execute.")
