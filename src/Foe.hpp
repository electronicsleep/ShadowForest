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

  Foe_Location reset_foe() {
   foe_loc = respawn_foe();
   return foe_loc;
  }

  Foe_Location reset_foe_right() {
   foe_loc = respawn_foe_right();
   return foe_loc;
  }

  Foe_Location respawn_foe() {
   foe_loc.x = rand()%400;
   foe_loc.y = rand()%200;
   return foe_loc;
  }

  Foe_Location respawn_foe_right() {
   foe_loc.x = rand()%600;
   foe_loc.y = rand()%800;
   return foe_loc;
  }

  Foe_Location return_location_left(int level) {
    int decide_move = rand();
    if (level > 1) {
      foe_loc = move_diagonal_left();
      foe_loc = move_down(5);
    }
    if (decide_move % 3 == 0) {
       foe_loc = move_diagonal_left();
       foe_loc = move_down(5);
    } else {
       foe_loc = move_diagonal2_left();
    }
    return foe_loc;
  }

    Foe_Location return_location_right(int level) {
    int decide_move = rand();
    if (level > 1) {
      foe_loc = move_diagonal_right();
    }
    if (decide_move % 3 == 0) {
      foe_loc = move_diagonal_right();
    } else {
      foe_loc = move_diagonal_right();
    }
    return foe_loc;
  }

  Foe_Location move_diagonal_left(){
    foe_loc.x++;
    foe_loc.y++;
    return foe_loc;
  }

  Foe_Location move_diagonal_right(){
    foe_loc.x--;
    foe_loc.y--;
    return foe_loc;
  }

  Foe_Location move_diagonal2_left(){
    foe_loc.x += 2;
    foe_loc.y += 2;
    return foe_loc;
  }

  Foe_Location move_down(int move){
    foe_loc.y = foe_loc.y + move;
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

  int update_health(int amount) {
    health = health - amount;
    cout << "Foe health is now: " << health << endl;

    if (health < 0) {
        cout << "Foe has died... " << endl;
        return 1;
   }
  return 0;
  }

};
