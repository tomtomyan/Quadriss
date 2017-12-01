#include "grid.h"

using namespace std;

Grid::~Grid() {
  theGrid.clear();
}

void Grid::checkRows() {
  vector<pair<int, int>> c = currentBlock->getCoordinates(currentLeftBottom);
  for (size_t i = 0; i < c.size(); i++) {
    bool clear = true;
    for(size_t x = 0; x < theGrid.size(); x++) {
      if (theGrid[x][c[i].second].getInfo().type == BlockType::None) {
        clear = false;
        break;
      }
    }
    if (clear) {
      for (size_t x = 0; x < theGrid.size(); x++) {
        theGrid[x][c[i].second].deleteCell();
      }
      //shift everything down
      
    }
  }

}

void Grid::placeLowest() {
  pair<int, int> newLeftBottom = currentLeftBottom;
  while (true) {
    newLeftBottom.second--;
    vector<pair<int, int>> c = currentBlock->getCoordinates(newLeftBottom);
    if (!checkValid(c)) {
      newLeftBottom.second++;
      break;
    }
  }
  //detach old cells and attach new cells
  vector<pair<int, int>> o = currentBlock->getCoordinates(currentLeftBottom);
  vector<pair<int, int>> c = currentBlock->getCoordinates(newLeftBottom);
  for (int i = 0; i < o.size(); i++) {
    notifyAttachDetach(false, theGrid[o[i].first][o[i].second], o[i]);
  }
  for (int i = 0; i < c.size(); i++) {
    notifyAttachDetach(true, theGrid[c[i].first][c[i].second], c[i]);
  }
}

bool Grid::checkValid(vector<pair<int, int>> coordinates) {
  for (int i = 0; coordinates.size(); i++) {
    if (theGrid[coordinates[i].first][coordinates[i].second]) return false;
  }
  return true;
}

void Grid::addScore(LevelType level, int numCells) {
  if (level == LevelType::Level1) {
    //score += 
  } else if (level == LevelType::Level2) {
    //score += 
  } else if (level == LevelType::Level3) {
    //score +=
  } else if (level == LevelType::Level4) {
    //score +=
  }

  if (score > highScore) highScore = score;
}

void Grid::left() {
  pair<int, int> newLeftBottom = currentLeftBottom;
  newLeftBottom.first--;
  vector<pair<int, int>> c = currentBlock->getCoordinates(newLeftBottom);
  if (checkValid(c)) {
    currentLeftBottom.first--;
  }
}

void Grid::right() {
  pair<int, int> newLeftBottom = currentLeftBottom;
  newLeftBottom.first++;
  vector<pair<int, int>> c = currentBlock->getCoordinates(newLeftBottom);
  if (checkValid(c)) {
    currentLeftBottom.first++;
  }
}

void Grid::down() {
  pair<int, int> newLeftBottom = currentLeftBottom;
  newLeftBottom.second++;
  vector<pair<int, int>> c = currentBlock->getCoordinates(newLeftBottom);
  if (checkValid(c)) {
    currentLeftBottom.second++;
  } 
}

void Grid::clockwise() {
  vector<pair<int, int>> c = currentBlock->rotate(true, currentLeftBottom);
  vector<pair<int, int>> o = currentBlock->getCoordinates(currentLeftBottom);
  if (checkValid(c)) {
    //rotate the block clockwise
    for (int i = 0; i < o.size(); i++) {
      notifyAttachDetach(false, theGrid[o[i].first][o[i].second], o[i]);
    }
    for (int i = 0; i < c.size(); i++) {
      notifyAttachDetach(true, theGrid[c[i].first][c[i].second], c[i]);
    }
  }
}

void Grid::counterClockwise() {
  vector<pair<int, int>> c = currentBlock->rotate(false, currentLeftBottom);
  vector<pair<int, int>> o = currentBlock->getCoordinates(currentLeftBottom);
  if (checkValid(c)) {
    //rotate the block counterclockwise
    for (int i = 0; i < o.size(); i++) {
      notifyAttachDetach(false, theGrid[o[i].first][o[i].second], o[i]);
    }
    for (int i = 0; i < c.size(); i++) {
      notifyAttachDetach(true, theGrid[c[i].first][c[i].second], c[i]);
    }
  }
}

void Grid::drop() {
  placeLowest();
  checkRows();
  unique_ptr<Block> o = level.obstacle(currentBlock);
  if (o) {
    currentBlock = o;
    placeLowest();
    checkRows();
  }
  currentBlock = nextBlock;
  nextBlock = level.generateBlock();
}

void Grid::levelUp() {
  if (theLevel.level == LevelType::None) {
    theLevel = make_unique<Level1>();
  } else if (theLevel.level == LevelType::Level1) {
    theLevel = make_unique<Level2>();
  } else if (theLevel.level == LevelType::Level2) {
    theLevel = make_unique<Level3>();
  } else if (theLevel.level == LevelType::Level3) {
    theLevel = make_unique<Level4>();
  }
}

void Grid::levelDown() {
  if (theLevel.level == LevelType::Level4) {
    theLevel = Level3();
  } else if (theLevel.level == LevelType::Level3) {
    theLevel = Level2();
  } else if (theLevel.level == LevelType::Level2) {
    theLevel = Level1();
  } else if (theLevel.level == LevelType::Level1) {
    theLevel = Level0();
  }
}

void Grid::random(bool isRandom, string fileName = string.empty) {
  
}

void Grid::setBlock(BlockType type) {
  
}

void Grid::init(LevelType level, bool isRandom = true, string fileName = string.empty) {
  theGrid.clear();
  
  theGrid.resize(15);
  for (int i = 0; i < 15; i++) {
    for (int j = 0; i < 11; j++) {
      theGrid[i].emplace_back(Cell(i, j));
    }
  }

}

void Grid::hint() {

}

void Grid::attachObserver(shared_ptr<Observer<Info, State>> ob) {
  this->ob.emplace_back(ob);
}

void Grid::detachObserver(shared_ptr<Observer<Info, State>> ob) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == *o) {
      observers.erase(it);
    }
  }
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
  out << "Level:      " << g.level << endl;
  out << "Score:      " << g.score << endl;
  out << "Hi Score: " << g.highScore << endl;
  out << "-----------" << endl;
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 11; j++) {
      if (theGrid[i][j].block) {
        if (theGrid[i][j].getInfo().type == BlockType::IBlock) {
          out << "I";
        } else if (theGrid[i][j].getInfo().type == BlockType::JBlock) {
          out << "J";
        } else if (theGrid[i][j].getInfo().type == BlockType::LBlock) {
          out << "L";
        } else if (theGrid[i][j].getInfo().type == BlockType::OBlock) {
          out << "O";
        } else if (theGrid[i][j].getInfo().type == BlockType::SBlock) {
          out << "S";
        } else if (theGrid[i][j].getInfo().type == BlockType::ZBlock) {
          out << "Z";
        } else if (theGrid[i][j].getInfo().type == BlockType::TBlock) {
          out << "T";
        } else if (theGrid[i][j].getInfo().type == BlockType::OneCell) {
          out << "o";
        }
      } else {
        out << " ";
      }
    }
    out << endl;
  }
  out << "-----------" << endl;
  out << "Next:" << endl;
  //print next block
  //if (nextBlock.getInfo().type == BlockType::J
}
