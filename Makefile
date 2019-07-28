CC = gcc
CFLAGS = -I . -DLOG_USE_COLOR
LFLAGS = -lm -ldl -lluajit -lSDL2 -framework OpenGL

SOURCES = log util list exe render game
TEST = main

OBJS = $(addprefix src/, $(addsuffix .o, $(SOURCES)))
TEST_OBJS = $(addprefix test/,$(addsuffix .o, $(TEST)))
MAIN_OBJ = src/main.o
OUT = main
TEST_OUT = tester

DEPS := $(OBJS:.o=.d)
-include $(DEPS)

%.o: %.c
	$(CC) -MMD -c -o $@ $< $(CFLAGS)

app: $(OBJS) $(MAIN_OBJ)
	$(CC) $(MAIN_OBJ) $(OBJS) $(LFLAGS) -o $(OUT) $(CFLAGS)

tests: $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) $(LFLAGS) -o $(TEST_OUT) $(CFLAGS)

all: app tests

run: app
	./$(OUT) example/game.ini

test: all
	./$(TEST_OUT)

clean:
	find . -name '*.o' -delete
	find . -name '*.P' -delete
	find . -name '*.d' -delete
	rm -f $(OUT)
	rm -f $(TEST_OUT)
