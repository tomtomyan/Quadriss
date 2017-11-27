#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
  std::vector<std::shared_ptr<Observer<InfoType, StateType>>> observers;
  StateType state;
  protected:
  void setState(StateType newState);
  public:
  void attach(std::shared_ptr<Observer<InfoType, StateType>> o);
  void detach(std::shared_ptr<Observer<InfoType, StateType>> o);
  void notifyObservers();
  virtual InfoType getInfo() const = 0;
  StateType getState() const;
  virtual ~Subject() = default;
};

#endif
