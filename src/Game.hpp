// Author: https://github.com/electronicsleep
// Purpose: Shadow Forest
// Released under the BSD license

using namespace std;

class Game {
public:

  void print_name(const char* name) {
    cout << "Game: " << name << endl;
  }

  SDL_Texture* update_hud(SDL_Renderer *render, const char* health) {
    int SDL_Result = 0;
    TTF_Font* Sans = TTF_OpenFont("OpenSans-Regular.ttf", 12);
    printf("OpenFont: %s\n", SDL_GetError());
    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, health, White);
    printf("RenderText: %s\n", SDL_GetError());
    SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);
    printf("CreateTexture: %s\n", SDL_GetError());

    //SDL_Result = SDL_RenderCopy(render, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    printf("RenderHUD: %s\n", SDL_GetError());

    if (SDL_Result < 0) {
    printf("HUD failed: %s\n", SDL_GetError());
    SDL_Quit();
    }
    printf("HUD Render Finished\n");
    return Message;
  }

};
