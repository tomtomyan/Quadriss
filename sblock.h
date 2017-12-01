#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"

class SBlock : public Block, public std::enable_shared_from_this<SBlock>{
  std::vector<std::pair<int, int>> baseGetCoordinates(int rotState, std::pair<int, int> leftBottom) const override;
  std::shared_ptr<Block> getThisPtr() override;

  public:
  SBlock(LevelType level, DisplayFormat format);
  virtual ~SBlock();
};

#endif

