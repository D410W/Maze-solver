#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

#include "maze.h"

/// Possible outcomes from the read_file()
#define ERR_FAILED_OPENING_INPUT_FILE 0
#define ERR_MISSING_ENTRY_EXIT 1
#define READ_OK 2

using std::vector;


/// Print out a Position
std::ostream& operator<<( std::ostream& os, const Position & p )
{
    os << "(" << p.row << "," << p.col << ")";
    return os;
}

/*!
 * Acha um caminho da entrada até a saída, marcando as células que compõem
 * a solução no objeto maze. Utiliza recursão.
 *
 * @param m O labirinto que queremos solucionar.
 * @param start O ponto (coordenada) de partida do caminho.
 * @param end O ponto (coordenada) de saída do labirinto.
 * @return `true` se existe uma solução; `false` caso contrário.
 */
bool solve_maze( Maze& m, const Position& start, const Position& end )
{
    
    Position maze_size = m.maze_size();
                    
    m.mark_cell(start);
    
    if (m.is_exit(start)) return true;

    for (direction_t dir = UP; int(dir) < int(AMOUNT); dir = direction_t(dir + 1)) {
        Position next_p = m.walk_to(start, dir);
        
        if (next_p.row < 0 or next_p.col < 0
         or next_p.row >= maze_size.row or next_p.col >= maze_size.col) continue;
     
        if (m.is_marked(next_p)) continue;
        if (m.is_blocked(next_p)) continue;
                
        if (solve_maze(m, next_p, end)) return true;
    }
    
    m.unmark_cell(start);

    return false;
}

/// Reads a maze from the input file and returns a matrix of integers representing the input maze.
/*!
 * @param file_name The input file name.
 * @param matrix A bi-dimensional matrix that stores the input data as integers.
 * @return A status code indicating the reading was ok, or the error code, otherwise.
 */
int read_file( std::string file_name, vector<vector<Maze::cell_type>> &matrix ){
    std::ifstream ifs { file_name }; // Creating and Opening the stream.
    
    if (!ifs) return ERR_FAILED_OPENING_INPUT_FILE;
        
    vector<Maze::cell_type> line;
    
    for (char c{}; !ifs.eof(); c = ifs.get()) {
        if (c == '\n') {
            matrix.push_back(line);
            line.clear();
        } else {
            switch (c) {
            case '1':
                line.push_back(Maze::cell_type::WALL);
                break;
            case '0':
                line.push_back(Maze::cell_type::FREE);
                break;
            case 'm':
                line.push_back(Maze::cell_type::ENTRY);
                break;
            case 'e':
                line.push_back(Maze::cell_type::EXIT);
                break;
            case ' ':
                line.push_back(Maze::cell_type::FREE);
                break;
            case '.':
                line.push_back(Maze::cell_type::INV_WALL);
            }
        }
    }

    return READ_OK;
}

int main( int argc, char *argv[] ){
    if ( argc != 2 ) {
        std::cout << ">>> Missing input file!\n"
                  << "    Sintax: maze [inpu_file_name]\n\n";
        return 1;
    }

    // Recebe uma matriz de inteiros representando um labirinto.
    vector<vector<Maze::cell_type>> input_matrix;
    auto result = read_file( argv[1], input_matrix );
    if ( result == ERR_FAILED_OPENING_INPUT_FILE ) {
        std::cerr << "--> Fail while attempting to open the input maze file [" << argv[1] << "]!\n";
        return 1;
    }
    else if ( result == ERR_MISSING_ENTRY_EXIT ) {
        std::cerr << "--> Maze does not have entry and/or exit cell marked.\n"
                  << "    Please use `m` for the maze's entry, and `e` for the maze's exit.\n\n";
        return 1;
    }
    else if ( result == READ_OK ) {
        std::cout << ">>> Input file successfuly read!\n";
    }
    else std::cerr << ">>> Undefined error code received!\n";

    // Cria o objeto labirinto.
    Maze maze( input_matrix );
    // Exibe o labirinto ainda sem solução.
    std::cout << ">>> Input maze is: \n";
    maze.print();
    std::cout << "    Entry is located at " << maze.entry()
              << ", and Exit is located at " << maze.exit() << std::endl << std::endl;

    std::cout << ">>> Finding a solution, please wait...\n";
    if ( solve_maze( maze, maze.entry(), maze.exit() ) )
    {
        std::cout << "  The `█` represents a wall\n"
                  << "  The ` ` represents a free cell\n"
                  << "  The `x` represents the maze's entry point\n"
                  << "  The `•` represents the path to the exit\n"
                  << "  The `e` represents the maze's exit.\n\n";
        maze.print(); // Exibe a solução.
    }
    else std::cout << ">>> Sorry, this maze does not have a solution.!!\n";

    return 0;
}
