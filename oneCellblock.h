#ifndef ONECELLBLOCK_H
#define ONECELLBLOCK_H

#include "block.h"

class OneCellBlock : public Block, public std::enable_shared_from_this<OneCellBlock>{
  std::vector<std::pair<int, int>> baseGetCoordinates(int rotState, std::pair<int, int> leftBottom) const override;
  std::shared_ptr<Block> getThisPtr() override;

  public:
  OneCellBlock(LevelType level, DisplayFormat format);
  virtual ~OneCellBlock();
};

#endif

