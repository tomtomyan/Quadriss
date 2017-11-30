#include "grid.h"

Grid::~Grid() {
  theGrid.clear();
}

void Grid::checkRows() {
  std::vector<std::pair<int, int>> c = currentBlock->getCoordinates(currentLeftBottom);
  vector<int> rows;
  for (int i = 0; i < c.size(); i++) {
    bool clear = true;
    for(int x = 0; x < theGrid.size(); x++) {
      if (theGrid[x][c[i].second].block == nullptr) {
        clear = false;
        break;
      }
    }
    if (clear) {
      for (int x = 0; x < theGrid.size(); x++) {
        theGrid[x][c[i].second].deleteCell();
      }
      //shift everything down
    }
  }

}

void Grid::placeLowest() {
  std::pair<int, int> newLeftBottom = currentLeftBottom;
  while (true) {
    newLeftBottom.second--;
    std::vector<std::pair<int, int>> c = currentBlock->getCoordinates(newLeftBottom);
    if (!checkValid(c)) {
      currentLeftBottom.second = newLeftBottom.second++;
      break;
    }
  }
  //attach new cells
}

bool Grid::checkValid(std::vector<pair<int, int>> coordinates) {
  for (int i = 0; coordinates.size(); i++) {
    if (theGrid[coordinates[i].first][coordinates[i].second]) return false;
  }
  return true;
}

void Grid::addScore(LevelType level, int numCells) {
  if (level = LevelType::level1) {

  }

  if (score > highScore) highScore = score;
}

void Grid::left() {
  std::pair<int, int> newLeftBottom = currentLeftBottom;
  newLeftBottom.first--;
  std::vector<std::pair<int, int>> c = currentBlock->getCoordinates(newLeftBottom);
  if (checkValid(c)) {
    currentLeftBottom.first--;
  }
}

void Grid::right() {
  std::pair<int, int> newLeftBottom = currentLeftBottom;
  newLeftBottom.first++;
  std::vector<std::pair<int, int>> c = currentBlock->getCoordinates(newLeftBottom);
  if (checkValid(c)) {
    currentLeftBottom.first++;
  }
}

void Grid::down() {
  std::pair<int, int> newLeftBottom = currentLeftBottom;
  newLeftBottom.second++;
  std::pair<int, int> c = currentBlock->getCoordinates(newLeftBottom);
  if (checkValid(c)) {
    currentLeftBottom.second++;
  } 
}

void Grid::clockwise() {
  std::vector<std::pair<int, int>> c = currentBlock->rotate(true, currentLeftBottom);
  if (checkValid(c)) {
    //rotate the block clockwise
  }
}

void Grid::counterClockwise() {
  std::vector<std::pair<int, int>> c = currentBlock->rotate(false, currentLeftBottom);
  if (checkValid(c)) {
    //rotate the block counterclockwise
  }
}

void Grid::drop() {
  placeLowest();
  checkRows();
  std::unique_ptr<Block> o = level.obstacle(currentBlock);
  if (o) {
    currentBlock = o;
    placeLowest();
    checkRows();
  }
  currentBlock = nextBlock;
  nextBlock = level.generateBlock();
}

void Grid::levelUp() {
  if (
}

void Grid::levelDown() {

}

void Grid::random(bool isRandom, string fileName = string.empty) {}

void Grid::setBlock(BlockType type) {

}

void Grid::init(LevelType level, bool isRandom = true, string fileName = string.empty) {

}

void Grid::hint() {

}

void Grid::attachObserver(Observer ob) {

}

void Grid::detachObserver(Observer ob) {

}

std::ostream &operator<<(std::ostream &out, const Grid &g) {

}
