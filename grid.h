#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <utility>

#include "block.h"
#include "cell.h"
#include "level.h"
#include "observer.h"
#include "info.h"
#include "state.h"

//#include "textdisplay.h"

class Grid {
  std::vector<std::vector<Cell>> theGrid;
  std::unique_ptr<Level> theLevel;
  std::unique_ptr<Block> currentBlock;
  std::unique_ptr<Block> nextBlock;
  std::vector<Observer<Info, State>> ob;
  std::pair<int, int> currentLeftBottom;

  int score;
  int highScore;
  
  void checkRows();
  void placeLowest();
  bool checkValid(std::vector<std::pair<int, int>> coordinates);

  public:
  ~Grid();

  void addScore(LevelType level, int numCells);
  void left();
  void right();
  void down();
  void clockwise();
  void counterClockwise();
  void drop();
  void levelUp();
  void levelDown();
  void random(bool isRandom, std::string fileName = "");
  void setBlock(BlockType type);
  void init(LevelType level, bool isRandom = true, std::string fileName = "");
  void hint();
  void attachObserver(std::shared_ptr<Observer<Info, State>> ob);
  void detachObserver(std::shared_ptr<Observer<Info, State>> ob);

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
