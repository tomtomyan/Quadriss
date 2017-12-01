#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"

class JBlock : public Block {
  virtual std::vector<std::pair<int, int>> baseGetCoordinates(int rotState, std::pair<int, int> leftBottom) const override;

  public:
  JBlock(LevelType level, DisplayFormat format);
  virtual ~JBlock();
//  Info getInfo();
};

#endif

