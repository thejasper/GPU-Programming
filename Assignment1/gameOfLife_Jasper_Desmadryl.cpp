#include <iostream>
#include <vector>
#include <fstream>

#define HARD_CODED_PATH

#define ALIVE 1
#define DEAD 0

// Size of the array on the stack
#define DIM 10 * 10

using namespace std;

// Jasper Desmadryl

/* Why is the array passed to the printLife1 function const?
 * It's an indication that printLife1 does not modify the array 'board'.
 *
 * Why is one array passed to the playLife1 function not const?
 * It's the array that contains the result. If it would be constant it would be 
 * impossible to return the result to the caller (the function returns nothing).
 *
 * Do we need to pass both the number of rows and columns into the printLife1 and playLife1 functions?
 * Yes, beside knowing how much elements there are in the array (numRows*numCols), 
 * you need to know how much elements there are in each row.
 *
 * Why is there an "&" in front of playLife2's board? Is it necessary?
 * Yes it's necessary to pass a reference. Without the '&' it's impossible to change
 * the values in the vector and getting them back to the caller.
 * If you don't pass by reference, a copy is created before passing board to playLife2.
 * Note: In printLife2 it's not necessary but it would be more efficient to use a reference.
 *
 * Is it necessary for playLife3 to return a bool** to evolve the game of life board? Why or why not?
 * It's not necessary, you could change the value of the argument 'board'. You just
 * have to watch out all memory gets deallocated correctly.
 */

// Function prototypes
void printLife1(const bool *board, int nRows, int nCols);  
void printLife2(vector< vector< bool > > board);
void printLife3(bool **board, int nRows, int nCols);  
void playLife1(const bool *board, int nRows, int nCols, bool *board2);
void playLife2(vector< vector< bool > > &board);
bool** playLife3(bool **board, int nRows, int nCols);

// offsets to get the surrounding cells, starting in upper left corner and going clockwise
int dr[] = { -1, -1, -1, 0, 1, 1, 1, 0};
int dc[] = { -1, 0, 1, 1, 1, 0, -1, -1};

int main(int argc, char* argv[])
{
#ifdef HARD_CODED_PATH
    argv[1] = (char*)"LifeZero4.in.txt";
#else
    if (argc < 2) {
        cout << "Not enough arguments. Usage: ./gameOfLife [pattern file]" << endl;
        return 1;
    }
#endif

    ifstream input(argv[1], ios::in);

    if (!input) {
        cout << "File not found." << endl;
        return 1;
    }

	int times;
    cout << "How many times do you want to evolve the game of life? ";
    cin >> times;

    // Read in dimensions and board from input file
    int numRows, numCols;
    input >> numRows >> numCols;
    int numElements = numRows * numCols;

    bool grid1[DIM]; // PART 1
    vector< vector<bool> > grid2(numRows, vector<bool>(numCols)); // PART 2
    bool** grid3 = new bool*[numRows]; // PART 3

    for (int i = 0; i < numRows; ++i) {
        grid3[i] = new bool[numCols];

        for (int j = 0; j < numCols; ++j) {
            char c;
            input >> c;

            bool val = (c == '*') ? ALIVE : DEAD;

            grid1[i * numCols + j] = val;
            grid2[i][j] = val;
            grid3[i][j] = val;
        }
    }

    /* PART 1) Use a 1D array to model a 2d game board using pointers.  No dynamic allocation.
     * For print function USE pointer arithmetic to go through the array!
     */
    cout << endl << "Game of life with one dimensional array!" << endl;
    cout << "----------------------------------------" << endl;

    printLife1(grid1, numRows, numCols);
    for (int i = 0; i < times; ++i) {
        bool newState[DIM];
        playLife1(grid1, numRows, numCols, newState);

        copy(newState, newState + numElements, grid1);

        printLife1(grid1, numRows, numCols);
    }


    /* PART 2) Solve same problem, but with vectors, and use iterator for print function.
     * No dynamic allocation!
     * Play the game of life take 2!
     */
    cout << endl << "Game of life with vectors!" << endl;
    cout << "--------------------------" << endl;

    printLife2(grid2);
    for (int i = 0; i < times; ++i) {
        playLife2(grid2);
        printLife2(grid2);
    }

    /* PART 3) Same problem, and now you can finally use dynamic allocation!  Use 2d
     * array with bool**.  Make sure each new is paired with a delete - don't leak memory!
     * Also, notice the playLife function returns its result array.
     */
    cout << endl << "Game of life with two dimenional array dynamically allocated!" << endl;
    cout << "-------------------------------------------------------------" << endl;

    printLife3(grid3, numRows, numCols);
    for (int i = 0; i < times; ++i) {
        bool** newState = playLife3(grid3, numRows, numCols);

        for (int j = 0; j < numRows; ++j) {
            delete[] grid3[j];
        }
        delete[] grid3;

        grid3 = newState;
        printLife3(grid3, numRows, numCols);
    }

    // cleanup
    for (int j = 0; j < numRows; ++j) {
        delete[] grid3[j];
    }
    delete[] grid3;

    return 0;
}

void printLife1(const bool *board, int nRows, int nCols)
{
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            if (*board++ == ALIVE)
                cout << "* ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

void printLife2(vector< vector< bool > > board)
{
    for (vector< vector<bool> >::const_iterator row = board.begin(); row != board.end(); ++row) {
        for (vector<bool>::const_iterator col = row->begin(); col != row->end(); ++col) {
            if (*col == ALIVE)
                cout << "* ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

void printLife3(bool **board, int nRows, int nCols)
{
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            if (board[i][j] == ALIVE)
                cout << "* ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

void playLife1(const bool *board, int nRows, int nCols, bool *board2)
{
    int n = nRows * nCols;

    // iterate cells, count neighbours and update state according to the rules
    for (int i = 0; i < n; ++i) {

        int aliveCount = 0;

        int row = i / nCols;
        int col = i % nCols;

        for (int k = 0; k < 8; ++k) {
            int nr = row + dr[k];
            int nc = col + dc[k];

            if (nr < 0 || nc < 0 || nr >= nRows || nc >= nCols)
                continue;

            if (board[nr*nCols + nc] == ALIVE)
                ++aliveCount;
        }

        board2[i] = board[i];

        if (board[i] == ALIVE && (aliveCount < 2 || aliveCount > 3)) {
            board2[i] = DEAD;
        } else if (board[i] == DEAD && aliveCount == 3) {
            board2[i] = ALIVE;
        }
    }
}

void playLife2(vector< vector< bool > > &board)
{
    int m = board.size();
    int n = board[0].size();

    vector< vector<bool> > newState(m, vector<bool>(n));

    // iterate cells, count neighbours and update state according to the rules
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {

            int aliveCount = 0;

            for (int k = 0; k < 8; ++k) {
                int nr = i + dr[k];
                int nc = j + dc[k];

                if (nr < 0 || nc < 0 || nr >= m || nc >= n)
                    continue;

                if (board[nr][nc] == ALIVE)
                    ++aliveCount;
            }

            newState[i][j] = board[i][j];

            if (board[i][j] == ALIVE && (aliveCount < 2 || aliveCount > 3)) {
                newState[i][j] = DEAD;
            } else if (board[i][j] == DEAD && aliveCount == 3) {
                newState[i][j] = ALIVE;
            }
        }
    }

    board = newState;
}

bool** playLife3(bool **board, int nRows, int nCols)
{
    bool** newState = new bool*[nRows];

    // iterate cells, count neighbours and update state according to the rules
    for (int i = 0; i < nRows; ++i) {
        newState[i] = new bool[nCols];

        for (int j = 0; j < nCols; ++j) {

            int aliveCount = 0;

            for (int k = 0; k < 8; ++k) {
                int nr = i + dr[k];
                int nc = j + dc[k];

                if (nr < 0 || nc < 0 || nr >= nRows || nc >= nCols)
                    continue;

                if (board[nr][nc] == ALIVE)
                    ++aliveCount;
            }

            newState[i][j] = board[i][j];

            if (board[i][j] == ALIVE && (aliveCount < 2 || aliveCount > 3)) {
                newState[i][j] = DEAD;
            } else if (board[i][j] == DEAD && aliveCount == 3) {
                newState[i][j] = ALIVE;
            }
        }
    }

    return newState;
}

