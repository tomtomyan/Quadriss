#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"

class OBlock : public Block, public std::enable_shared_from_this<OBlock>{
  std::vector<std::pair<int, int>> baseGetCoordinates(int rotState, std::pair<int, int> leftBottom) const override;
  std::shared_ptr<Block> getThisPtr() override;

  public:
  OBlock(LevelType level, DisplayFormat format);
  virtual ~OBlock();
};

#endif

