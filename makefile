
UNITY_ROOT=unity

SRC_FILES=$(UNITY_ROOT)/src/unity.c $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c test/controller_test.c test/controller_test_runner.c src/controller.c test/mock_console.c test/trajectory_test.c test/trajectory_test_runner.c src/trajectory.c

INC_DIRS=-Isrc -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src -I$(UNITY_ROOT)/extras/memory/src

LIB_FLAGS=$(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 --libs --cflags)
lunar: src/lunar.c
	clang src/lunar.c src/controller.c $(LIB_FLAGS) -o bin/lunar
	- bin/lunar 640

test: clean $(SRC_FILES)
	clang $(INC_DIRS) $(SRC_FILES) test/all_tests.c -o bin/all_tests
	- bin/all_tests

clean:
	rm -f  bin/*
