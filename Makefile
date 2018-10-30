all:
	gcc -Wall -Werror -o bin/damping src/damping.c src/matrix.c -lm -lSDL -lSDL_gfx -fstack-protector-strong -O2 -D_FORTIFY_SOURCE=2 -I/usr/include/SDL

clean:
	rm bin/damping
