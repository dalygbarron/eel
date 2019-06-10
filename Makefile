CC = g++
CFLAGS = -std=c++14 -g
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -ldl -llua5.3
MAIN = src/main.o
SOURCES = Script BulletManager Bullet SpriteBatch Read SubStream Scene Repository Game Config
SCENES = scenes/TestScene
TESTS = bulletTest
OBJS = $(addprefix src/,$(addsuffix .o,$(SOURCES) $(SCENES)))
TEST_OBJS = $(addprefix src/test/,$(addsuffix .o,$(TESTS)))
OUT = main
TEST_OUT = tester

%.o: %.cc
	@g++ -MD -c -o $@ $< $(CFLAGS)
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

-include *.P

app: $(OBJS) $(MAIN)
	$(CC) $(MAIN) $(OBJS) $(LFLAGS) -o $(OUT) $(CFLAGS)

tests: $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) $(LFLAGS) -o $(TEST_OUT) $(CFLAGS)

all: app tests

run: app
	./$(OUT)

runTests: all
	./$(TEST_OUT)

clean:
	find . -name '*.o' -delete
	find . -name '*.P' -delete
	find . -name '*.d' -delete
	rm -f $(OUT)
	rm -f $(TEST_OUT)
