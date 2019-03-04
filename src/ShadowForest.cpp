// Author: https://github.com/electronicsleep
// Purpose: Shadow Forest
// Released under the BSD license

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <time.h>

#include "Player.hpp"
#include "Foe.hpp"

using namespace std;

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const int debug = 0;

void printMsg(string msg) {
    cout << msg << endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != NULL) {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == NULL) {
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
    Foe foe2;
    foe.set_location(300, 300);
    foe2.set_location(100, 100);
    player.print_name("Chris");
    foe.print_name("Zombie1");
    foe2.print_name("Zombie2");
    int foes_destroy = 0;
    int time = 0;
    //player.print_stats();
    //foe.print_stats();
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
    SDL_Texture *zombie_hit = loadTexture("Images/zombie-hit.bmp", ren);
    SDL_Texture *wizard_cast = loadTexture("Images/wizard-cast.bmp", ren);
    SDL_Texture *magic_sword = loadTexture("Images/magic-sword.bmp", ren);
    SDL_Texture *magic_shield = loadTexture("Images/magic-shield.bmp", ren);
    SDL_Texture *damage = loadTexture("Images/damage.bmp", ren);

    while (!quit) {
        SDL_Delay(1);
        SDL_PollEvent(&event);


        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                printMsg("QUIT");
                break;

            case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
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

        if (loop > 100) {
            loop = 0;
            //player.print_stats();
            //foe.print_stats();
        }

        // Foe1
        Foe::Foe_Location foe_loc1;
        foe_loc1 = foe.return_location();

        // Foe2
        Foe::Foe_Location foe_loc2;
        foe_loc2 = foe2.return_location();

        if (show_magic == "magic_sword") {
            SDL_Rect magic_sword_bmp = {x-40, y-5, 64, 64};
            SDL_RenderCopy(ren, magic_sword, NULL, &magic_sword_bmp);

            // Wizard Cast
            SDL_Rect wizard_cast_bmp = { x, y, 64, 64 };
            SDL_RenderCopy(ren, wizard_cast, NULL, &wizard_cast_bmp);

            if (foe_loc1.x < x + 60 && foe_loc1.y < y + 60 && foe_loc1.x > x - 60 && foe_loc1.y > y - 60) {

                cout << " **** damage foe ***" << endl;
                SDL_Rect zombie_hit_bmp = { foe_loc1.y, foe_loc1.x, 64, 64 };
                SDL_RenderCopy(ren, zombie_hit, NULL, &zombie_hit_bmp);

                // Red Box
                SDL_Rect damage_bmp = { foe_loc1.y, foe_loc1.x, 64, 64 };
                SDL_RenderCopy(ren, damage, NULL, &damage_bmp);

                    int foe_death;
                    foe_death = foe.update_health(5);
                    if (foe_death == 1) {
                        foes_destroy++;
                        cout << " --> foes_destroy: " << foes_destroy << endl;
                        foe.reset_foe();
                        foe.health = 0;
                    }
                }

            if (foe_loc2.x < x + 60 && foe_loc2.y < y + 60 && foe_loc2.x > x - 60 && foe_loc2.y > y - 60) {

                cout << " **** damage foe ***" << endl;

                SDL_Rect zombie_hit_bmp = { foe_loc2.y, foe_loc2.x, 64, 64 };
                SDL_RenderCopy(ren, zombie_hit, NULL, &zombie_hit_bmp);

                // Red Box
                SDL_Rect damage_bmp = { foe_loc2.y, foe_loc2.x, 64, 64 };
                SDL_RenderCopy(ren, damage, NULL, &damage_bmp);

                    int foe_death;
                    foe_death = foe.update_health(5);
                    if (foe_death == 1) {
                        foes_destroy++;
                        cout << " --> foes_destroy: " << foes_destroy << endl;
                        foe2.reset_foe();
                        foe2.health = 0;
                    }
                }

        } else if (show_magic == "magic_shield") {
            SDL_Rect foe_hit_bmp = {x-40, y-5, 64, 64};
            SDL_RenderCopy(ren, magic_shield, NULL, &foe_hit_bmp);

            // Wizard Cast
            SDL_Rect wizard_cast_bmp = { x, y, 64, 64 };
            SDL_RenderCopy(ren, wizard_cast, NULL, &wizard_cast_bmp);

        } else {
            // Wizard
            SDL_Rect wizard_bmp = { x, y, 64, 64 };
            SDL_RenderCopy(ren, wizard, NULL, &wizard_bmp);
        }


        SDL_Rect zombie1_bmp = { foe_loc1.x, foe_loc1.y, 64, 64 };
        SDL_RenderCopy(ren, zombie, NULL, &zombie1_bmp);


        SDL_Rect zombie2_bmp = { foe_loc2.x, foe_loc2.y, 64, 64 };
        SDL_RenderCopy(ren, zombie, NULL, &zombie2_bmp);


        //SDL_Rect zombie_hit_bmp = { foe_loc2.x, foe_loc2.y, 64, 64 };
        //SDL_RenderCopy(ren, zombie, NULL, &zombie_hit_bmp);


        //cout << " x " << foe_loc2.x << " x " << x << endl;
        //cout << " y " << foe_loc2.y << " y " << y << endl;
        if (foe_loc2.x < x + 50 && foe_loc2.y < y + 50 && foe_loc2.x > x - 50 && foe_loc2.y > y - 50) {
            cout << " **** damage player ***" << endl;
            SDL_Rect damage_bmp = { x, y, 64, 64 };
            SDL_RenderCopy(ren, damage, NULL, &damage_bmp);
            player.update_health(2);
        }

        if (foe_loc1.x < x + 50 && foe_loc1.y < y + 50 && foe_loc1.x > x - 50 && foe_loc1.y > y - 50) {
            cout << " **** damage player ***" << endl;
            SDL_Rect damage_bmp = { x, y, 64, 64 };
            SDL_RenderCopy(ren, damage, NULL, &damage_bmp);
            player.update_health(2);
        }

        time++;
        SDL_RenderPresent(ren);
    }

    SDL_DestroyTexture(bg);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
