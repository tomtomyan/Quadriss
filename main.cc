#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>
#include "grid.h"
#include "graphicsdisplay.h"
using namespace std;

enum Command {Invalid, Left, Right, Down, Clockwise, CounterClockwise, Drop, LevelUp, LevelDown, NoRandom, Random, Sequence, Restart, Hint, SetBlock, Rename};

pair<Command, tuple<int, string>> interpretCommand(vector<pair<Command, vector<string>>> &allCmds, string cmd){
  string argument;
  istringstream iss{cmd};
  int n;
  if (!(iss >> n)) n = 1;
  iss >> cmd;

  Command fullCmd;
  int size = allCmds.size();
  int counter = 0; //counter stores occurences where the cmd is found in the list of strings
  for (int i = 0; i < size; i++) {
    pair<Command, vector<string>> cmdDef = allCmds.at(i);
    int defSize = cmdDef.second.size();
    for(int j=0; j < defSize; j++){
      if (cmdDef.second.at(j).find(cmd) == 0) {
        counter++;
        fullCmd = cmdDef.first;
      }
    }
  }

  if (counter != 1) fullCmd = Command::Invalid;
  if(Command::SetBlock) argument = cmd;
  return make_pair(fullCmd, make_tuple(n, argument));
}


int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid grid;
  shared_ptr<GraphicsDisplay> graphDis;

  // Vector holds all of the known commands
  vector<pair<Command, vector<string>>> allCmds;
    auto temp1 = make_pair(Command::Left, vector<string>{"left"});
    auto temp2 = make_pair(Command::Right, vector<string>{"right"});
    auto temp3 = make_pair(Command::Down, vector<string>{"down"});
    auto temp4 = make_pair(Command::Clockwise, vector<string>{"clockwise"});
    auto temp5 = make_pair(Command::CounterClockwise, vector<string>{"counterclockwise"});
    auto temp6 = make_pair(Command::Drop, vector<string>{"drop"});
    auto temp7 = make_pair(Command::LevelUp, vector<string>{"levelup"});
    auto temp8 = make_pair(Command::LevelDown, vector<string>{"leveldown"});
    auto temp9 = make_pair(Command::NoRandom, vector<string>{"norandom"});
    auto temp10 = make_pair(Command::Random, vector<string>{"random"});
    auto temp11 = make_pair(Command::Sequence, vector<string>{"sequence"});
    auto temp12 = make_pair(Command::Restart, vector<string>{"restart"});
    auto temp13 = make_pair(Command::Hint, vector<string>{"hint"});
    auto temp14 = make_pair(Command::SetBlock, vector<string>{"I","J","S","Z","O","T","L"});
    auto temp15 = make_pair(Command::Rename, vector<string>{"rename"});
    allCmds.emplace_back(temp1);
    allCmds.emplace_back(temp2);
    allCmds.emplace_back(temp3);
    allCmds.emplace_back(temp4);
    allCmds.emplace_back(temp5);
    allCmds.emplace_back(temp6);
    allCmds.emplace_back(temp7);
    allCmds.emplace_back(temp8);
    allCmds.emplace_back(temp9);
    allCmds.emplace_back(temp10);
    allCmds.emplace_back(temp11);
    allCmds.emplace_back(temp12);
    allCmds.emplace_back(temp13);
    allCmds.emplace_back(temp14);
    allCmds.emplace_back(temp15);

  // COMMAND LINE ARGUMENT VARIABLES
  bool textOnly = false;
  string scriptFile = "sequence.txt";
  string startLevel = "0"; // default start level
  bool isSequence = false;
  bool seqFirstTime = true;
  string fileName;  // if isSequence is true, read commands from this file
  ifstream fileStream;
  int seed = 1;

  //COMMAD LINE ARGUMENTS
  for (int i = 1; i < argc; i++) {
    if (argv[i] == std::string("-text")) {
      textOnly = true;
      cout << "Text only mode" << endl;
    } else if (argv[i] == string("-seed")) {
      if (i+1 < argc) {
        int n;
        string s = argv[i+1];
        istringstream iss{s};
        if (iss >> n) {
          seed = n;
          cout << "Seed set to " << seed << endl;
        }
        ++i;
      }
    } else if (argv[i] == string("-scriptfile")) {
      if (i+1 < argc) {
        scriptFile = argv[i+1];
        cout << "Script file set to " << scriptFile << endl;
        ++i;
      }
    } else if (argv[i] == std::string("-startlevel")) {
      if (i+1 < argc) {
        startLevel = argv[i+1];
        cout << "Start level set to " << startLevel << endl;
        ++i;
      }
    }
  }

  if (!textOnly) {
    graphDis = make_shared<GraphicsDisplay>(380, 700);
    grid.attachObserver(graphDis);
  }


  if (startLevel == "0") {
    grid.init(LevelType::Level0, seed, false, scriptFile);
  } else if (startLevel == "1") {
    grid.init(LevelType::Level1, seed);
  } else if (startLevel == "2") {
    grid.init(LevelType::Level2, seed);
  } else if (startLevel == "3") {
    grid.init(LevelType::Level3, seed);
  } else if (startLevel == "4") {
    grid.init(LevelType::Level4, seed);
  } else {  // if no startlevel option is supplied, start at Level 0
    grid.init(LevelType::Level0, seed, false, scriptFile);
  }
  cout << grid << endl;
  if (!textOnly) graphDis->redraw(grid.getGameState());

  //COMMAND INTERPRETER
  try {
    while (true) {
      // GETS COMMAND FROM INPUT
      if (isSequence && seqFirstTime) {
        if(seqFirstTime){
          seqFirstTime = false;
          fileStream = ifstream{fileName};
          if (!(fileStream >> cmd)) {
            isSequence = false;
            cout << "End of sequence file. Start providing input." << endl;
            continue;
          }
        }
        else if (!(fileStream >> cmd)) {
          isSequence = false;
          cout << "End of sequence file. Start providing input." << endl;
          continue;
        }
      }
      else if(!(cin >> cmd)){
        cout << "Error, please try again" << endl;
        continue;
      }

      // EXECUTES COMMAND
      auto fullCmd = interpretCommand(allCmds, cmd);
      Command newcmd = fullCmd.first;
      int n = get<0>(fullCmd.second);

      if(newcmd == Command::Invalid){
        cout << "Invalid command. Please try again" << endl;
        continue;
      }
      else if (newcmd == Command::Left) grid.left(n);
      else if (newcmd == Command::Right) grid.right(n);
      else if (newcmd == Command::Down) grid.down(n);
      else if (newcmd == Command::Clockwise) grid.clockwise(n);
      else if (newcmd == Command::CounterClockwise) grid.counterClockwise(n);
      else if (newcmd == Command::Drop) grid.drop(n);
      else if (newcmd == Command::LevelUp) grid.levelUp(n);
      else if (newcmd == Command::LevelDown) grid.levelDown(n);
      else if (newcmd == Command::Random) grid.random(true);
      else if (newcmd == Command::Hint) grid.hint();
      else if (newcmd == Command::NoRandom) {
        string file;
        if ((isSequence && fileStream >> file) || (cin >> file)) {
          grid.random(false, file);
        }
      } 
      else if (newcmd == Command::Sequence) {
        if ((isSequence && fileStream >> fileName) || (cin >> fileName)) {
	        seqFirstTime = true;
          isSequence = true;
        }
      } 
      else if (newcmd == Command::Restart) {
        grid.init(LevelType::Level0, seed, false, scriptFile);
      } 
      else if(newcmd = Command::SetBlock){
        string para = get<1>(fullCmd.second);
        BlockType type;
        if (para == "I") type = BlockType::IBlock;
        else if (para == "J") type = BlockType::JBlock;
        else if (para == "L") type = BlockType::LBlock;
        else if (para == "O") type = BlockType::OBlock;
        else if (para == "S") type = BlockType::SBlock;
        else if (para == "Z") type = BlockType::ZBlock;
        else if (para == "T") type = BlockType::TBlock;
        grid.setBlock(type);
      }
      else if (newcmd == Command::Rename) {
        //////////// New feature: Renaming commands //////////////
        string renamedCmd;
        string newCmdName;
        if(isSequence){
          fileStream >> renamedCmd;
          fileStream >> newCmdName;
        }
        else{
          cin >> renamedCmd;
          cin >> newCmdName;
        }
        auto toBeRenamed = interpretCommand(allCmds,renamedCmd);
        auto result = interpretCommand(allCmds,newCmdName);
        if(toBeRenamed.first==Command::Invalid || result.first!=Command::Invalid){
          cout << "Invalid input, please try again." << endl;
          continue;
        }
        int allSize = allCmds.size();
        for(int i=0; i<allSize; i++){
          if(allCmds.at(i).first == toBeRenamed.first){
            allCmds.at(i).second.emplace_back(newCmdName);
          }
        }
      }

      cout << grid;
      if (!textOnly) graphDis->redraw(grid.getGameState());
    }
  } catch (ios::failure &) {}

}
