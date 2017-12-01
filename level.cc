#include "level.h"
using namespace std;

Level::Level(LevelType level, bool isHeavy, bool isRandom):
	level{level}, isHeavy{isHeavy}, isRandom{isRandom} {}


LevelType Level::getLevel() {
	return level;
}


bool Level::getIsHeavy() {
	return isHeavy;
}


bool Level::getIsRandom() {
	return isRandom;
}


string Level::getFileName() {
	return fileName;
}
