#ifndef LEVEL3_H
#define LEVEL3_H
#include <fstream>
#include <memory>
#include "level.h"
class Block;

class Level3 : public Level {
	std::ifstream fileStream;
  public:
	Level3(int seed, std::string fileName = "");
  void setIsRandom(bool isRandom, std::string fileName = "") override;
  std::shared_ptr<Block> generateBlock(BlockType type = BlockType::None) override;
  std::shared_ptr<Block> obstacle(std::pair<int,int> &) override;
};

#endif
