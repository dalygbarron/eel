rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
CC = g++
CFLAGS = -std=c++14
LFLAGS = -lSDL2 -lSDL2_image -framework GLUT -framework OpenGL -ldl -llua
HEADERS := $(call rwildcard,src/,*.hh)
OBJS = hello.o Script.o Graphics.o Input.o Texture.o Vector.o Shader.o PolygonShader.o BulletManager.o
OUT = main


%.o: src/%.cc $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(ADD) -g

all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(OUT) $(CFLAGS) -g

run: all
	./$(OUT)

clean:
	rm -f *.o $(OUT)
