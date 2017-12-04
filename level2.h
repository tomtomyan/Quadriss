#ifndef LEVEL2_H
#define LEVEL2_H
#include <memory>
#include "level.h"
class Block;

class Level2 : public Level {
  public:
	Level2(int seed);
  void setIsRandom(bool isRandom, std::string fileName = "") override;
  std::shared_ptr<Block> generateBlock(BlockType type = BlockType::None) override;
  std::shared_ptr<Block> obstacle(std::pair<int,int> &) override;
};

#endif
