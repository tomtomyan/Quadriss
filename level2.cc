#include "level2.h"
#include "info.h"
using namespace std;

Level2::Level2(int seed):
        Level{LevelType::Level2, false, true, seed} {}

void Level2::setIsRandom(bool isRandom, string fileName) {}

shared_ptr<Block> Level2::generateBlock(BlockType type) {
  if(type == BlockType::None){
    int randNum = rand() % 7 + 1;
    if (randNum == 1) type = BlockType::SBlock;
    else if (randNum == 2) type = BlockType::ZBlock;
    else if (randNum == 3) type = BlockType::IBlock;
    else if (randNum == 4) type = BlockType::JBlock;
    else if (randNum == 5) type = BlockType::LBlock;
    else if (randNum == 6) type = BlockType::OBlock;
    else if (randNum == 7) type = BlockType::TBlock;
  }
  return makeBlock(type, LevelType::Level2);
}

shared_ptr<Block> Level2::obstacle(pair<int,int> &) {
	return nullptr;
}
