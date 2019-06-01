CC = g++
CFLAGS = -std=c++14 -g
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -ldl -llua5.3
SOURCES = main Script BulletManager Bullet SpriteBatch Read SubStream Scene Repository scenes/TestScene
OBJS = $(addprefix src/,$(addsuffix .o,$(SOURCES)))
OUT = main

%.o: %.cc
	@g++ -MD -c -o $@ $< $(CFLAGS)
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

-include *.P

all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(OUT) $(CFLAGS)

run: all
	./$(OUT)

clean:
	find . -name '*.o' -delete
	find . -name '*.P' -delete
	find . -name '*.d' -delete
	rm -f $(OUT)
