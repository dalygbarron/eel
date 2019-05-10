CC = g++
CFLAGS = -std=c++14
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -ldl -llua
OBJS = main.o Script.o
OUT = main

%.o: src/%.cc
	@g++ -MD -c -o $@ $<
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
	rm -f *.o *.P $(OUT)
