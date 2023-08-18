#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> 

using namespace std;

enum class State{kEmpty, kObstacle, kPath, kClosed, kStart, kFinish};

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};


vector<State> ParseLine(string line)
{
    vector<State> row;
    istringstream my_stream(line);

    int n;
    char c;

    while (my_stream >> n >> c && c == ',')
    {
        if(n == 0)
        {
            row.push_back(State::kEmpty);
        }
        else
        {
            row.push_back(State::kObstacle);
        }
    }

    return row;
}

vector<vector<State>> ReadBoardFile(string path)
{
    vector<vector<State>> board{};
    ifstream myFile(path);

    if (myFile) //check if successfully opened 
    {
        cout << "file stream has been created" << "\n";
        string line;
        while(getline(myFile, line))
        {
            // cout << line << "\n";
            vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }

    return board;
}

// compare the f-value of two nodes here
bool Compare(vector<int> node1 , vector<int> node2)
{
  int f1 = node1[2] + node1[3];
  int f2 = node2[2] + node2[3];
  
  return f1 > f2;
  
}

void CellSort(vector<vector<int>> *v)
{
    sort(v->begin(), v->end(), Compare);
}

// Calculate the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2)
{
  return abs(x2-x1) + abs(y2-y1);
}

// cell is on the grid and not an obstacle (i.e. equals kEmpty).
bool CheckValidCell(int x, int y, vector<vector<State>> &grid)
{
    // check that (x,y is on the grid)
    if (&grid[x][y] != NULL)
    {
        return grid[x][y] == State::kEmpty;
    }
    
    return false;

//their solution 
//       bool on_grid_x = (x >= 0 && x < grid.size());
//   bool on_grid_y = (y >= 0 && y < grid[0].size());
}

/** 
 * Add a node to the open list and mark it as open. 
 */
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &grid)
{
  vector<int> v{x,y,g,h};
  open_nodes.push_back(v);
  
  grid[x][y] = State::kClosed;
}

void ExpandNeighbors(const vector<int> &curr, int goal[2], vector<vector<int>> &open, vector<vector<State>> &grid)
{
  // TODO: Get current node's data.
  int x = curr[0];
  int y = curr[1];
  int g = curr[2];

  // TODO: Loop through current node's potential neighbors.
  for (int i=0; i<4; i++)
  { 
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    // TODO: Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (CheckValidCell(x2, y2, grid))
    {
        // TODO: Increment g value, compute h value, and add neighbor to open list.
        int g2 = g + 1;
        int h = Heuristic(x2, y2, goal[0], goal[1]);
        //x,y,g,h,open, grid
        AddToOpen(x2, y2, g2, h, open, grid);
    }

  }
}

// vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) {
vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) 
{
    // Create the vector of open nodes.
    vector<vector<int>> open {};

    // Initialize the starting node.
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0],goal[1]);
    AddToOpen(x, y, g, h, open, grid);

    while(open.size() != 0)
    {
        // TODO: Sort the open list using `CellSort`, and get the current node.
        CellSort(&open);
        vector<int> currNode = open.back();
        open.pop_back();

        // TODO: Get the x and y values from the current node,
        // and set grid[x][y] to kPath.
        int currX = currNode[0];
        int currY = currNode[1];
        grid[currX][currY] = State::kPath;

        // TODO: Check if you've reached the goal. If so, return grid.
        if (currX == goal[0] && currY == goal[1])
        {
            return grid;
        }

        // If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
        ExpandNeighbors(currNode, goal, open, grid);
    }

    cout << "No path found!" << "\n";
    return std::vector<vector<State>> {};
}

string CellString(State cell)
{
    switch(cell)
    {
        case State::kObstacle:
            return "⛰️   ";
        
        case State::kPath: return "🚗   ";
        case State::kStart: return "🚦   ";
        case State::kFinish: return "🏁   ";
        default:
            return "0   ";
    }
}

void PrintBoard(vector<vector<State>> board)
{
    // for (auto v : board)
    // {
    //     for(int i : v)
    //     {
    //         cout << i;
    //     }
    //     cout << "\n";
    // }
    
    // other option to use size 
    for (int i = 0; i < board.size(); i++) 
    {
        for (int j = 0; j < board[i].size(); j++) 
        {
            string cell = CellString(board[i][j]);
            cout << cell;
        }
        cout << "\n";
    }
}

/*
    Main
*/
int main()
{

    // vector<vector<int>> init{0,0};
    // vector<vector<int>> goal{4,5};
  int init[2]{0, 0};
  int goal[2]{4, 5};
    // vector<vector<State>> board = ReadBoardFile("1.board");
    auto board = ReadBoardFile("1.board");
    PrintBoard(board);

    vector<vector<State>> solution = Search(board, init, goal);
}
