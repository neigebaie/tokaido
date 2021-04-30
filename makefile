define colorecho
      @tput setaf 3
      @echo $1
      @tput sgr0
endef

CFLAGS  = `sdl2-config --cflags` -Wall -mtune=native -no-pie -g -Iinclude # -Wextra
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lcrypto

TARGETS = tokaido

all: $(TARGETS)

# src/square_init.c src/square_draw.c src/square_action.c  src/board.c src/utility.c src/gui.c src/account.c src/main.c
tokaido: src/utility.c src/gui.c src/game.c src/board.c src/square_init.c src/square_action.c src/square_draw.c src/account.c src/main.c
	@cc $(CFLAGS) -o $@ $+ $(LDFLAGS)
	$(call colorecho,"$@ success. ./\"$@\" to execute.")
