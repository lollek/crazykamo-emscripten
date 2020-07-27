CC = emcc

CFLAGS = -O2
LDFLAGS = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets

CFILES = $(wildcard src/*.c)
OBJFILES = $(addsuffix .o, $(basename $(CFILES)))

all:	build
.PHONY: all

build:	$(OBJFILES)
	$(CC) $(LDFLAGS) $(OBJFILES) -o target/main.html
.PHONY: build

run:	build
	$ python3 -m http.server 8080 --directory=target
.PHONE: run

clean:
	@$(RM) src/*.o
	@$(RM) target/main*

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $*.c
