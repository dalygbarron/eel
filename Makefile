CC = g++
CFLAGS = -std=c++14
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -ldl -llua5.3
BUILD = build
SOURCES = main Script BulletManager Bullet SpriteBatch Read SubStream Scene scenes/TestScene
OBJS = $(addprefix $(BUILD)/,$(addsuffix .o,$(SOURCES)))
OUT = main

$(BUILD)/%.o: src/%.cc
	@g++ -MD -c -o $(BUILD)/$@ $< $(CFLAGS)
	@cp $(BUILD)/$*.d $(BUILD)/$*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

-include *.P

all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(OUT) $(CFLAGS)

run: all
	./$(OUT)

clean:
	rm -f *.o *.P $(OUT)
