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
	
  BlockType inputInterpreter(std::string input);

	public:
  virtual ~Level();
	Level(LevelType level, bool isHeavy, bool isRandom, int seed, std::string fileName = "");
	LevelType getLevel();
	bool getIsHeavy();
	virtual void setIsRandom(bool, std::string) = 0;
	bool getIsRandom();
	int getSeed();	
  std::shared_ptr<Block> makeBlock(BlockType type, LevelType level, DisplayFormat format = DisplayFormat::Standard);
	virtual std::shared_ptr<Block> generateBlock(BlockType type = BlockType::None) = 0;
	virtual std::shared_ptr<Block> obstacle(std::pair<int,int> &) = 0;
};

#endif
