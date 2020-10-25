C_COMPILER=gcc
ifeq ($(shell uname -s), Darwin)
C_COMPILER=clang
endif

SRC_FILES=src/console.c
UNITY_ROOT=unity
INC_DIRS=-Isrc -I$(UNITY_ROOT)/src -Itest/mocks -I$(UNITY_ROOT)/extras/fixture/src -I$(UNITY_ROOT)/extras/memory/src -Iinclude/util

console: $(SRC_FILES) mock_controller
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) mock_controller.o -o console $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 --libs --cflags) -lallegro_main -lallegro_ttf -lallegro_primitives
	./console

mock_controller: test/mocks/mock_controller.c
	$(C_COMPILER) $(INC_DIRS) test/mocks/mock_controller.c -c -o mock_controller.o
