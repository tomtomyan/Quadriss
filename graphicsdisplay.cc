#include <iostream>
#include <sstream>
#include <iomanip>
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int winWidth, int winHeight):
 winWidth{winWidth}, winHeight{winHeight}, xw{winWidth, winHeight}, cellSize{(winHeight/24) < (winWidth/13) ? (winHeight/24) : (winWidth/13)} {
  createGrid();

  gridXShift = cellSize;
  gridYShift = cellSize*4;
  drawInitial();
}

void GraphicsDisplay::createGrid(){
  grid.clear();
  for(int y=0; y<gridHeight; y++){
    vector<pair<bool, int>> row;
    for(int x=0; x<gridWidth; x++){
      row.emplace_back(make_pair(false, blankColour));
    }
    grid.emplace_back(row);
  }
}

void GraphicsDisplay::drawInitial(){
  xw.fillRectangle(0, 0, winWidth, winHeight, blankColour); //fills background
  xw.fillRectangle(gridXShift-1, gridYShift-1, (cellSize*gridWidth)+2, 1); //draws border
  xw.fillRectangle(gridXShift-1, gridYShift+(cellSize*15)+1, (cellSize*gridWidth)+2, 1);
  xw.fillRectangle(gridXShift-1, gridYShift-1, 1, (cellSize*gridHeight)+2);
  xw.fillRectangle(gridXShift+(cellSize*gridWidth)+1, gridYShift-1, 1, (cellSize*gridHeight)+2);
  needShift = true;
  maxRowShift = gridHeight;
}

void GraphicsDisplay::drawGameOver(){
  xw.fillRectangle(0, 0, winWidth, winHeight, Xwindow::Black); //fills background
  xw.drawString((winWidth/2)-20, winHeight/2, "Game Over", Xwindow::Red);
}

//  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown}; // Available colours.
int GraphicsDisplay::colourDefinition(BlockType type, DisplayFormat format) const{
  int colour = blankColour;
  if(format == DisplayFormat::Standard){
    switch(type){
      case BlockType::IBlock:  colour = Xwindow::Green;
                               break;
      case BlockType::JBlock:  colour = Xwindow::Blue;
                               break;
      case BlockType::LBlock:  colour = Xwindow::Cyan;
                               break;
      case BlockType::SBlock:  colour = Xwindow::Yellow;
                               break;
      case BlockType::ZBlock:  colour = Xwindow::Magenta;
                               break;
      case BlockType::OBlock:  colour = Xwindow::Orange;
                               break;
      case BlockType::TBlock:  colour = Xwindow::Red;
                               break;
    }
  }
  else{
    switch(format){
      case DisplayFormat::Obstacle: colour = Xwindow::Brown;
                                    break;
      case DisplayFormat::Hint: colour = Xwindow::Black;
                                break;
    }
  }
  return colour;
}

void GraphicsDisplay::redraw(GameState gameState){
  if(gameState.gameOver){
    drawGameOver();
    this->gameOver = true;
    createGrid();
    return;
  }
  else if(this->gameOver && !(gameState.gameOver)){
    drawInitial();
    this->gameOver = false;
  }
  // Draws text at top
  xw.fillRectangle(0, 0, cellSize*gridWidth, (cellSize*2)+(cellSize/2), blankColour);
  ostringstream levelStr;
  levelStr << gameState.level;
  xw.drawString(gridXShift, cellSize, levelStr.str());
  ostringstream scoreStr;
  scoreStr << "Score: " << setw(15)  << gameState.playScore;
  xw.drawString(gridXShift, cellSize*2, scoreStr.str());
  ostringstream hiScoreStr;
  hiScoreStr << "High Score: " << setw(10)  << gameState.highScore;
  xw.drawString(gridXShift, cellSize*3, hiScoreStr.str());
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
  needShift = false;
  maxRowShift = 0;
  // Draws next block
  int numCells = gameState.nextBlockCoords.size();
  int col = colourDefinition(gameState.nextBlock, DisplayFormat::Standard);
  for(int x=0; x<4; x++){
    for(int y=0; y<3; y++){
      xw.fillRectangle(gridXShift+(cellSize*x), gridYShift+(cellSize*(gridHeight+y+1)), cellSize, cellSize, blankColour);
    }
  }
  for(int i=0; i<numCells; i++){
    pair<int, int> cur = gameState.nextBlockCoords.at(i);
    xw.fillRectangle(gridXShift+(cellSize*cur.first), gridYShift+(cellSize*(gridHeight+cur.second)), cellSize, cellSize,col);
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
      maxRowShift = coords.second+1 > maxRowShift ? coords.second+1 : maxRowShift;
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

void GraphicsDisplay::print(){
  cout << "-------------------" << endl;
  for(int y=0; y<gridHeight; y++){
    for(int x=0; x<gridWidth; x++){
      int col = grid[y][x].second;
      if(col == 0) cout  << " ";
      else cout << col;
    }
    cout << endl;
  }
  cout << "-------------------" << endl;
}

