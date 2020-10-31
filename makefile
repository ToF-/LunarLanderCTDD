
LIB_FLAGS=$(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_ttf-5 --libs --cflags)
lunar: src/lunar.c
	clang src/lunar.c $(LIB_FLAGS) -o bin/lunar
	bin/lunar 640
