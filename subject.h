#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
 // std::vector<Observer<InfoType, StateType>*> observers;
  StateType state;
  protected:
  void setState(StateType newState);
  public:
  // void attach(Observer<InfoType, StateType> *o);
  void notifyObservers();
  virtual InfoType getInfo() const = 0;
  StateType getState() const;
};

#endif
