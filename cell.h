#ifndef CELL_H
#define CELL_H

#include <cstddef>
#include <memory>
#include "subject.h"
#include "observer.h"
#include "state.h"
#include "info.h"
#include "block.h"

class Cell :  public Subject<Info, State>, public Observer<Info, State>{
  std::shared_ptr<Block> block = nullptr;

  public:
  void notify(std::shared_ptr<Subject<Info, State>> whoFrom) override;
  Info getInfo() const override;
  LevelType deleteCell() const;
};

#endif
