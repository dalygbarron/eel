rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
CC = g++
CFLAGS = -std=c++14
LFLAGS = -lSDL2 -lSDL2_image -framework OpenGL -ldl -llua
HEADERS := $(call rwildcard,src/,*.hh)
OBJS = hello.o Script.o
OUT = main


%.o: src/%.cc $(HEADERS) $(SQL_HEADER)
	$(CC) -c -o $@ $< $(CFLAGS) $(ADD)

all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(OUT) $(CFLAGS)

clean:
	rm -f build/*
