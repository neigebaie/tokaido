FLAGS = `sdl2-config --cflags --libs`

tokaido : src/main.c
	gcc src/main.c -o bin/tokaido $(FLAGS)
