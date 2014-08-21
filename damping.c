#include "common.h"
#include "matrix.h"

#define CONFIG_FILE "config.ini"

static const int screen_width = 800;
static const int screen_height= 600;

SDL_Surface *screen = NULL;

int stop = 0;

double x[2], a[4], b[2], c[2], d, u, u1, u0;
uint64_t startTime;
double oldy=0.0/0.0;

#ifndef _WIN32
    uint64_t timeGetTime() {
        struct timeval tv;
        gettimeofday(&tv,NULL);
        return tv.tv_sec*1000 + tv.tv_usec / 1000;
    }
#endif


void load_config(const char *name);

void render(double dt, int xpos)
{
    int xp1;
    /* temp matrices */
	double dx[2], dx2[2];  /* 1x2 */
	double ax[2]; /* 1x2 */
	double bu[2]; /* 1x2 */
	double cx;
	double y;

    /* x'(t) = A*x(t) + B*u(t) */
	mat_mult(bu, b, 2, &u, 1, 1); /* bu = B * u */
	mat_mult(ax, a, 2, x, 1, 2); /* ax = A * x */
	mat_sum(dx, ax, bu, 1, 2); /* x'(t) = bu + ax */

    /* Let's integrate them */
	mat_mult(dx2, dx, 2, &dt, 1, 1);  /* dx2 = dx * dt */
	mat_sum(x, x, dx2, 1, 2); /* x += dx2 */

    /* y(t) = C*x(t) + d*u(t) */
	mat_mult(&cx, c, 1, x, 1, 2); /* cx = C * x */
	y = cx + d*u;

    /* Debug prints */
	mat_print("ax", ax, 2);
	mat_print("bu", bu, 2);
	mat_print("dx", dx, 2);
	mat_print("cx", &cx, 1);
	printf("---\n");

    /* Draw line between last and actual point */
	xp1 = xpos-1;

    /* HACK: don't draw line when cursor moves from the end of the screen
     * to the beginning 
     * */
	if(xp1<0) 
		xp1=xpos;

    /* And do the same with y */
	if(oldy==0.0/0.0)
		oldy=y;

    
	y = screen_height/3*2 - y*screen_height/4;

	lineRGBA(screen, xp1, oldy, xpos, y, 0xff, 0xff, 0xff, 0xff);

	oldy=y;
}

void event()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				stop = 1;
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
					case SDLK_u:
					case SDLK_i:
						u=0;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						stop = 1;
						break;
					case SDLK_u:
						u = u0;
						break;
					case SDLK_i:
						u = u1;
						break;
					case SDLK_r:
                        load_config(CONFIG_FILE);
						x[0]=x[1]=0;
						break;
					default:
						break;
				}
			default:
				break;
		}
	}
}

void ltrim(char *str) {
    char *s1 = str;
    while(*s1 && isspace(*s1))
        s1++;
    while(*s1) {
        *str=*s1;
        s1++; str++;
    }
    *str=0;
}

void rtrim(char *str) {
    char *init=str;
    while(*str)
        str++;
    str--;
    while(str != init && isspace(*str))
        *(str--)=0;
}

inline void trim(char *str) {
    ltrim(str);
    rtrim(str);
}

void process_pair(char *key, char *value) {
    trim(key);
    trim(value);

    if(strlen(key) == 0 || strlen(value) == 0)
        return;

    if(!strcmp(key, "a"))
        sscanf(value, "%lf %lf %lf %lf", a, a+1, a+2, a+3);
    else if(!strcmp(key, "b"))
        sscanf(value, "%lf %lf", b, b+1);
    else if(!strcmp(key, "c"))
        sscanf(value, "%lf %lf", c, c+1);
    else if(!strcmp(key, "d"))
        sscanf(value, "%lf", &d);
    else if(!strcmp(key, "u"))
        sscanf(value, "%lf", &u0);
    else if(!strcmp(key, "i"))
        sscanf(value, "%lf", &u1);
    else if(!strcmp(key, "x0"))
        sscanf(value, "%lf %lf", x, x+1);
    else
        printf("Invalid config line %s\n", key); 
}

void load_config(const char *name) {

    #define LINELEN 64
    #define KEY 0
    #define VALUE 1
    #define COMMENT 2
 
    FILE *fp;
    char line[2][LINELEN+1], ch;

    int pos = 0;
    int line_num = 1;
    int mode = 0;

    fp = fopen(name, "r");
    if(!fp) {
        fprintf(stderr, "Cannot open config file.\n");
        exit(-1);
    }

    ch = fgetc(fp);

    while(!feof(fp)) {
        if(ch == '#')
            mode = COMMENT;
        else if(ch == '\n' || ch == '\r') {
            process_pair(line[0],line[1]);
            mode = KEY;
            pos = 0;
            line_num++;
        } else {
            if(mode != COMMENT) {
                if(ch == '=') {
                    if(mode == KEY) {
                        mode = VALUE;
                        pos = 0;
                    } else {
                        fprintf(stderr, "Invalid char at line %d.\n", line_num);
                        fclose(fp);
                        exit(-1);
                    }

                } else if(isgraph(ch) || isspace(ch)) {
                    if(pos<LINELEN) {
                        line[mode][pos++] = tolower(ch);
                        line[mode][pos] = 0;
                    } else {
                        fprintf(stderr, "Line %d too long.\n", line_num);
                        fclose(fp);
                        exit(-1);
                    }
                } else {
                    fprintf(stderr, "Invalid char at line %d.\n", line_num);
                    fclose(fp);
                    exit(-1);
                }
            }
        }
        ch = fgetc(fp);
    }

    process_pair(line[0],line[1]);
    fclose(fp);

    #undef LINELEN
    #undef KEY
    #undef VALUE
    #undef COMMENT
}

int main(int argc, char *argv[]) {
	int x=0;
	srand(time(NULL));
	
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(screen_width, screen_height, 32, SDL_HWSURFACE);

	load_config(CONFIG_FILE);

	while(!stop)
	{
		event();

		SDL_LockSurface(screen);

		lineRGBA(screen, x, 0, x, screen_height, 0,0,0, 0xff);
		
		render(10/1000.0f, x);

		SDL_UnlockSurface(screen);
		SDL_Flip(screen);

		SDL_Delay(10);

		x = (x+1)%screen_width;
	}

	SDL_Quit();
	return 0;
}
