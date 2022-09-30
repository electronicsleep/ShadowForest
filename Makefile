build:
	cd src; g++ ShadowForest.cpp -o ShadowForest -std=c++20 -Wall -lSDL2main -lSDL2 -lSDL2_ttf

run:
	cd src; ./ShadowForest
