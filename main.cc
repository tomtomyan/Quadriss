#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "grid.h"
#include "graphicsdisplay.h"
using namespace std;


int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid grid;
  shared_ptr<GraphicsDisplay> graphDis = make_shared<GraphicsDisplay>(380, 700);
  grid.attachObserver(graphDis);
  // Vector holds all of the known commands
  vector<vector<string>> allCmds;
  for (int i = 0; i < 13; ++i) {  // Remove?
    vector<string> cmdType;
    allCmds.emplace_back(cmdType);
  }

  bool textOnly = false;
  string scriptFile = "sequence.txt";
  string startLevel = "0"; // default start level
  bool isSequence = false;
  bool seqFirstTime = true;
  string fileName;  // if isSequence is true, read commands from this file
  ifstream fileStream;
  int seed = 123;

  //COMMAD LINE ARGUMENTS
  for (int i = 1; i < argc; i++) {
    if (argv[i] == std::string("-text")) {
      textOnly = true;
      cout << "Text only mode" << endl;
    } else if (argv[i] == string("-seed")) {
      if (i+1 < argc) {
        int n;
        string s = argv[i+1];
        istringstream iss{s};
        if (iss >> n) {
          seed = n;
          cout << "Seed set to " << seed << endl;
        }
        ++i;
      }
    } else if (argv[i] == string("-scriptfile")) {
      if (i+1 < argc) {
        scriptFile = argv[i+1];
        cout << "Script file set to " << scriptFile << endl;
        ++i;
      }
    } else if (argv[i] == std::string("-startlevel")) {
      if (i+1 < argc) {
        startLevel = argv[i+1];
        cout << "Start level set to " << startLevel << endl;
        ++i;
      }
    }
  }
  if (startLevel == "0") {
    grid.init(LevelType::Level0, seed, false, scriptFile);
  } else if (startLevel == "1") {
    grid.init(LevelType::Level1, seed);
  } else if (startLevel == "2") {
    grid.init(LevelType::Level2, seed);
  } else if (startLevel == "3") {
    grid.init(LevelType::Level3, seed);
  } else if (startLevel == "4") {
    grid.init(LevelType::Level4, seed);
  } else {  // if no startlevel option is supplied, start at Level 0
    grid.init(LevelType::Level0, seed, false, scriptFile);
  }
  cout << grid << endl;
  graphDis->redraw(grid.getGameState());

  //COMMAND INTERPRETER
  try {
      string str[13] = {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence", "restart", "hint"};
    while (true) {
      if (isSequence && seqFirstTime) {
	seqFirstTime = false;
	fileStream = ifstream{fileName};
	if (!(fileStream >> cmd)) {
	  isSequence = false;
	  cout << grid;
    graphDis->redraw(grid.getGameState());
	  cout << "End of sequence file. Start providing input." << endl;
	  continue;
	}
      }
      else if (isSequence) {
	if (!(fileStream >> cmd)) {
	  isSequence = false;
	  cout << grid;
    graphDis->redraw(grid.getGameState());
          cout << "End of sequence file. Start providing input." << endl;
	  continue;
	}
      }
      else {
        cin >> cmd;
      }

      if (cmd == "I") {
	grid.setBlock(BlockType::IBlock);
	cout << grid;
  graphDis->redraw(grid.getGameState());
	continue;
      }
      else if (cmd == "J") {
	grid.setBlock(BlockType::JBlock);
	cout << grid;
  graphDis->redraw(grid.getGameState());
	continue;
      }
      else if (cmd == "L") {
	grid.setBlock(BlockType::LBlock);
	cout << grid;
  graphDis->redraw(grid.getGameState());
	continue;
      }
      else if (cmd == "O") {
        grid.setBlock(BlockType::OBlock);
	cout << grid;
  graphDis->redraw(grid.getGameState());
	continue;
      }
      else if (cmd == "S") {
        grid.setBlock(BlockType::SBlock);
	cout << grid;
  graphDis->redraw(grid.getGameState());
	continue;
      }
      else if (cmd == "Z") {
        grid.setBlock(BlockType::ZBlock);
	cout << grid;
  graphDis->redraw(grid.getGameState());
	continue;
      }
      else if (cmd == "T") {
        grid.setBlock(BlockType::TBlock);
	cout << grid;
  graphDis->redraw(grid.getGameState());
	continue;
      }
      
      //////////// New feature: Renaming commands //////////////
      string newCmdName;
      if (cmd == "rename") {
         cin >> cmd;
	 cin >> newCmdName;
         int index;
         if (cmd == "left") index  = 0;
         else if (cmd == "right") index = 1;
         else if (cmd == "down") index = 2;
         else if (cmd == "clockwise") index = 3;
         else if (cmd == "counterclockwise") index = 4;
         else if (cmd == "drop") index = 5;
         else if (cmd == "levelup") index = 6;
         else if (cmd == "leveldown") index = 7;
         else if (cmd == "norandom") index = 8;
         else if (cmd == "random") index = 9;
         else if (cmd == "sequence") index = 10;
         else if (cmd == "restart") index = 11;
         else if (cmd == "hint") index = 12;
         else {
            cout << "Invalid rename. Try again." << endl;
            continue;
         }
         allCmds.at(index).emplace_back(newCmdName);
	 cout << grid;
   graphDis->redraw(grid.getGameState());
         continue;
      }
      // first search if cmd is in allCmds
      for (unsigned int i = 0; i < allCmds.size(); ++i) {
         auto s = find(allCmds.at(i).begin(), allCmds.at(i).end(), cmd);
         if (s != allCmds.at(i).end()) { // found cmd in allCmds
            if (i == 0) grid.left(1);
	    else if (i == 1) grid.right(1);
            else if (i == 2) grid.down(1);
            else if (i == 3) grid.clockwise(1);
            else if (i == 4) grid.counterClockwise(1);
            else if (i == 5) grid.drop(1);
            else if (i == 6) grid.levelUp(1);
            else if (i == 7) grid.levelDown(1);
            else if (i == 8) {
	      string file;
              if (cin >> file) {
                grid.random(false, file);
              }
	    }
            else if (i == 9) grid.random(true);
            else if (i == 10) {
              string file;
              if (cin >> file) {
                grid.random(false, file);
              }
	    }
            else if (i == 11) {}
            else { grid.hint(); }
	    cout << grid;
      graphDis->redraw(grid.getGameState());
         }
      }
      //////////////////////////////////////////////////////////


      // pass in file assuming it is valid
      // handle if file does not exist case in Level and Grid
      istringstream iss{cmd};
      
      int n;
      if (!(iss >> n)) n = 1;
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

      //cout << newcmd << endl;

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
            grid.random(false, file);
          }
      } else if (newcmd == "random") {
	      grid.random(true);
      } else if (newcmd == "sequence") {
          if (cin >> fileName) {
	    seqFirstTime = true;
            isSequence = true;
          }
      } else if (newcmd == "restart") {
          grid.init(LevelType::Level0, seed, false, scriptFile);
      } else if (newcmd == "hint") {
        grid.hint();
      }

      cout << grid;
      graphDis->redraw(grid.getGameState());
    }
  } catch (ios::failure &) {}

}
