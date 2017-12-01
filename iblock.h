#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"

class IBlock : public Block, public std::enable_shared_from_this<IBlock>{
  std::vector<std::pair<int, int>> baseGetCoordinates(int rotState, std::pair<int, int> leftBottom) const override;
  std::shared_ptr<Block> getThisPtr() override;

  public:
  IBlock(LevelType level, DisplayFormat format);
  virtual ~IBlock();
};

#endif

