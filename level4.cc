#include "level4.h"
/*
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
*/
#include "invalidfileexcept.h"
#include "invalidshapeexcept.h"
#include <fstream>
using namespace std;


Level4::Level4(string fileName):
        Level{LevelType::Level4, true, true}, fileStream{ifstream{fileName}} {}


void Level4::setIsRandom(bool isRandom) {
        if ((isRandom == false) && !(fileStream.is_open())) {
                throw InvalidFile{};
        }
	this->isRandom = isRandom;
}


void Level4::setFileName(string fileName) {
	this->fileName = fileName;
}

/*
void setFileStream(ifstream &fileStream) {
	this->fileStream = fileStream;
}
*/

shared_ptr<Block> Level4::generateBlock(BlockType type) {
	/*
	if (!(getFileStream().is_open())) {
		throw InvalidFile{};
	}
	*/
  if (type == BlockType::None && getIsRandom() == false) {
    string input;  // input is type of Blocks
    if (fileStream >> input) {
      type = inputInterpreter(input);
    }
  }
  else if (type == BlockType::None) {
    int randNum = rand() % 81 + 1;  // 1-81
    if ((1 <= randNum) && (randNum <= 18)) type = BlockType::SBlock;
    else if ((19 <= randNum) && (randNum <= 36)) type = BlockType::ZBlock;
    else if ((37 <= randNum) && (randNum <= 45)) type = BlockType::IBlock;
    else if ((46 <= randNum) && (randNum <= 54)) type = BlockType::JBlock;
    else if ((55 <= randNum) && (randNum <= 63)) type = BlockType::LBlock;
    else if ((64 <= randNum) && (randNum <= 72)) type = BlockType::OBlock;
    else if ((73 <= randNum) && (randNum <= 81)) type = BlockType::TBlock;
    else {
      //throw something???
    }
	}
  return makeBlock(type, LevelType::Level4);
}


shared_ptr<Block> Level4::obstacle(pair<int,int> &leftBottom) {
	int leftBottomRow = leftBottom.second; // y-value
	leftBottom = make_pair(5, leftBottomRow);
	return makeBlock(BlockType::OneCellBlock, LevelType::Level4, DisplayFormat::Obstacle);
}
