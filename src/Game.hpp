// Author: https://github.com/electronicsleep
// Purpose: Shadow Forest
// Released under the BSD license

using namespace std;

class Game {
public:

  void print_name(const char* name) {
    cout << "Game: " << name << endl;
  }

  void update_hud(SDL_Renderer* render, TTF_Font* Sans, int health) {
    int SDL_Result = 0;
    SDL_Color White = {255, 255, 255};
    SDL_Color Red = {255, 0, 0};

    std::string health_string = std::to_string(health);
    char const *hud_text = health_string.c_str();

    SDL_Surface* surfaceMessage;
    if (health > 50) {
        surfaceMessage = TTF_RenderText_Solid(Sans, hud_text, White);
    } else {
        surfaceMessage = TTF_RenderText_Solid(Sans, hud_text, Red);
    }
    SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);

          SDL_Rect Message_rect;
          Message_rect.x = 0;
          Message_rect.y = 0;
          Message_rect.w = 100;
          Message_rect.h = 50;

    SDL_Result = SDL_RenderCopy(render, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    if (SDL_Result < 0) {
    SDL_Quit();
    }

    SDL_FreeSurface(surfaceMessage);
  }

};
