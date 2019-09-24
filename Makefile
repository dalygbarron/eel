CC = g++
CFLAGS = -std=c++14 -I src/
LFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -ldl -llua5.3 -lpthread

MODEL = $(addprefix model/, Actor Bullet Mob Script SubStream Tileset TileMap)
SCENE = $(addprefix scene/, Scene SplashScene SplashSceneLogo PlainScene WalkScene)
CONTROL = $(addprefix model/control/, Control Panel TextBox Bopper)
SERVICE = $(addprefix service/, Config Game Radio Repository Status Engine)
BUILDER = $(addprefix service/builder/, ControlBuilder)
STATIC = $(addprefix static/, Utils xml/pugixml)
TEST = $(addprefix test/, testGeneral testBullet testUtils helpers)

OBJS = $(addprefix src/, $(addsuffix .o, $(CONTROL) $(MODEL) $(SCENE) $(SERVICE) $(STATIC) $(BUILDER) ))
TEST_OBJS = $(addprefix src/test/,$(addsuffix .o, $(TEST)))
MAIN_OBJ = src/main.o
OUT = main
TEST_OUT = tester

DEPS := $(OBJS:.o=.d)
-include $(DEPS)

%.o: %.cc
	$(CC) -MMD -c -o $@ $< $(CFLAGS)

app: $(OBJS) $(MAIN_OBJ)
	$(CC) $(MAIN_OBJ) $(OBJS) $(LFLAGS) -o $(OUT) $(CFLAGS)

tests: $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) $(LFLAGS) -o $(TEST_OUT) $(CFLAGS)

all: app tests

run: app
	./$(OUT) example/game.xml

test: all
	./$(TEST_OUT)

clean:
	find . -name '*.o' -delete
	find . -name '*.P' -delete
	find . -name '*.d' -delete
	rm -f $(OUT)
	rm -f $(TEST_OUT)
