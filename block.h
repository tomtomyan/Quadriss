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

  virtual std::vector<std::pair<int, int>> baseGetCoordinates(int roState, std::pair<int, int> leftBottom) const = 0;

  virtual std::shared_ptr<Block> getThisPtr() = 0;

  public:
  Block(BlockType type, LevelType level, DisplayFormat format);
  virtual ~Block() = 0;
  int getCellsLeft() const;
  int getRotationState() const;
  void setRotationState(int);
  Info getInfo() const;
  std::vector<std::pair<int, int>> getRotated(bool clockwise, std::pair<int, int> leftBottom) const;
  void rotate(bool clockwise);
  LevelType cellDeleted();
  std::vector<std::pair<int, int>> getCoordinates(std::pair<int, int>) const;
  void notifyAttachDetach(bool isAttach, std::shared_ptr<Observer<Info, State>> ob, std::pair<int, int> coords);
  std::shared_ptr<Subject<Info, State>> getThisSubjectPtr() override;

  friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Block> &b);
};

#endif

