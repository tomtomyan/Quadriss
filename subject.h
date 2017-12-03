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
   virtual std::shared_ptr<Subject<InfoType, StateType>> getThisSubjectPtr() = 0;
   StateType getState() const;
//   virtual ~Subject<InfoType, StateType>() = 0;
};

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(std::shared_ptr<Observer<InfoType, StateType>> o){
  observers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::detach(std::shared_ptr<Observer<InfoType, StateType>> o){
  for(auto it=observers.begin(); it!=observers.end(); ++it){
    if(&(*it) == &o){
      observers.erase(it);
    }
  }
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers(){
  for (auto ob : observers) ob->notify(getThisSubjectPtr());
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newState){
  state = newState;
}

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const{
  return state;
}
/*
template <typename InfoType, typename StateType>
Subject<InfoType, StateType>::~Subject<InfoType, StateType>(){};
*/
#endif
