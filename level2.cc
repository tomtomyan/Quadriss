#include "level2.h"
#include "info.h"
/*
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
*/
using namespace std;


Level2::Level2():
        Level{LevelType::Level2, false, true} {}


void Level2::setIsRandom(bool isRandom) {}


void Level2::setFileName(string fileName) {}


//void setFileStream(ifstream &fileStream) {}


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
    else{
      //throw something?
    }
  }
  return makeBlock(type, LevelType::Level2);
}


shared_ptr<Block> Level2::obstacle(pair<int,int> &) {
	return nullptr;
}
