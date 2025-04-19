# Detect OS
UNAME := $(shell uname)

# Build based on OS name
DetectOS:
	-@make $(UNAME)

Linux:
	g++ src/ShadowForest.cpp -o ShadowForest -std=c++17 -Wall -Wextra -lSDL2main -lSDL2 -lSDL2_ttf

Darwin:
	g++ src/ShadowForest.cpp -o ShadowForest -I/opt/homebrew/include -L/opt/homebrew/lib -std=c++17 -Wall -Wextra -lSDL2main -lSDL2 -lSDL2_ttf

run:
	./ShadowForest
