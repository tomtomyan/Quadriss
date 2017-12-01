#ifndef LEVEL_H
#define LEVEL_H
#include <fstream>
#include <memory>
#include "info.h"
class Block;

class Level {
	LevelType level;
	bool isHeavy;
	
	protected:
	bool isRandom;
	std::string fileName;
	
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
	virtual std::shared_ptr<Block> generateBlock() = 0;
	virtual std::shared_ptr<Block> obstacle(std::pair<int,int> &) = 0;
};

#endif
