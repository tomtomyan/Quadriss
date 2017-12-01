#include "textdisplay.h"

TextDisplay::TextDisplay(int x, int y) {
  for (int i = 0; i < y; i++ ) {
    std::vector<char> row;
    for (int j = 0; j < x; j++) {
      row.emplace_back(' ');
    }
    theDisplay.emplace_back(row);
  }
}

void TextDis

