# ShadowForest - Open Source C++ SDL2 game

Open Source Game created with C++ and SDL2

![Alt text](screenshot.jpg?raw=true "ShadowForest screenshot")

## How to play
* Spacebar to start level
* Arrow keys moves player
* Space bar to attack
* Destroy monsters before they move off screen

## Setup Build

### Linux

```
apt-get install -y make g++ libsdl2-2.0-0 libsdl2-dev libsdl2-ttf-dev 
apt-get install -y libsdl2-image-dev libsdl2-mixer-dev freeglut3-dev libglew-dev
```

### MacOS

```
brew install SDL2 SDL2_Image SDL2_Mixer SDL2_ttf
```

### Build / Start
```
cd src && make
./ShadowForest
```

* entity is a moving object in the game

### Todo
* Mazes
* Animation
* High scores
* NPC
* Chests/weapons
* Hero types
* Enemy types

### Links
https://www.libsdl.org/
