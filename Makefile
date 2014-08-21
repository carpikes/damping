all:
	gcc -Wall -Werror -o bin/damping src/damping.c src/matrix.c -lm -lSDL -lSDL_gfx

clean:
	rm bin/damping
