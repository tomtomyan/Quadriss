#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
//#include "subject.h"
template <typename InfoType, typename StateType> class Subject;

template <typename InfoType, typename StateType> class Observer{
  public:
  virtual void notify(std::shared_ptr<Subject<InfoType, StateType>> whoFrom) = 0;
  virtual ~Observer() = default;
};

#endif

