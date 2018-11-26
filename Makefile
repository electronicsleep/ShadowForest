
all: test

test: run1

run1:
	g++ ShadowForest.cpp -o ShadowForest -std=c++0x -Wall -lSDL2main -lSDL2
