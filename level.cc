#include "level.h"


Level::Level(LevelType level, bool isHeavy, bool isRandom):
	level{level}, isHeavy{isHeavy}, isRandom{isRandom} {}


LevelType getLevel() {
	return level;
}


bool getIsHeavy() {
	return isHeavy;
}


bool getIsRandom() {
	return isRandom;
}


string getFileName() {
	return fileName;
}


ifstream &getFileStream() {
	return fileStream;
}
