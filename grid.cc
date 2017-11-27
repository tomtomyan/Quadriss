#include "grid.h"

Grid::~Grid() {
  theGrid.clear();
}

void Grid::checkRows() {

}

void Grid::placeLowest() {

}

bool Grid::checkValid(std::vector<pair<int, int>> coordinates) {

}

void Grid::addScore() {}

void Grid::left() {}

void Grid::right() {}

void Grid::down() {}

void Grid::clockwise() {}

void Grid::counterClockwise() {}

void Grid::drop() {}

void Grid::levelUp() {}

void Grid::levelDown() {}

void Grid::random(bool isRandom, string fileName = string.empty) {}

void Grid::setBlock(BlockType type) {}

void Grid::init(LevelType level, bool isRandom = true, string fileName = string.empty) {}

void Grid::hint() {}

void Grid::attachObserver(Observer ob);

void Grid::detachObserver(Observer ob);

std::ostream &operator<<(std::ostream &out, const Grid &g) {}
