#include "iostream"

#include "grid.h"

using namespace std;

Grid::~Grid() {
  theGrid.clear();
}

void Grid::detach(vector<pair<int, int>> &v) {
  for (size_t i = 0; i < v.size(); i++) {
    currentBlock->notifyAttachDetach(false, theGrid[v[i].second][v[i].first], v[i]);
  }
}

void Grid::attach(vector<pair<int, int>> &v) {
  for (size_t i = 0; i < v.size(); i++) {
    currentBlock->notifyAttachDetach(true, theGrid[v[i].second][v[i].first], v[i]);
  }
}

void Grid::checkRows() {
  vector<pair<int, int>> c = currentBlock->getCoordinates(currentLeftBottom);
  int size = c.size();
  vector<int> rowsDeleted;
  for (size_t i = 0; i < size; i++) {
    int y = c[i].second;
    bool clear = true;
    for(size_t x = 0; x < width; x++) {
      if (theGrid[y][x]->getInfo().type == BlockType::None) {
        clear = false;
        break;
      }
    }
    if (clear) {
      rowsDeleted.emplace_back(y);
      for (size_t x = 0; x < width; x++) {
        LevelType deletedCellLevel = theGrid[y][x]->deleteCell(make_pair(x, y));
	if(deletedCellLevel != LevelType::None){
	  addScore(false, deletedCellLevel, 0);
	}
      }
    }
  }

  // We need to sort the list of deleted row. This way, we can delete the top
  // rows first and not shift the positions of the rows below it.
  vector<int> sortedDeleted;
  while(rowsDeleted.size() > 0){
    int lenRD = rowsDeleted.size();
    int min = rowsDeleted.at(0);
    int posMin = 0;
    for(int i=1; i<lenRD; i++){
      int cur = rowsDeleted.at(i);
      if(cur<min){
        min = cur;
	posMin = i;
      }
    }
    sortedDeleted.emplace_back(min);
    rowsDeleted.erase(rowsDeleted.begin()+posMin);
  }
  
  int numDeleted = sortedDeleted.size();
  for(int i=0; i<numDeleted; i++){
    theGrid.erase(theGrid.begin()+(sortedDeleted.at(i)));
    vector<shared_ptr<Cell>> row;
    for(int j=0; j<width; j++){
      row.emplace_back(make_shared<Cell>());
    }
    theGrid.insert(theGrid.begin(), row);
  }

  addScore(true, theLevel->getLevel(), numDeleted);
}

void Grid::placeLowest() {
  pair<int, int> newLeftBottom = currentLeftBottom;
  vector<pair<int, int>> old = currentBlock->getCoordinates(currentLeftBottom);
  detach(old);
  while (true) {
    newLeftBottom.second++;
    vector<pair<int, int>> c = currentBlock->getCoordinates(newLeftBottom);
    if (!checkValid(c)) {
      newLeftBottom.second--;
      break;
    }
  }

  vector<pair<int, int>> current = currentBlock->getCoordinates(newLeftBottom);
  attach(current);
}

bool Grid::checkValid(vector<pair<int, int>> coords) {
  for (int i = 0; i < coords.size(); i++) {
    if(coords.at(i).second<0 || coords.at(i).second>=height || coords.at(i).first<0 || coords.at(i).first>=width) return false;
    if (theGrid[coords[i].second][coords[i].first]->getInfo().type != BlockType::None) return false;
  }
  return true;
}

void Grid::addScore(bool isLine, LevelType level, int numLines) {
  if(level == LevelType::None || (isLine && numLines==0)) return;
  
  int levelScore = 0;
  if (level == LevelType::Level1) {
    levelScore = 1;
  } else if (level == LevelType::Level2) {
    levelScore = 2;
  } else if (level == LevelType::Level3) {
    levelScore = 3;
  } else if (level == LevelType::Level4) {
    levelScore = 4;
  }

  if(isLine){
    int base = levelScore + numLines;
    score += (base * base);
  }
  else{
    int base = levelScore + 1;
    score += (base * base);
  }

  if (score > highScore) highScore = score;
}

void Grid::left(int n) {
  for (int i = 0; i < n; i++) {
    pair<int, int> newLeftBottom = make_pair(currentLeftBottom.first-1, currentLeftBottom.second);
    vector<pair<int, int>> old = currentBlock->getCoordinates(currentLeftBottom);
    vector<pair<int, int>> current = currentBlock->getCoordinates(newLeftBottom);
    detach(old);
    if (checkValid(current)) {
      attach(current);
      currentLeftBottom.first--;
    } else {
      attach(old);
    }
  }
  if(theLevel->getIsHeavy()) down(1);
}

void Grid::right(int n) {
  for (int i = 0; i < n; i++) {
    pair<int, int> newLeftBottom = make_pair(currentLeftBottom.first+1, currentLeftBottom.second);
    vector<pair<int, int>> old = currentBlock->getCoordinates(currentLeftBottom);
    vector<pair<int, int>> current = currentBlock->getCoordinates(newLeftBottom);
    detach(old);
    if (checkValid(current)) {
      attach(current);
      currentLeftBottom.first++;
    } else {
      attach(old);
    }
  }
  if(theLevel->getIsHeavy()) down(1);
}

void Grid::down(int n) {
  for (int i = 0; i < n; i++) {
    pair<int, int> newLeftBottom = make_pair(currentLeftBottom.first, currentLeftBottom.second+1);
    vector<pair<int, int>> old = currentBlock->getCoordinates(currentLeftBottom);
    vector<pair<int, int>> current = currentBlock->getCoordinates(newLeftBottom);
    detach(old);
    if (checkValid(current)) {
      attach(current);
      currentLeftBottom.second++;
    } else {
      attach(old);
    }
  }
  if(theLevel->getIsHeavy()) down(1);
}

void Grid::clockwise(int n) {
  for (int i = 0; i < n; i++) {
    vector<pair<int, int>> old = currentBlock->getCoordinates(currentLeftBottom);
    vector<pair<int, int>> current = currentBlock->getRotated(true, currentLeftBottom);
    detach(old);
    if (checkValid(current)) {
      currentBlock->rotate(true);
      attach(current);
    } else {
      attach(old);
    }
  }
  if(theLevel->getIsHeavy()) down(1);
}

void Grid::counterClockwise(int n) {
  for (int i = 0; i < n; i++) {
    vector<pair<int, int>> old = currentBlock->getCoordinates(currentLeftBottom);
    vector<pair<int, int>> current = currentBlock->getRotated(false, currentLeftBottom);
    detach(old);
    if (checkValid(current)) {
      currentBlock->rotate(false);
      attach(current);
    } else {
      attach(old);
    }
  }
  if(theLevel->getIsHeavy()) down(1);
}

void Grid::drop(int n) {
  placeLowest();
  checkRows();
  shared_ptr<Block> o = theLevel->obstacle(currentLeftBottom);//change this
  if (o) {
    cout << "obstacle found" << endl;
    currentBlock = o;
    placeLowest();
    checkRows();
  }
  currentBlock = nextBlock;
  nextBlock = theLevel->generateBlock();

  currentLeftBottom.first = 0;
  currentLeftBottom.second = 3;
  vector<pair<int, int>> current = currentBlock->getCoordinates(currentLeftBottom);
  if (checkValid(current)) attach(current); //else game is over
}

void Grid::setLevel(LevelType level){
  if (level == LevelType::Level0) {
    theLevel = make_unique<Level0>("sequence.txt"); 
  } else if (level == LevelType::Level1){
    theLevel = make_unique<Level1>();
  } else if (level == LevelType::Level2) {
    theLevel = make_unique<Level2>();
  } else if (level == LevelType::Level3) {
    theLevel = make_unique<Level3>();
  } else if (level == LevelType::Level4) {
    theLevel = make_unique<Level4>();
  }
}

void Grid::levelUp(int n) {
  LevelType level = LevelType::None;
  if (theLevel->getLevel() == LevelType::Level0) {
    level = LevelType::Level1;
  } else if (theLevel->getLevel() == LevelType::Level1) {
    level = LevelType::Level2;
  } else if (theLevel->getLevel() == LevelType::Level2) {
    level = LevelType::Level3;
  } else if (theLevel->getLevel() == LevelType::Level3) {
    level = LevelType::Level4;
  }
  setLevel(level);
}

void Grid::levelDown(int n) {
  LevelType level = LevelType::None;
  if (theLevel->getLevel() == LevelType::Level0) {
    level = LevelType::Level4;
  } else if (theLevel->getLevel() == LevelType::Level1) {
    level = LevelType::Level0;
  } else if (theLevel->getLevel() == LevelType::Level2) {
    level = LevelType::Level1;
  } else if (theLevel->getLevel() == LevelType::Level3) {
    level = LevelType::Level2;
  }
  setLevel(level);
}

void Grid::random(bool isRandom, string fileName) {
  theLevel->setIsRandom(isRandom);
  if(!isRandom) theLevel->setFileName(fileName);
}

void Grid::setBlock(BlockType type) {
  vector<pair<int, int>> old = currentBlock->getCoordinates(currentLeftBottom);
  detach(old);
  currentBlock = theLevel->generateBlock(type); 
  vector<pair<int, int>> cur = currentBlock->getCoordinates(currentLeftBottom);
  if (!checkValid(cur)) {
    currentLeftBottom = make_pair(0, 3);
    cur = currentBlock->getCoordinates(currentLeftBottom);
  }
  attach(cur);
}

void Grid::init(LevelType level, bool isRandom, string fileName) {
  theGrid.clear();
  for (int y = 0; y < height; y++) {
    vector<shared_ptr<Cell>> row;
    for (int x = 0; x < width; x++) {
      row.emplace_back(make_shared<Cell>());
    }
    theGrid.emplace_back(row);
  }
  
  setLevel(level);
  theLevel->setIsRandom(isRandom);
  theLevel->setFileName(fileName);
  currentLeftBottom = make_pair(0,3);
  currentBlock = theLevel->generateBlock();

  vector<pair<int, int>> coords = currentBlock->getCoordinates(currentLeftBottom);
  attach(coords);
  nextBlock = theLevel->generateBlock();
}

void Grid::hint() {
  for (int i = 0; i < 8; i++) {

  }
}

void Grid::attachObserver(shared_ptr<Observer<Info, State>> ob) {
  this->ob.emplace_back(ob);
}

void Grid::detachObserver(shared_ptr<Observer<Info, State>> ob) {
  for (auto it = this->ob.begin(); it != this->ob.end(); ++it) {
    if (&(*it) == &ob) {
      this->ob.erase(it);
    }
  }
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
  out << "Level:      ";
  if (g.theLevel->getLevel() == LevelType::Level0) {
    out << 0;
  } else if (g.theLevel->getLevel() == LevelType::Level1) {
    out << 1;
  } else if (g.theLevel->getLevel() == LevelType::Level2) {
    out << 2;
  } else if (g.theLevel->getLevel() == LevelType::Level3) {
    out << 3;
  } else if (g.theLevel->getLevel() == LevelType::Level4) {
    out << 4;
  }
  out << endl;
  out << "Score:      " << g.score << endl;
  out << "Hi Score: " << g.highScore << endl;
  out << "-----------" << endl;
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 11; j++) {
      if (g.theGrid[i][j]->getInfo().type == BlockType::IBlock) {
        out << "I";
      } else if (g.theGrid[i][j]->getInfo().type == BlockType::JBlock) {
        out << "J";
      } else if (g.theGrid[i][j]->getInfo().type == BlockType::LBlock) {
        out << "L";
      } else if (g.theGrid[i][j]->getInfo().type == BlockType::OBlock) {
        out << "O";
      } else if (g.theGrid[i][j]->getInfo().type == BlockType::SBlock) {
        out << "S";
      } else if (g.theGrid[i][j]->getInfo().type == BlockType::ZBlock) {
        out << "Z";
      } else if (g.theGrid[i][j]->getInfo().type == BlockType::TBlock) {
        out << "T";
      } else if (g.theGrid[i][j]->getInfo().type == BlockType::OneCellBlock) {
        out << "o";
      }  else {
        out << " ";
      }
    }
    out << endl;
  }
  out << "-----------" << endl;
  out << "Next:" << endl;
  //print next block
  if (g.nextBlock->getInfo().type == BlockType::IBlock) {
    out << "IIII" << endl;
  } else if (g.nextBlock->getInfo().type == BlockType::JBlock) {
    out << "J" << endl << "JJJ" << endl;
  } else if (g.nextBlock->getInfo().type == BlockType::LBlock) {
    out << "  L" << endl << "LLL" << endl;
  } else if (g.nextBlock->getInfo().type == BlockType::OBlock) {
    out << "OO" << endl << "OO" << endl;
  } else if (g.nextBlock->getInfo().type == BlockType::SBlock) {
    out << " SS" << endl << "SS" << endl;
  } else if (g.nextBlock->getInfo().type == BlockType::ZBlock) {
    out << "ZZ" << endl << " ZZ" << endl;
  } else if (g.nextBlock->getInfo().type == BlockType::TBlock) {
    out << "TTT" << endl << " T" << endl;
  }
  
  return out;
}
