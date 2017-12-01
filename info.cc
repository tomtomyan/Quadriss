#include "info.h"

std::ostream &operator<<(std::ostream &out, const BlockType &bt){
  if(bt == BlockType::None) out << "None";
  else if(bt == BlockType::IBlock) out << "I Block";
  else if(bt == BlockType::JBlock) out << "J Block";
  else if(bt == BlockType::LBlock) out << "L BLock";
  else if(bt == BlockType::OBlock) out << "O Block";
  else if(bt == BlockType::SBlock) out << "S Block";
  else if(bt == BlockType::ZBlock) out << "Z Block";
  else if(bt == BlockType::TBlock) out << "T Block";
  else if(bt == BlockType::OneCell) out << "One Cell";
  return out;
}

std::ostream &operator<<(std::ostream &out, const LevelType &lt){
  if(lt == LevelType::None) out << "None";
  else if(lt == LevelType::Level1) out << "Level 1";
  else if(lt == LevelType::Level2) out << "Level 2";
  else if(lt == LevelType::Level3) out << "Level 3";
  else if(lt == LevelType::Level4) out << "Level 4";
  return out;
}

std::ostream &operator<<(std::ostream &out, const DisplayFormat &df){
  if(df == DisplayFormat::Standard) out << "Standard";
  else if(df == DisplayFormat::Hint) out << "Hint";
  else if(df == DisplayFormat::Obstacle) out << "Obstacle";
  else if(df == DisplayFormat::Current) out << "Current";
  return out;
}

