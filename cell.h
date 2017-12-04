#ifndef CELL_H
#define CELL_H

#include <cstddef>
#include <memory>
#include <iostream>
#include "subject.h"
#include "observer.h"
#include "block.h"

class Cell :  public Subject<Info, State>, public Observer<Info, State>, public std::enable_shared_from_this<Cell>{
  std::shared_ptr<Block> block; 

  public:
  void notify(std::shared_ptr<Subject<Info, State>> whoFrom) override;
  Info getInfo() const override;
  LevelType deleteCell(std::pair<int, int> coords, bool lastChecked = false);
  std::shared_ptr<Subject<Info, State>> getThisSubjectPtr() override;
  
  friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Cell> &c);
};

#endif
