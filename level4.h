#ifndef LEVEL4_H
#define LEVEL4_H
#include <fstream>
#include <memory>
#include "level.h"
class Block;

class Level4 : public Level {
	std::ifstream fileStream;
  int numDrops = 0;
  public:
	Level4(int seed, std::string fileName = "");
  void setIsRandom(bool isRandom, std::string fileName = "") override;
  std::shared_ptr<Block> generateBlock(BlockType type = BlockType::None) override;
  std::shared_ptr<Block> obstacle(std::pair<int,int> &) override;
};

#endif
