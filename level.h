#ifndef LEVEL_H
#define LEVEL_H
#include <fstream>
#include <memory>
#include "info.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "oneCellblock.h"
class Block;

class Level {
	LevelType level;
	bool isHeavy;
	
	protected:
	bool isRandom;
	std::string fileName;
	
	std::shared_ptr<Block> makeBlock(BlockType type, LevelType level, DisplayFormat format = DisplayFormat::Standard);
  BlockType inputInterpreter(std::string input);

	public:
	Level(LevelType, bool, bool);
	LevelType getLevel();
	bool getIsHeavy();
	virtual void setIsRandom(bool) = 0;
	bool getIsRandom();
	virtual void setFileName(std::string) = 0;
	std::string getFileName();
//	virtual void setFileStream(ifstream &) = 0; // NEW
	std::ifstream &getFileStream();  // NEW
	virtual std::shared_ptr<Block> generateBlock(BlockType type = BlockType::None) = 0;
	virtual std::shared_ptr<Block> obstacle(std::pair<int,int> &) = 0;
};

#endif
