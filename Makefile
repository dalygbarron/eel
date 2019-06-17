CC = g++
CFLAGS = -std=c++14
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -ldl -llua5.3 -lpthread
MAIN = src/main.o
SOURCES = Game Script BulletManager Bullet SpriteBatch Read SubStream Scene Repository Config Utils
SCENES = scenes/TestScene
WIDGETS =
TESTS = testGeneral testBullet testUtils
OBJS = $(addprefix src/,$(addsuffix .o,$(SOURCES) $(SCENES) $(WIDGETS)))
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
	./$(OUT) example/game.ini

debug: app
	gdb $(OUT)

runTests: all
	./$(TEST_OUT)

clean:
	find . -name '*.o' -delete
	find . -name '*.P' -delete
	find . -name '*.d' -delete
	rm -f $(OUT)
	rm -f $(TEST_OUT)
