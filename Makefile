#Makefile

all: build

build: main.out
	./main.out

main.out: main.cpp
	g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main.out

clean:
	rm -f main.out

.PHONY: all build clean