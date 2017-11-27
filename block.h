#ifndef BLOCK_H
#define BLOCK_H

#include <cstddef>
#include <vector>
#include <memory>
#include "observer.h"
#include "subject.h"
#include "state.h"
#include "info.h"

class Block : public Subject<Info, State>{
  int cellsLeft;
  int rotationState;
  LevelType level;
  BlockType type;
  DisplayFormat format;
  public:
  Info getInfo() const;
  LevelType cellDeleted();
  std::vector<std::pair<int, int>> getCoordinates(std::pair<int, int>) const;
  void notifyAttachDetach(bool isAttach, std::shared_ptr<Observer<Info, State>> ob, std::pair<int, int> coords);
};

#endif

