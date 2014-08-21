all:
	g++ -Wall -Werror -o damping damping.c matrix.c -lm -lSDL -lSDL_gfx
