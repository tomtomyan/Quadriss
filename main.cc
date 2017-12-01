#include <iostream>
#include <string>
#include "grid.h"

using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid grid;
  string startLevel = argv[__]; /////insert index of startlevel cmd arg
  //string fileName = "sequence.txt";
  ifstream fileStream{};
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
  while (true) {

  }
  try {
    while (true) {
      cin >> cmd;
      if (cmd == "left") {
          grid.left();
      } else if (cmd == "right") {
	  grid.right();
      } else if (cmd == "down") {
	  grid.down();
      } else if (cmd == "clockwise") {
	  grid.clockwise();
      } else if (cmd == "counterclockwise") {
	  grid.counterclockwise();
      } else if (cmd == "drop") {
	  grid.drop();
      } else if (cmd == "levelup") {
	  grid.levelUp();
      } else if (cmd == "leveldown") {
	  grid.levelDown();
      } else if (cmd == "norandom") {
          string file;
          if (cin >> file) {
            ifstream fileStream{file};
// create copy ctor for Level 3/4, pass in new fileStream???
            while (
          }
      } else if (cmd == "random") {
	  
      } else if (cmd == "sequence") {
	  string file;
	  if (cin >> file) {
	    grid.random(
	  }
      } else if (cmd == "restart") {

      } else if (cmd == "hint") {

      } 


    }
  } catch (ios::failure &) {}

}
