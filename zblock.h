#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "block.h"

class ZBlock : public Block, public std::enable_shared_from_this<ZBlock>{
  std::vector<std::pair<int, int>> baseGetCoordinates(int rotState, std::pair<int, int> leftBottom) const override;
  std::shared_ptr<Block> getThisPtr() override;

  public:
  ZBlock(LevelType level, DisplayFormat format);
  virtual ~ZBlock();
};

#endif

