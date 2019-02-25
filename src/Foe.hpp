
using namespace std;

class Foe
{
 public:
  string player_name = "Foe1";
  string player_type = "Zombie";
  int health = 100;
  int exp = 0;
  int str = 0;
  int dex = 0;
  int intelligence = 0;

  void is_alive(Foe* foe)
  {
    cout << "Foe is alive";
  }

  void print_name(const char* name)
  {
    cout << "Foe name is " << name << endl;
  }

  void print_stats()
  {
    cout << "###### Stats ######" << endl;
    cout << "Foe health is " << health << endl;
    cout << "Foe experience is " << exp << endl;
    cout << "Foe strength is " << str << endl;
    cout << "Foe dexterity is " << dex << endl;
    cout << "Foe intelligence is " << intelligence << endl;
  }

   void update_exp()
  {
    exp++;
    cout << "Foe experience is now: " << exp << endl;
  }

   void update_health(int amount)
  {
    health = health - amount;
    cout << "Foe health is now: " << health << endl;

    if (health < 0) {
        cout << "Foe has died... " << endl;
   }
  }
};
