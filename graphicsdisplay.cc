#include <iostream>
#include <sstream>
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int winWidth, int winHeight):
 winWidth{winWidth}, winHeight{winHeight}, xw{winWidth, winHeight}, cellSize{winHeight/24 < winWidth/13 ? winHeight/24 : winWidth/13} {
  for(int y=0; y<gridHeight; y++){
    vector<pair<bool, int>> row;
    for(int x=0; x<gridWidth; x++){
      row.emplace_back(make_pair(false, blankColour));
    }
    grid.emplace_back(row);
  }

  gridXShift = cellSize;
  gridYShift = cellSize*4;
  xw.fillRectangle(0, 0, winWidth, winHeight, blankColour); //fills background
  xw.fillRectangle(gridXShift-1, gridYShift-1, (cellSize*gridWidth)+2, 1); //draws border
  xw.fillRectangle(gridXShift-1, gridYShift+(cellSize*15)+1, (cellSize*gridWidth)+2, 1);
  xw.fillRectangle(gridXShift-1, gridYShift-1, 1, (cellSize*gridHeight)+2);
  xw.fillRectangle(gridXShift+(cellSize*gridWidth)+1, gridYShift-1, 1, (cellSize*gridHeight)+2);
  needShift = true;
  maxRowShift = gridHeight;
}

//  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown}; // Available colours.
int GraphicsDisplay::colourDefinition(BlockType type, DisplayFormat format) const{
  int colour = blankColour;
  if(format == DisplayFormat::Standard){
    switch(type){
      case BlockType::IBlock: colour = Xwindow::Green;
      case BlockType::JBlock: colour = Xwindow::Blue;
      case BlockType::LBlock: colour = Xwindow::Cyan;
      case BlockType::SBlock: colour = Xwindow::Yellow;
      case BlockType::ZBlock: colour = Xwindow::Magenta;
      case BlockType::OBlock: colour = Xwindow::Orange;
      case BlockType::TBlock: colour = Xwindow::Red;
    }
  }
  else{
    switch(format){
      case DisplayFormat::Obstacle: colour = Xwindow::Brown;
      case DisplayFormat::Hint: colour = Xwindow::Black;
    }
  }
  return colour;
}

void GraphicsDisplay::redraw(GameState gameState){
  // Draws text at top
  ostringstream levelStr;
  levelStr << gameState.level;
  xw.drawString(gridXShift, cellSize/2, levelStr.str());
  ostringstream scoreStr;
  scoreStr << "Score: " << gameState.playScore;
  xw.drawString(gridXShift, (cellSize/2)+cellSize, scoreStr.str());
  ostringstream hiScoreStr;
  hiScoreStr << "Hi Score: " << gameState.highScore;
  xw.drawString(gridXShift, (cellSize/2)+cellSize, hiScoreStr.str());
  // Draws grid
  if(needShift){
    for(int y=0; y<maxRowShift; y++){
      for(int x=0; x<gridWidth; x++){
        xw.fillRectangle(gridXShift+(cellSize*x), gridYShift+(cellSize*y), cellSize, cellSize, grid.at(y).at(x).second);
      }
    }
  }
  int numQueue = queue.size();
  for(int i=0; i<numQueue; i++){
    pair<pair<int, int>, int> change = queue.at(i);
    if(needShift && change.first.second <= maxRowShift) continue;
    xw.fillRectangle(gridXShift+(cellSize*change.first.first), gridYShift+(cellSize*change.first.second), cellSize, cellSize, change.second);
  }
  queue.clear();
  // Draws next block
  int numCells = gameState.nextBlockCoords.size();
  int col = colourDefinition(gameState.nextBlock, DisplayFormat::Standard);
  for(int i=0; i<numCells; i++){
    pair<int, int> cur = gameState.nextBlockCoords.at(i);
    xw.fillRectangle(gridXShift+(cellSize*cur.first), gridYShift+(cellSize*(gridHeight+cur.second+1)), cellSize, cellSize,col);
  }
}

void GraphicsDisplay::notify(shared_ptr<Subject<Info, State>> whoNotified) {
  auto info = whoNotified->getInfo();
  State state = whoNotified->getState();
  pair<int, int> coords = state.coordinates;
  int colour = colourDefinition(info.type, info.format);

  if(state.message == Message::Delete){
    grid.at(coords.second).at(coords.first) = make_pair(true, colour);
    bool deleteRow = true;
    for(int i=0; i<gridWidth; i++){
      if(!(grid.at(coords.second).at(i).first)){
        deleteRow = false;
        break;
      }
    }
    if(deleteRow){
      needShift = true;
      maxRowShift = coords.second > maxRowShift ? coords.second : maxRowShift;
      grid.erase(grid.begin()+coords.second);
      vector<pair<bool, int>> row;
      for(int i=0; i<gridWidth; i++){
        row.emplace_back(make_pair(false, blankColour));
      }
      grid.insert(grid.begin(), row);
    }
  }
  else{
    grid.at(coords.second).at(coords.first) = make_pair(false, colour);
    queue.emplace_back(make_pair(coords, colour));
  }
}

