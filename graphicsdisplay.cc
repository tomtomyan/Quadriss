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
  playerScore = -1; //to make sure the top part redraws upon a new game
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

void GraphicsDisplay::clearRows(){
  // We need to sort the list of deleted row. This way, we can delete the top
  // rows first and not shift the positions of the rows below it.
  vector<int> sortedDeleted;
  while(rowsDeleted.size() > 0){
    int lenRD = rowsDeleted.size();
    int min = rowsDeleted.at(0);
    int posMin = 0;
    for(int i=1; i<lenRD; i++){
      int cur = rowsDeleted.at(i);
      if(cur<min){
        min = cur;
	      posMin = i;
      }
    }
    sortedDeleted.emplace_back(min);
    rowsDeleted.erase(rowsDeleted.begin()+posMin);
  }
  // Delete rows and add new ones on
  int numDeleted = sortedDeleted.size();
  for(int i=0; i<numDeleted; i++){
    grid.erase(grid.begin()+sortedDeleted.at(i));
    vector<pair<bool, int>> row;
    for(int j=0; j<gridWidth; j++){
      row.emplace_back(make_pair(false, blankColour));
    }
    grid.insert(grid.begin(), row);
  }
  rowsDeleted.clear();
}

void GraphicsDisplay::emptyQueue(){
  vector<pair<pair<int, int>, int>> finalQueue;
  int numQueue = queue.size();
  for(int i=0; i<numQueue; i++){
    pair<pair<int, int>, int> change = queue.at(i);
    bool alreadyExists = false;
    int finalSize = finalQueue.size();
    for(int k=0; k<finalSize; k++){
      if(change.first.first == finalQueue.at(k).first.first && change.first.second == finalQueue.at(k).first.second){
        alreadyExists = true;
        break;
      }
    }
    if(alreadyExists) continue;
    int finalIndex = i;
    for(int j=i+1; j<numQueue; j++){
      if(change.first.first == queue.at(j).first.first && change.first.second == queue.at(j).first.second){
        finalIndex = j;
      }
    }
    finalQueue.emplace_back(queue.at(finalIndex));
  }
  
  int finalSize = finalQueue.size();
  for(int i=0; i<finalSize; i++){
    pair<pair<int, int>, int> change = finalQueue.at(i);
    xw.fillRectangle(gridXShift+(cellSize*change.first.first), gridYShift+(cellSize*change.first.second), cellSize, cellSize, change.second);
  }
  queue.clear();
}

void GraphicsDisplay::redraw(GameState gameState){
  if(gameState.gameOver){
    drawGameOver();
    this->gameOver = true;
    createGrid();
    return;
  }

//  print();
  // Draws text at top
  if(level!=gameState.level || playerScore!=gameState.playScore || highScore!=gameState.highScore){
    level = gameState.level;
    playerScore = gameState.playScore;
    highScore = gameState.highScore;
    xw.fillRectangle(0, 0, cellSize*gridWidth, cellSize*3, blankColour);
    ostringstream levelStr;
    levelStr << gameState.level;
    xw.drawString(gridXShift, cellSize, levelStr.str());
    ostringstream scoreStr;
    scoreStr << "Score: " << setw(15)  << gameState.playScore;
    xw.drawString(gridXShift, cellSize*2, scoreStr.str());
    ostringstream hiScoreStr;
    hiScoreStr << "High Score: " << setw(10)  << gameState.highScore;
    xw.drawString(gridXShift, cellSize*3, hiScoreStr.str());
  }
  // Draws grid
  emptyQueue();
  if(needShift){
    for(int y=0; y<maxRowShift; y++){
      for(int x=0; x<gridWidth; x++){
        xw.fillRectangle(gridXShift+(cellSize*x), gridYShift+(cellSize*y), cellSize, cellSize, grid.at(y).at(x).second);
      }
    }
  }
  needShift = false;
  maxRowShift = 0;
  // Draws next block
  if(gameState.nextBlock != nextBlock){
    nextBlock = gameState.nextBlock;
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
//  drawGuideLines();
}

void GraphicsDisplay::notify(shared_ptr<Subject<Info, State>> whoNotified) {
  auto info = whoNotified->getInfo();
  State state = whoNotified->getState();
  pair<int, int> coords = state.coordinates;
  int colour = colourDefinition(info.type, info.format);

  if(state.message == Message::Delete || state.message == Message::DeleteRows){
    grid.at(coords.second).at(coords.first) = make_pair(true, colour);
    bool deleteRow = true;
    for(int i=0; i<gridWidth; i++){
      if(!(grid.at(coords.second).at(i).first)){
        deleteRow = false;
        break;
      }
    }
    if(deleteRow){
      cout << "(" << coords.first << ", " << coords.second << ")" << endl;
      needShift = true;
      maxRowShift = coords.second+1 > maxRowShift ? coords.second+1 : maxRowShift;
      rowsDeleted.emplace_back(coords.second);
    }
    if(state.message == Message::DeleteRows) clearRows();
  }
  else{
    if(state.message == Message::FirstAttach){
      createGrid();
      drawInitial();
      this->gameOver = false;
    }
    grid.at(coords.second).at(coords.first) = make_pair(false, colour);
    queue.emplace_back(make_pair(coords, colour));
  }
}

void GraphicsDisplay::drawGuideLines(){
  for(int y = 0; y<winHeight; y+=20){
    xw.fillRectangle(0, y, winWidth, 1, Xwindow::Red);
  }
  for(int x = 0; x<winWidth; x+=20){
    xw.fillRectangle(x, 0, 1, winHeight, Xwindow::Red);
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

