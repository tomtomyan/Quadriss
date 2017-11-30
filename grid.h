#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <utility>

#include "block.h"
#include "cell.h"
//#include "textdisplay.h"

class Grid {
  std::vector<std::vector<Cell>> theGrid;
  std::unique_ptr<Level> theLevel;
  std::unique_ptr<Block> currentBlock;
  std::unique_ptr<Block> nextBlock;
  std::vector<Observer> ob;
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
  void random(bool isRandom, string fileName = string.empty);
  void setBlock(BlockType type);
  void init(LevelType level, bool isRandom = true, string fileName = string.empty);
  void hint();
  void attachObserver(Observer ob);
  void detachObserver(Observer ob);

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
