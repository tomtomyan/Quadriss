#ifndef LEVEL_H
#define LEVEL_H
#include <fstream>

class Level {
	LevelType level;
	bool isHeavy;
	bool isRandom;
	string fileName;
	ifstream &fileStream; // NEW - cannot be ifstream fileStream (can't copy ifstreams)
	
	public:
	Level(LevelType, bool, bool);
	LevelType getLevel();
	bool getIsHeavy();
	virtual void setIsRandom(bool) = 0;
	bool getIsRandom();
	virtual void setFileName(string) = 0;
	string getFileName();
	virtual void setFileStream(ifstream &) = 0; // NEW
	ifstream &getFileStream();  // NEW
	shared_ptr<Block>generateBlock() = 0;
	shared_ptr<Block>obstacle(Pair<int,int> &) = 0;
};

#endif
