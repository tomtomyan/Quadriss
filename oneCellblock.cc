#include "oneCellblock.h"
using namespace std;

OneCellBlock::OneCellBlock(LevelType level, DisplayFormat format) : Block{BlockType::OneCellBlock, level, format} {}

OneCellBlock::~OneCellBlock(){};

vector<pair<int, int>> OneCellBlock::baseGetCoordinates(int rotState, pair<int, int> leftBottom) const{
  vector<pair<int, int>> coords;
  if(rotState == 0 || rotState == 1 || rotState == 2 || rotState == 3){
    coords.emplace_back(make_pair(leftBottom.first, leftBottom.second));
  }
  return coords;
}

shared_ptr<Block> OneCellBlock::getThisPtr(){
  shared_ptr<OneCellBlock> now = shared_from_this();
  return dynamic_pointer_cast<Block>(now);
}

