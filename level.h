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
	int seed;
	
	protected:
	bool isRandom;
	std::string fileName;
	
	std::shared_ptr<Block> makeBlock(BlockType type, LevelType level, DisplayFormat format = DisplayFormat::Standard);
  BlockType inputInterpreter(std::string input);

	public:
	Level(LevelType, bool, bool, int seed, std::string fileName = "");
	LevelType getLevel();
	bool getIsHeavy();
	virtual void setIsRandom(bool) = 0;
	bool getIsRandom();
	virtual void setFileName(std::string) = 0;
	std::string getFileName();
	std::ifstream &getFileStream();
	void setSeed(int seed);
	int getSeed();
	virtual std::shared_ptr<Block> generateBlock(BlockType type = BlockType::None) = 0;
	virtual std::shared_ptr<Block> obstacle(std::pair<int,int> &) = 0;
};

#endif
