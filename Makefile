CC = emcc

CFLAGS = -O2
LDFLAGS = -s MODULARIZE=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets

CFILES = $(wildcard src/*.c)
OBJFILES = $(addsuffix .o, $(basename $(CFILES)))

all:	build
.PHONY: all

debug: CFLAGS += -DDEBUG -g
debug: build

build:	$(OBJFILES) ctags
	$(CC) $(LDFLAGS) $(OBJFILES) -o target/main.js
.PHONY: build

run:	build
	$ python3 -m http.server 8080 --directory=target
.PHONY: run

clean:
	@$(RM) src/*.o
	@$(RM) target/main*
.PHONY: clean

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $*.c

ctags:
	@type ctags >/dev/null 2>&1 && ctags -R * || true
.PHONY: ctags
