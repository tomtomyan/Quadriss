#include <iostream>
#include <string>

#include "cell.h"
//#include "iblock.h"
#include "jblock.h"
#include "block.h"

using namespace std;

void print(vector<vector<shared_ptr<Cell>>> &grid){
  cout << "<===================" << endl;
  for(int y=0; y<4; y++){
    cout << "|";
    for(int x=0; x<4; x++){
//      cout << c.getInfo().type;
  // shared_ptr<Cell> c = grid[y][x];
     Info info = grid.at(y).at(x)->getInfo();
//      cout << info.type;
      if(info.type == BlockType::IBlock) cout << "I";
      else if(info.type == BlockType::JBlock) cout << "J";
      else cout << " ";
    }
    cout << "|" << endl;
  }
  cout << "====================>" << endl;
}
      
bool inGrid(int x, int y, vector<pair<int, int>> coords){
  int size = coords.size();
  for(int i=0; i<size; i++){
    pair<int, int> now = coords.at(i);
    if(now.first<0 || now.first>=x || now.second<0 || now.second>=y) return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  vector<vector<shared_ptr<Cell>>> grid;
  for(int y=0; y<4; y++){
    vector<shared_ptr<Cell>> row;
    for(int x=0; x<4; x++){
      row.emplace_back(make_shared<Cell>());
    }
    grid.emplace_back(row);
  }

  print(grid);

  shared_ptr<Block> b1 = make_shared<JBlock>(LevelType::Level1, DisplayFormat::Standard);
  vector<pair<int, int>> coords = b1->getCoordinates(make_pair(0,3));
  if(inGrid(4, 4, coords)){
    for(int i=0; i<1; i++){
      pair<int, int> now = coords.at(i);
      cout << "attach? "<< now.first << " " << now.second << endl;
      b1->notifyAttachDetach(true,grid[now.second][now.first], now);
    }
  }

  print(grid);
  cout << "end" << endl;
}
