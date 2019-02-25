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

#include "Player.hpp"
#include "Foe.hpp"

using namespace std;


const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const int debug = 0;

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


    Player player;
    Foe foe;
    player.print_name("Chris");
    foe.print_name("Zombie1");
    player.print_stats();
    foe.print_stats();
    string show_magic = "";

    int x = 200;
    int y = 200;

    int loop = 0;
    bool quit = false;

    string errorMsg = "";

    SDL_Event event;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
	printMsg("Failed to init SDl2");
        exit(1);
    }

    // Window
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
    SDL_Texture *wizard = loadTexture("Images/wizard.bmp", ren);
    SDL_Texture *zombie = loadTexture("Images/zombie.bmp", ren);
    SDL_Texture *wizard_cast = loadTexture("Images/wizard-cast.bmp", ren);
    SDL_Texture *magic_sword = loadTexture("Images/magic-sword.bmp", ren);
    SDL_Texture *magic_shield = loadTexture("Images/magic-shield.bmp", ren);


    while (!quit)
    {
        SDL_Delay(1);
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
            case SDLK_SPACE:  show_magic = "magic_sword"; break;
            case SDLK_TAB:  show_magic = "magic_shield"; break;

            case SDLK_LEFT:  x = x - 5; show_magic = ""; break;
            case SDLK_RIGHT: x = x + 5; show_magic = ""; break;
            case SDLK_UP:    y = y - 5; show_magic = ""; break;
            case SDLK_DOWN:  y = y + 5; show_magic = ""; break;

        }
        break;
        }

        loop++;
        if (debug == 1) {
            cout << "loop: " << loop << endl;
            cout << "show_magic: " << show_magic << endl;
        }

        SDL_RenderClear(ren);


        // Background
        SDL_RenderCopy(ren, bg, NULL, NULL);

        //printMsg("Result: " + to_string(loop % 3));

        if (loop > 100)
        {
            loop = 0;
            //player.update_health(10);
            player.print_stats();
            foe.print_stats();
        }

        if (show_magic == "magic_sword") {
            SDL_Rect dstrect1 = {x-40, y-5, 64, 64};
            SDL_RenderCopy(ren, magic_sword, NULL, &dstrect1);

            // Wizard Cast
            SDL_Rect dstrect2 = { x, y, 64, 64 };
            SDL_RenderCopy(ren, wizard_cast, NULL, &dstrect2);

        } else if (show_magic == "magic_shield") {
            SDL_Rect dstrect1 = {x-40, y-5, 64, 64};
            SDL_RenderCopy(ren, magic_shield, NULL, &dstrect1);

            // Wizard Cast
            SDL_Rect dstrect2 = { x, y, 64, 64 };
            SDL_RenderCopy(ren, wizard_cast, NULL, &dstrect2);

        } else {

            // Wizard
            SDL_Rect dstrect2 = { x, y, 64, 64 };
            SDL_RenderCopy(ren, wizard, NULL, &dstrect2);

            // Foe
            //foe_location = return_location()
            Foe::Foe_Location foe_loc2;
            foe_loc2 = foe.return_location();
            SDL_Rect dstrect3 = { foe_loc2.x, foe_loc2.y, 64, 64 };
            SDL_RenderCopy(ren, zombie, NULL, &dstrect3);

            //cout << " x " << foe_loc2.x << " x " << x << endl;
            //cout << " y " << foe_loc2.y << " y " << y << endl;
            if (foe_loc2.x < x + 50 && foe_loc2.y < y + 50 && foe_loc2.x > x - 50 && foe_loc2.y > y - 50)
            {
                cout << " **** damage ***" << endl;
                player.update_health(10);
            }
        }
        SDL_RenderPresent(ren);
    }

    SDL_DestroyTexture(bg);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
