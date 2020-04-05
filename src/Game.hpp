// Author: https://github.com/electronicsleep
// Purpose: Shadow Forest
// Released under the BSD license

using namespace std;

class Game {
public:

  void print_name(const char* name) {
    cout << "Game: " << name << endl;
  }

  void update_hud(SDL_Renderer* render, TTF_Font* Sans, int health, int level) {
    int SDL_Result = 0;
    SDL_Color White = {255, 255, 255};
    SDL_Color Red = {255, 0, 0};

    std::string health_string = std::to_string(health);
    std::string level_string = std::to_string(level);

    const char *health_title = "Health: ";
    const char *health_value = health_string.c_str();
    const char *level_title = " Level: ";
    const char *level_value = level_string.c_str();

    char hud_txt[80];
    strcpy(hud_txt, health_title);
    strcat(hud_txt, health_value);
    strcat(hud_txt, level_title);
    strcat(hud_txt, level_value);
    puts(hud_txt);

    SDL_Surface* surfaceMessage;
    if (health > 50) {
        surfaceMessage = TTF_RenderText_Solid(Sans, hud_txt, White);
    } else {
        surfaceMessage = TTF_RenderText_Solid(Sans, hud_txt, Red);
    }
    SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);

          SDL_Rect Message_rect;
          Message_rect.x = 0;
          Message_rect.y = 0;
          Message_rect.w = 300;
          Message_rect.h = 50;

    SDL_Result = SDL_RenderCopy(render, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    if (SDL_Result < 0) {
    SDL_Quit();
    }

    SDL_FreeSurface(surfaceMessage);
  }

};
