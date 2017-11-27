#ifndef OBSERVER_H
#define OBSERVER_H

template <typename InfoType, typename StateType> class Subject;

template <typename InfoType, typename StateType> class Observer{
  public:
  virtual void notify(Subject<InfoType, StateType> &whoFrom) = 0;
  virtual ~Observer() = default;
};

#endif

