#include <iostream>
#include <string>
#include <sstream>
#include "grid.h"

using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid grid;
  string startLevel = argv[__]; /////insert index of startlevel cmd arg
  if (startLevel == "0") {
    grid.init(LevelType::Level0, false, "sequence.txt");
  }
  else if (startLevel == "1") {
    grid.init(LevelType::Level1);
  }
  else if (startLevel == "2") {
    grid.init(LevelType::Level2);
  }
  else if (startLevel == "3") {
    grid.init(LevelType::Level3);
  }
  else if (startLevel == "4") {
    grid.init(LevelType::Level4);
  }
  else {  // if no startlevel option is supplied, start at Level 0
    grid.init(LevelType::Level0, false, "sequence.txt");
  }
  try {
    while (true) {
      cin >> cmd;

      // pass in file assuming it is valid
      // handle if file does not exist case in Level and Grid
      istringstream iss{cmd};
      
      int n = 1;

      iss >> n;
      iss >> cmd;

      string str[13] = {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence", "restart", "hint"};
      int counter = 0;
      string newcmd;
      for (int i = 0; i < 13; i++) {
        if (str[i].find(cmd) == 0) {
          counter++;
          newcmd = str[i]
        }
      }

      if (counter != 1) continue;

      if (newcmd == "left") {
        grid.left(n);
      } else if (cmd.find("ri") == 0) {
	      grid.right(n);
      } else if (cmd.find("do") == 0) {
	      grid.down(n);
      } else if (cmd.find("cl") == 0) {
	      grid.clockwise(n);
      } else if (cmd == "counterclockwise") {
	      grid.counterclockwise(n);
      } else if (cmd == "drop") {
	      grid.drop(n);
      } else if (cmd == "levelup") {
	      grid.levelUp(n);
      } else if (cmd == "leveldown") {
	      grid.levelDown(n);
      } else if (cmd == "norandom") {
        string file;
        if (cin >> file) {
          ifstream fileStream{file};
          // create copy ctor for Level 3/4, pass in new fileStream???
          grid.random(false, file);
        }
      } else if (cmd == "random") {
	  
      } else if (cmd == "sequence") {
	      string file;
	      if (cin >> file) {
	        grid.random(false, file);
	      }
      } else if (cmd == "restart") {

      } else if (cmd == "hint") {

      }
    }
  } catch (ios::failure &) {}

}
