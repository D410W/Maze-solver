#include "maze.h"

Maze::Maze( const vector< vector<Maze::cell_type> > & input_matrix )
    : m_maze{input_matrix}{
  for (int i = 0; i < m_maze.size(); ++i) {
    for (int j = 0; j < m_maze[i].size(); ++j) {
      switch (m_maze[i][j]) {
      case cell_type::ENTRY:
        m_entry = Position(j,i);
        break;
      case cell_type::EXIT:
        m_exit = Position(j,i);
        break;
      }
    }
  }
  
}

void Maze::print() const{
  for (int i = 0; i < m_maze.size(); ++i) {
    for (int j = 0; j < m_maze[i].size(); ++j) {
      std::string toout;
      switch (m_maze[i][j]) {
      case cell_type::WALL:
        toout = "█";
        break;
      case cell_type::FREE:
        toout = " ";
        break;
      case cell_type::ENTRY:
        toout = "x";
        break;
      case cell_type::EXIT:
        toout = "e";
        break;
      case cell_type::PATH:
        toout = "•";
        break;
      case cell_type::INV_WALL:
        toout = " ";
        break;
      }
      std::cout << toout;
    }
    std::cout << std::endl;
  }
}

bool Maze::is_blocked( const Position& pos ) const{
  cell_type cell = m_maze[pos.col][pos.row];
  return cell == cell_type::WALL || cell == cell_type::INV_WALL;
}

bool Maze::is_exit( const Position & pos ) const{
  return m_maze[pos.col][pos.row] == cell_type::EXIT;
}

Position Maze::walk_to( Position pos, const direction_t & dir ) const{
  switch (dir) {
  case UP:
    pos.row++;
    break;
  case DOWN:
    pos.row--;
    break;
  case LEFT:
    pos.col++;
    break;
  case RIGHT:
    pos.col--;
    break;
  }
  
  return pos;
}
