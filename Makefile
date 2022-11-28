# Detect OS
UNAME := $(shell uname)

# Build based on OS name
DetectOS:
	-@make $(UNAME)

Linux:
	cd src; g++ ShadowForest.cpp -o ShadowForest -std=c++17 -Wall -lSDL2main -lSDL2 -lSDL2_ttf

Darwin:
	cd src; g++ ShadowForest.cpp -o ShadowForest -I/opt/homebrew/include -L/opt/homebrew/lib -std=c++17 -Wall -lSDL2main -lSDL2 -lSDL2_ttf

run:
	cd src; ./ShadowForest
