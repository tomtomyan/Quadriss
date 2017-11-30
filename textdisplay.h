#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
//#include "observer.h"
//#include "state.h"       //// TextDisplay is in vector of observers in Grid
//#include "info.h"
class Cell;

class TextDisplay: public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;
 public:
  TextDisplay(int n);

  void notify(shared_ptr <Subject<Info, State>> whoNotified) override; // Cell passed in

 // friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
