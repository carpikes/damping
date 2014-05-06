all:
	g++ -o damping damping.c matrix.c -lm -lSDL -lSDL_gfx -lSDL_ttf -Wall -Werror
