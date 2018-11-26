/*
Author: Chris Robertson https://github.com/electronicsleep
Date: 11/27/2017
Purpose: C++ and SDL2
Released under the BSD license
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;


const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

void printMsg(string msg){
    cout << msg << endl;
}


SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != NULL){
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == NULL){
            printMsg("Error: CreateTextureFromSurface");
            exit(1);
        }
    } else {
        printMsg("Error: LoadBMP: " + file);
        exit(1);
    }
    return texture;
}


int main(int argc, char ** argv) {


    int x = 0;
    int y = 0;

    int loop = 0;
    bool quit = false;

    string errorMsg = "";

    SDL_Event event;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
	printMsg("Failed to init SDl2");
        exit(1);
    }

    // WINDOW
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Shadow Forest",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        errorMsg = SDL_GetError();
        printMsg("Could not create window: " + errorMsg);
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(window);
        errorMsg = SDL_GetError();
        printMsg("SDL_CreateRenderer Error" + errorMsg);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *bg = loadTexture("Images/background.bmp", ren);
    SDL_Texture *user = loadTexture("Images/wizard.bmp", ren);

    while (!quit)
    {
        SDL_Delay(20);
        SDL_PollEvent(&event);


        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            printMsg("QUIT");
            break;

        case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:  x--; break;
            case SDLK_RIGHT: x++; break;
            case SDLK_UP:    y--; break;
            case SDLK_DOWN:  y++; break;
        }
        break;
        }

        loop++;
        SDL_RenderClear(ren);


        // BACKGROUND
        SDL_RenderCopy(ren, bg, NULL, NULL);

        //printMsg("Result: " + to_string(loop % 3));

        if (loop > 100)
            loop = 0;

        // WIZARD
        SDL_Rect dstrect2 = { x, y, 64, 64 };
        SDL_RenderCopy(ren, user, NULL, &dstrect2);
        SDL_RenderPresent(ren);

        //printMsg("Loop: " + to_string(loop));
    }

    SDL_DestroyTexture(bg);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
