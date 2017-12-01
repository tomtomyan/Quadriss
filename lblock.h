#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"

class LBlock : public Block, public std::enable_shared_from_this<LBlock>{
  std::vector<std::pair<int, int>> baseGetCoordinates(int rotState, std::pair<int, int> leftBottom) const override;
  std::shared_ptr<Block> getThisPtr() override;

  public:
  LBlock(LevelType level, DisplayFormat format);
  virtual ~LBlock();
};

#endif

