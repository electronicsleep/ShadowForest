// Author: https://github.com/electronicsleep
// Purpose: Shadow Forest
// Released under the BSD license

using namespace std;

class Foe {
 public:

  struct Foe_Location {
    int x, y = 0;
  };

  Foe_Location foe_loc;
  string player_name = "Foe1";
  string player_type = "Zombie";
  int health = 100;
  int exp = 0;
  int str = 0;
  int dex = 0;
  int intelligence = 0;



  void is_alive(Foe* foe) {
    cout << "Foe is alive";
  }

  Foe_Location return_location() {
    foe_loc = move_diagnal();
    if (foe_loc.x > 500) {
      foe_loc.x = 0;
      int y2;
      y2 = (rand()%300)+1;
      foe_loc.y = y2;
    }
    return foe_loc;
  }

  Foe_Location move_diagnal(){
    foe_loc.x++;
    foe_loc.y++;
    return foe_loc;
  }

  void set_location(int x, int y) {
    foe_loc.x = x;
    foe_loc.y = y;
  }

  void print_name(const char* name) {
    cout << "Foe name is " << name << endl;
  }

  void print_stats() {
    cout << "###### Stats ######" << endl;
    cout << "Foe health is " << health << endl;
    cout << "Foe experience is " << exp << endl;
    cout << "Foe strength is " << str << endl;
    cout << "Foe dexterity is " << dex << endl;
    cout << "Foe intelligence is " << intelligence << endl;
  }

  void update_exp() {
    exp++;
    cout << "Foe experience is now: " << exp << endl;
  }

  void update_health(int amount) {
    health = health - amount;
    cout << "Foe health is now: " << health << endl;

    if (health < 0) {
        cout << "Foe has died... " << endl;
   }
  }

};
