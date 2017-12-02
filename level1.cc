#include "level1.h"
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


Level1::Level1():
        Level{LevelType::Level1, false, true} {}


void Level1::setIsRandom(bool) {}


void Level1::setFileName(string fileName) {}


//void setFileStream(ifstream &fileStream) {}


// generate a random number between 1 and 84 inclusive
// if this number is:
// 1-7: S-Block
// 8-14: Z-Block
// 15-28: I
// 29-42: J
// 43-56: L
// 57-70: O
// 71-84: T
shared_ptr<Block> Level1::generateBlock(BlockType type) {
  if(type == BlockType::None){
    int randNum = rand() % 84 + 1;
    if ((1 <= randNum) && (randNum <= 7)) type = BlockType::SBlock;
    else if ((8 <= randNum) && (randNum <= 14)) type = BlockType::ZBlock;
    else if ((15 <= randNum) && (randNum <= 28)) type = BlockType::IBlock;
    else if ((29 <= randNum) && (randNum <= 42)) type = BlockType::JBlock;
    else if ((43 <= randNum) && (randNum <= 56)) type = BlockType::LBlock;
  	else if ((57 <= randNum) && (randNum <= 70)) type = BlockType::OBlock;
  	else if ((71 <= randNum) && (randNum <= 84)) type = BlockType::TBlock;
    else{
      //throw something
    }
  }
  return makeBlock(type, LevelType::Level1);
}


shared_ptr<Block> Level1::obstacle(pair<int,int> &) {
	return nullptr;
}
