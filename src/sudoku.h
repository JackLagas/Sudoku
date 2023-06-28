#include <array>

#define BOARD_SIZE 9

class Sudoku{
private:

    std::array<int, BOARD_SIZE * BOARD_SIZE> board;
    std::array<bool, BOARD_SIZE * BOARD_SIZE> lockedBoard;
    std::array<bool, BOARD_SIZE * BOARD_SIZE> errorBoard;
    int cursorX, cursorY;


    void InitializeBoard();
    void DisplayBoard();
    void DisplayNCurses();
    void GetInput();
    bool IsPositionValid(int index);
    void CheckBoard();
    bool HasWon();

public:


    Sudoku();
   
    void Run();


};