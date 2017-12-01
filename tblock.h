#ifndef TBLOCK_H
#define TBLOCK_H

#include "block.h"

class TBlock : public Block, public std::enable_shared_from_this<TBlock>{
  std::vector<std::pair<int, int>> baseGetCoordinates(int rotState, std::pair<int, int> leftBottom) const override;
  std::shared_ptr<Block> getThisPtr() override;

  public:
  TBlock(LevelType level, DisplayFormat format);
  virtual ~TBlock();
};

#endif

