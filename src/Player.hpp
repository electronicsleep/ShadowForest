
using namespace std;

class Player
{
 public:
  string player_name = "Chris";
  string player_type = "Wizard";
  int exp = 0;

  int str = 0;
  int dex = 0;
  int intelligence = 0;

  void is_alive(Player* player)
   {
    cout << "Player is alive";
   }

  void print_name(const char* name)
   {
    cout << "Player name is " << name << endl;
   }

  void print_stats()
   {
    cout << "###### Stats ######" << endl;
    cout << "Player experience is " << exp << endl;
    cout << "Player str is " << str << endl;
    cout << "Player dex is " << dex << endl;
    cout << "Player intelligence is " << intelligence << endl;
   }

   void update_exp()
   {
   	exp++;
    cout << "Player experience is now: " << exp << endl;
   }
};
