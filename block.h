#ifndef BLOCK_H
#define BLOCK_H

#include <cstddef>
#include <vector>
#include <memory>
#include <iostream>
#include "observer.h"
#include "subject.h"
#include "state.h"
#include "info.h"

class Block : public Subject<Info, State>{
  BlockType type;
  LevelType level;
  DisplayFormat format;
  int cellsLeft;
  int rotationState;

  std::vector<std::pair<int, int>> baseGetCoordinates(int roState, std::pair<int, int> leftBottom) const;

  public:
  Block(BlockType type, LevelType level, DisplayFormat format);
  Info getInfo() const;
  std::vector<std::pair<int, int>> getRotated(bool clockwise, std::pair<int, int> leftBottom) const;
  void rotate(bool clockwise);
  LevelType cellDeleted();
  std::vector<std::pair<int, int>> getCoordinates(std::pair<int, int>) const;
  void notifyAttachDetach(bool isAttach, std::shared_ptr<Observer<Info, State>> ob, std::pair<int, int> coords);

  friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Block> &b);
};

#endif

