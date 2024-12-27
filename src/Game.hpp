// Author: https://github.com/electronicsleep
// Purpose: Shadow Forest
// Released under the BSD license

using namespace std;

class Game {
  public:

  void print_name(const char* name) {
    cout << "Game: " << name << endl;
  }

  void update_hud(SDL_Renderer* render, TTF_Font* Sans, int health, int level, int score) {
    int SDL_Result = 0;
    char hud_txt[80];
    int texW = 0;
    int texH = 0;

    std::string health_string = std::to_string(health);
    std::string level_string = std::to_string(level);
    std::string score_string = std::to_string(score);

    const char *health_title = "Health: ";
    const char *health_value = health_string.c_str();
    const char *level_title = " Level: ";
    const char *level_value = level_string.c_str();
    const char *score_title = " Score: ";
    const char *score_value = score_string.c_str();

    SDL_Color White = {255, 255, 255};
    SDL_Color Red = {255, 0, 0};

    strcpy(hud_txt, health_title);
    strcat(hud_txt, health_value);
    strcat(hud_txt, level_title);
    strcat(hud_txt, level_value);
    strcat(hud_txt, score_title);
    strcat(hud_txt, score_value);

    SDL_Surface* surfaceMessage;
    if (health > 50) {
        surfaceMessage = TTF_RenderText_Solid(Sans, hud_txt, White);
    } else {
        surfaceMessage = TTF_RenderText_Solid(Sans, hud_txt, Red);
    }
    SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);

    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 0, 0, texW, texH };

    SDL_Result = SDL_RenderCopy(render, Message, NULL, &dstrect);

    if (SDL_Result < 0) {
        SDL_Quit();
    }

    SDL_FreeSurface(surfaceMessage);
  }
};
