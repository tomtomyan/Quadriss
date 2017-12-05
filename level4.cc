#include "level4.h"
#include "invalidfileexcept.h"
#include "invalidshapeexcept.h"
#include <fstream>
using namespace std;

Level4::Level4(int seed, string fileName):
        Level{LevelType::Level4, true, true, seed} {}

void Level4::setIsRandom(bool isRandom, string fileName) {
  if(fileName != "" ) this->fileName = fileName;
  if (isRandom == false) {
    fileStream = ifstream{this->fileName};
    if(!fileStream) throw InvalidFile();
  }
	this->isRandom = isRandom;
}

shared_ptr<Block> Level4::generateBlock(BlockType type) {
  if (type == BlockType::None && getIsRandom() == false) {
    string input;  // input is type of Blocks
    if (fileStream >> input) {
      type = inputInterpreter(input);
    }
    if(type == BlockType::None){
      cout << "End of file, switching to random generation" << endl;
    }
  }
 
  if (type == BlockType::None) {
    int randNum = rand() % 81 + 1;  // 1-81
    if ((1 <= randNum) && (randNum <= 18)) type = BlockType::SBlock;
    else if ((19 <= randNum) && (randNum <= 36)) type = BlockType::ZBlock;
    else if ((37 <= randNum) && (randNum <= 45)) type = BlockType::IBlock;
    else if ((46 <= randNum) && (randNum <= 54)) type = BlockType::JBlock;
    else if ((55 <= randNum) && (randNum <= 63)) type = BlockType::LBlock;
    else if ((64 <= randNum) && (randNum <= 72)) type = BlockType::OBlock;
    else if ((73 <= randNum) && (randNum <= 81)) type = BlockType::TBlock;
	}
  return makeBlock(type, LevelType::Level4);
}

shared_ptr<Block> Level4::obstacle(pair<int,int> &leftBottom) {
	leftBottom = make_pair(5, 3);
  numDrops++;
  if (numDrops % 5 == 0) return makeBlock(BlockType::OneCellBlock, LevelType::Level4, DisplayFormat::Obstacle);
  return nullptr;
}
