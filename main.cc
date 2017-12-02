#include <iostream>
#include <string>
#include <sstream>
#include "grid.h"

using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid grid;

  bool textOnly = false;
  string scriptFile = "";
  string startLevel = "0"; //default start level

  //COMMAD LINE ARGUMENTS
  for (int i = 1; i < argc; i++) {
    if (argv[i] == std::string("-text")) {
      textOnly = true;
    } else if (argv[i] == std::string("-seed")) {
      //set random number seed
    } else if (argv[i] == std::string("-scriptfile")) {
      if (i+1 < argc) scriptFile = argv[i+1];
    } else if (argv[i] == std::string("-startlevel")) {
      if (i+1 < argc) startLevel = argv[i+1];
    }
  }
  if (startLevel == "0") {
    grid.init(LevelType::Level0, false, "sequence.txt");
  } else if (startLevel == "1") {
    grid.init(LevelType::Level1);
  } else if (startLevel == "2") {
    grid.init(LevelType::Level2);
  } else if (startLevel == "3") {
    grid.init(LevelType::Level3);
  } else if (startLevel == "4") {
    grid.init(LevelType::Level4);
  } else {  // if no startlevel option is supplied, start at Level 0
    grid.init(LevelType::Level0, false, "sequence.txt");
  }

  //COMMAND INTERPRETER
  try {
      string str[13] = {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence", "restart", "hint"};
    while (true) {
      cin >> cmd;

      // pass in file assuming it is valid
      // handle if file does not exist case in Level and Grid
      istringstream iss{cmd};
      
      int n = 1;

      iss >> n;
      iss >> cmd;

      int counter = 0; //counter stores occurences where the cmd is found in the list of strings
      string newcmd;
      for (int i = 0; i < 13; i++) {
        if (str[i].find(cmd) == 0) {
          counter++;
          newcmd = str[i];
        }
      }

      if (counter != 1) continue; //if it isn't 1 then restart the loop

      if (newcmd == "left") {
        grid.left(n);
      } else if (newcmd == "right") {
	      grid.right(n);
      } else if (newcmd == "down") {
	      grid.down(n);
      } else if (newcmd == "clockwise") {
	      grid.clockwise(n);
      } else if (newcmd == "counterclockwise") {
	      grid.counterClockwise(n);
      } else if (newcmd == "drop") {
	      grid.drop(n);
      } else if (newcmd == "levelup") {
	      grid.levelUp(n);
      } else if (newcmd == "leveldown") {
	      grid.levelDown(n);
      } else if (newcmd == "norandom") {
        string file;
        if (cin >> file) {
          ifstream fileStream{file};
          // create copy ctor for Level 3/4, pass in new fileStream???
          grid.random(false, file);
        }
      } else if (newcmd == "random") {
	      grid.random(true);
      } else if (newcmd == "sequence") {
	      string file;
	      if (cin >> file) {
	        grid.random(false, file);
	      }
      } else if (newcmd == "restart") {
        
      } else if (newcmd == "hint") {
        grid.hint();
      }
    }
  } catch (ios::failure &) {}

}
