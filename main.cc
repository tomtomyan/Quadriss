#include <iostream>
#include <string>

#include "grid.h"

using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;

  shared_ptr<Level> curLevel = nullptr;
  string startLevel = argv[__]; /////insert index of startlevel cmd arg
  if (startLevel == "0") {
    curLevel = make_shared<Level0>();
  }
  else if (startLevel == "1") {
    curLevel = make_shared<Level1>();
  }
  else if (startLevel == "2") {
    curLevel = make_shared<Level2>();
  }
  else if (startLevel == "3") {
    curLevel = make_shared<Level3>();
  }
  else if (startLevel == "4") {
    curLevel = make_shared<Level4>();
  }
  else {  // if no startlevel option is supplied, start at Level 0
    curLevel = make_shared<Level0>();
  }
  while (true) {
    shared_ptr<Block> curBlock = curLevel->generateBlock();/////
  }

  try {
    while (true) {
      cin >> cmd;
      if (cmd == "left") {

      } else if (cmd == "right") {

      } else if (cmd == "down") {

      } else if (cmd == "clockwise") {

      } else if (cmd == "counterclockwise") {

      } else if (cmd == "drop") {

      } else if (cmd == "levelup") {

      } else if (cmd == "leveldown") {

      } else if (cmd == "norandom") {

      } else if (cmd == "random") {

      } else if (cmd == "sequence") {

      } else if (cmd == "restart") {

      } else if (cmd == "hint") {

      } 


    }
  } catch (ios::failure &) {}

}
