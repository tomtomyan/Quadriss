#ifndef LEVEL0_H
#define LEVEL0_H
#include <fstream>
#include <memory>
#include "level.h"
class Block;

class Level0 : public Level {
	std::ifstream fileStream;
	public:
	Level0(int seed, std::string fileName = "sequence.txt");
	void setIsRandom(bool isRandom, std::string fileName = "") override;
	std::shared_ptr<Block> generateBlock(BlockType type = BlockType::None) override;
	std::shared_ptr<Block> obstacle(std::pair<int,int> &) override;
};

#endif
