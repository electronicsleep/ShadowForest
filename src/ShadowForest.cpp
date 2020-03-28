// Author: https://github.com/electronicsleep
// Purpose: Shadow Forest
// Released under the BSD license

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <time.h>

#include "Game.hpp"
#include "Player.hpp"
#include "Foe.hpp"

using namespace std;

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const int debug = 0;

void printMsg(string msg) {
    cout << msg << endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *render) {
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != NULL) {
        texture = SDL_CreateTextureFromSurface(render, loadedImage);
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

void renderTexture(SDL_Texture *tex, SDL_Renderer *render, int x, int y){
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(render, tex, NULL, &dst);
}

void checkLevel(int foes_destroyed, int &level, int &start_game) {
    if (foes_destroyed == 10 or foes_destroyed == 20) {
      level++;
      cout << "You have reached level: " << level << endl;
      cout << "Press spacebar to restart." << endl;
      start_game = 0;
    }
}

int main(int argc, char ** argv) {
    Game game;
    Player player;
    Foe foe;
    Foe foe2;
    foe.set_location(300, 300);
    foe2.set_location(100, 100);
    game.print_name("Shadow Forest");
    player.print_name("Logan");
    foe.print_name("Zombie1");
    foe2.print_name("Zombie2");
    int foes_destroyed = 0;
    int foes_missed = 0;
    int time = 0;
    string show_magic = "";

    int x = 200;
    int y = 200;

    int weapon_offset = 80;
    string move_direction = "left";

    int loop = 0;
    bool quit = false;

    int start_game = 0;
    int game_over = 0;
    int level = 1;

    // foe hit points
    int hit_points = 15;
    int foe_destroyed = 0;
    int display_hud = 0;

    string errorMsg = "";
    SDL_Event event;
    int SDL_Result = 0;


    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
	printMsg("Failed to init SDl2");
        exit(1);
    }

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


    if(TTF_Init() < 0) {
        printf("TTF Init failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    if (window == NULL) {
        errorMsg = SDL_GetError();
        printMsg("Could not create window: " + errorMsg);
        return 1;
    }

    //Required for SDL_RenderCopy
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == NULL) {
        SDL_DestroyWindow(window);
        errorMsg = SDL_GetError();
        printMsg("SDL_CreateRenderer Error" + errorMsg);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *bg = loadTexture("Images/background.bmp", render);
    SDL_Texture *shadow_forest_title = loadTexture("Images/shadow-forest-title.bmp", render);
    SDL_Texture *shadow_forest_game_over = loadTexture("Images/shadow-forest-game-over.bmp", render);
    SDL_Texture *wizard = loadTexture("Images/wizard.bmp", render);
    SDL_Texture *wizard_right = loadTexture("Images/wizard-right.bmp", render);
    SDL_Texture *wizard_top = loadTexture("Images/wizard-top.bmp", render);
    SDL_Texture *zombie = loadTexture("Images/zombie.bmp", render);
    SDL_Texture *zombie_right = loadTexture("Images/zombie-right.bmp", render);
    SDL_Texture *wizard_cast = loadTexture("Images/wizard-cast.bmp", render);
    SDL_Texture *magic_sword = loadTexture("Images/magic-sword.bmp", render);
    SDL_Texture *magic_sword_right = loadTexture("Images/magic-sword-right.bmp", render);
    SDL_Texture *magic_shield = loadTexture("Images/magic-shield.bmp", render);
    SDL_Texture *damage = loadTexture("Images/damage.bmp", render);
    SDL_Texture *warning = loadTexture("Images/warning.bmp", render);

    while (!quit) {
        SDL_Delay(1);
        SDL_PollEvent(&event);

        if (game_over == 1) {
            start_game = 0;
        }

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                printMsg("QUIT");
                break;

            case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:  show_magic = "magic_sword"; start_game = 1; game_over = 0; break;
                case SDLK_TAB:  show_magic = "magic_shield"; break;

                case SDLK_LEFT:  x = x - 5; show_magic = ""; move_direction = "left"; break;
                case SDLK_RIGHT: x = x + 5; show_magic = ""; move_direction = "right"; break;
                case SDLK_UP:    y = y - 5; show_magic = ""; move_direction = "up"; break;
                case SDLK_DOWN:  y = y + 5; show_magic = ""; move_direction = "down";
            }
            break;
        }

        loop++;
        if (debug == 1) {
            cout << "loop increment: " << loop << endl;
            cout << "show_magic: " << show_magic << endl;
        }

        SDL_RenderClear(render);

        // Background
        SDL_Result = SDL_RenderCopy(render, bg, NULL, NULL);

        if (display_hud == 0) {
          SDL_Rect Message_rect;
          Message_rect.x = 0;
          Message_rect.y = 0;
          Message_rect.w = 100;
          Message_rect.h = 50;

          SDL_Texture* Message = game.update_hud(render, "hello");
          SDL_Result = SDL_RenderCopy(render, Message, NULL, &Message_rect);
          display_hud = 1;
        }

        if (game_over == 1) {
          SDL_Rect shadow_forest_game_over_bmp = { 0, 200, 300, 400 };
          SDL_RenderCopy(render, shadow_forest_game_over, NULL, &shadow_forest_game_over_bmp);
        } else if (start_game == 0) {
          SDL_Rect shadow_forest_title_logo_bmp = { 0, 200, 300, 400 };
          SDL_RenderCopy(render, shadow_forest_title, NULL, &shadow_forest_title_logo_bmp);
        }

        if (loop > 100) {
            loop = 0;
        }

        if (start_game == 1) {

            if (level == 2) {
                hit_points=5;
            } else if (level == 3) {
                hit_points=1;
            }

            // Foe1
            Foe::Foe_Location foe_loc1;
            foe_loc1 = foe.return_location_left(level);
            if (foe_loc1.x > 600 or foe_loc1.y > 800) {
              foe_loc1 = foe.respawn_foe();
              foes_missed++;
              cout << "foes_missed: " << foes_missed << endl;
            }

            // Foe2
            Foe::Foe_Location foe_loc2;
            foe_loc2 = foe2.return_location_right(level);
            if (foe_loc2.x < 0 or foe_loc2.y < 0) {
              foe_loc2 = foe2.respawn_foe_right();
              foes_missed++;
              cout << "foes_missed: " << foes_missed << endl;
            }

            if (show_magic == "magic_sword") {
                // Wizard Cast
                if (move_direction == "left") {
                    renderTexture(magic_sword, render, x-40, y-5);
                    renderTexture(wizard_cast, render, x, y);
                } else {
                    renderTexture(magic_sword_right, render, x+40, y-5);
                    renderTexture(wizard_right, render, x, y);
                }

                if (debug == 1) {
                    // Proximity
                    renderTexture(warning, render, x-40, y-5);
                }

                if (debug == 1) {
                    cout << "foe_loc1: " << foe_loc1.x << " ";
                    cout << foe_loc1.y << " " << endl;
                }

                if (foe_loc1.x < x + weapon_offset && foe_loc1.y < y + weapon_offset && foe_loc1.x > x - weapon_offset && foe_loc1.y > y - weapon_offset) {
                    cout << " **** damage foe ***" << endl;

                    // Red Box Damage
                    renderTexture(damage, render, foe_loc1.x, foe_loc1.y);

                    foe_destroyed = foe.update_health(hit_points);
                    if (foe_destroyed == 1) {
                        foes_destroyed++;
                        player.print_foes_destroyed(foes_destroyed);
                        show_magic = "";
                        checkLevel(foes_destroyed, level, start_game);

                        foe.reset_foe();
                        foe.health = 0;
                    }
                }

                if (foe_loc2.x < x + weapon_offset && foe_loc2.y < y + weapon_offset && foe_loc2.x > x - weapon_offset && foe_loc2.y > y - weapon_offset) {
                    cout << " **** damage foe ***" << endl;

                    // Red Damage Box
                    renderTexture(damage, render, foe_loc2.x, foe_loc2.y);

                    foe_destroyed = foe.update_health(hit_points);
                    if (foe_destroyed == 1) {
                        foes_destroyed++;
                        player.print_foes_destroyed(foes_destroyed);
                        show_magic = "";
                        checkLevel(foes_destroyed, level, start_game);

                        foe2.reset_foe_right();
                        foe2.health = 0;
                    }
                }

            } else if (show_magic == "magic_shield") {
                SDL_Rect foe_hit_bmp = {x-40, y-5, 64, 64};
                SDL_RenderCopy(render, magic_shield, NULL, &foe_hit_bmp);

                // Wizard Cast
                SDL_Rect wizard_cast_bmp = { x, y, 64, 64 };
                SDL_RenderCopy(render, wizard_cast, NULL, &wizard_cast_bmp);
            } else {
                // Wizard
                if (move_direction == "left") {
                    SDL_Rect wizard_bmp = { x, y, 64, 64 };
                    SDL_RenderCopy(render, wizard, NULL, &wizard_bmp);
                } else if (move_direction == "right") {
                    SDL_Rect wizard_right_bmp = { x, y, 64, 64 };
                    SDL_RenderCopy(render, wizard_right, NULL, &wizard_right_bmp);
                } else {
                    SDL_Rect wizard_top_bmp = { x, y, 64, 64 };
                    SDL_RenderCopy(render, wizard_top, NULL, &wizard_top_bmp);
                }
            }

            SDL_Rect zombie1_bmp = { foe_loc1.x, foe_loc1.y, 64, 64 };
            SDL_RenderCopy(render, zombie, NULL, &zombie1_bmp);

            SDL_Rect zombie_right_bmp = { foe_loc2.x, foe_loc2.y, 64, 64 };
            SDL_RenderCopy(render, zombie_right, NULL, &zombie_right_bmp);

            if (foe_loc2.x < x + 50 && foe_loc2.y < y + 50 && foe_loc2.x > x - 50 && foe_loc2.y > y - 50) {
                cout << " **** damage player ***" << endl;
                renderTexture(damage, render, x, y);
                player.print_foes_destroyed(foes_destroyed);
                player.update_health(2, foes_missed, foes_destroyed, game_over, level);
            }

            if (foe_loc1.x < x + 50 && foe_loc1.y < y + 50 && foe_loc1.x > x - 50 && foe_loc1.y > y - 50) {
                cout << " **** damage player ***" << endl;
                renderTexture(damage, render, x, y);
                player.print_foes_destroyed(foes_destroyed);
                player.update_health(2, foes_missed, foes_destroyed, game_over, level);
            }


        } // End start game

    time++;
    SDL_RenderPresent(render);

    } // End run game

SDL_DestroyTexture(bg);
SDL_DestroyRenderer(render);
SDL_DestroyWindow(window);

SDL_Quit();
return 0;
}
