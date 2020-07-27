CC = emcc

all:	src/main.c
	$(CC) src/main.c -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets -o target/main.html
