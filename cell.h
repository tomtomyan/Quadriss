#ifndef CELL_H
#define CELL_H

#include <cstddef>
#include "subject.h"
#include "observer.h"
#include "state.h"
#include "info.h"

class Cell :  public Subject<Info, State>, public Observer<Info, State>{
  //std::shared_pointer block = std::shared_pointer...

  public:
  void notify(Subject<Info, State> &whoFrom) override;
  Info getInfo() override;
  LevelType deleteCell();
};

#endif
