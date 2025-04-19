// Author: https://github.com/electronicsleep
// Purpose: Shadow Forest
// Released under the BSD license

using namespace std;

class Player {
  public:
    string player_name = "Logan";
    string player_type = "Wizard";
    int health = 100;
    int exp = 0;
    int str = 0;
    int dex = 0;
    int intelligence = 0;

  int get_health() {
    return health;
  }

  void print_name(const char* name) {
    cout << "Player name is " << name << endl;
  }

  void print_stats() {
    cout << "###### Stats ######" << endl;
    cout << "Player health is " << health << endl;
    cout << "Player experience is " << exp << endl;
    cout << "Player strength is " << str << endl;
    cout << "Player dexterity is " << dex << endl;
    cout << "Player intelligence is " << intelligence << endl;
  }

  void print_foes_destroyed(int foes_destroyed) {
    cout << " **** Foes Destroyed: " << foes_destroyed << endl;
  }

  void update_exp() {
    exp++;
    cout << "Player experience is now: " << exp << endl;
  }

  void update_health(int amount, int &foes_missed, int &foes_destroyed, bool &game_over, int &level) {
    int score = 0;
    health = health - amount;
    cout << "Player health is now: " << health << endl;

    if (health <= 0) {
      cout << " ***************" << endl;
      cout << "Player has died... Game Over" << endl;
      cout << " ******** STATS: " << endl;
      cout << " **** Foes Destroyed: " << foes_destroyed << endl;
      cout << " **** Foes Missed: " << foes_missed << endl;
      cout << " **** Level: " << level << endl;
      score = foes_destroyed - foes_missed;
      cout << " **** Score: " << score << endl;

      if (foes_destroyed > foes_missed) {
        cout << "You defeated your foes, nice work." << endl;
      } else {
        cout << "You where defeated by your foes." << endl;
      }

      if (score >= 100) {
        cout << "**** Awesome score! " << score << endl;
      }

      cout << "Game Over." << endl;
      cout << "Reset game stats." << endl;
      cout << "Press spacebar to restart." << endl;
      game_over = true;
      foes_missed = 0;
      foes_destroyed = 0;
      health = 100;
      level = 1;
    }
  }
};
