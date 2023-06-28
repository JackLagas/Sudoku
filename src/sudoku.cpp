#include "sudoku.h"
#include <iostream>
#include <ncurses.h>
#include <algorithm>

Sudoku::Sudoku(): board{
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 0, 8, 5,
        0, 0, 1, 0, 2, 0, 0, 0, 0,
        0, 0, 0, 5, 0, 7, 0, 0, 0,
        0, 0, 4, 0, 0, 0, 1, 0, 0,
        0, 9, 0, 0, 0, 0, 0, 0, 0,
        5, 0, 0, 0, 0, 0, 0, 7, 3,
        0, 0, 2, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 4, 0, 0, 0, 9
    }{
    cursorX = 0;
    cursorY = 0;
    InitializeBoard();

}

void Sudoku::InitializeBoard(){

    board = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 0, 8, 5,
        0, 0, 1, 0, 2, 0, 0, 0, 0,
        0, 0, 0, 5, 0, 7, 0, 0, 0,
        0, 0, 4, 0, 0, 0, 1, 0, 0,
        0, 9, 0, 0, 0, 0, 0, 0, 0,
        5, 0, 0, 0, 0, 0, 0, 7, 3,
        0, 0, 2, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 4, 0, 0, 0, 9
    };
    for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        lockedBoard[i] = board[i] != 0;
        errorBoard[i] = false;
    }
}

void Sudoku::DisplayBoard(){

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            std::cout << " " << ((board[9 * i + j] == 0) ? " " : std::to_string(board[9 * i + j])) << " ";
            if ((j + 1) % 3 == 0 && j != 8)
                std::cout << " | ";
        }
        std::cout << std::endl;
        if ((i + 1) % 3 == 0 && i != 8)
            for(int j = 0; j < BOARD_SIZE + 2; j++)
                std::cout << "---";
            std::cout << std::endl;
            
    }
}

void Sudoku::DisplayNCurses(){
    initscr();
    WINDOW* windows[9];
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    int k = 0;
    // Create all windows
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            windows[k] = newwin(9, 15, 9 * i, 15 * j);
            k++;
        }
    }
    // Make boxes from windows
    for(int i = 0; i < 9; i++){
        box(windows[i], 0, 0);
    }
    refresh();
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){

            if(errorBoard[9 * i + j]) wattron(windows[3 * (i / 3) + (j / 3)], COLOR_PAIR(1));
            mvwprintw(
                windows[3 * (i / 3) + (j / 3)], // Get the index of the relevent board
                (3 * i + 1) % 9,  // Get each position in board
                (5 * j + 2) % 15, // ^^^
                ((board[9 * i + j] == 0) ? " " : std::to_string(board[9 * i + j]).c_str())    // Substitue 0 for empty space and convert to c string
            );
            if(errorBoard[9 * i + j]) wattroff(windows[3 * (i / 3) + (j / 3)], COLOR_PAIR(1));
        }
    }

    move(3 * cursorY + 1, 5 * cursorX + 2);

    // Refresh windows
    for(int i = 0; i < 9; i++){
        wrefresh(windows[i]);
    }
    
   
}

void Sudoku::GetInput(){
    keypad(stdscr, TRUE);   // Don't really know what this does but it makes the code work so...
    int key = getch();
    //clear();

    switch(key){
        case KEY_RIGHT:
            cursorX++;
            if(cursorX > 8)
                cursorX = 0;
            break;
        case KEY_LEFT:
            cursorX--;
            if(cursorX < 0)
                cursorX = 8;
            break;
        case KEY_UP:
            cursorY--;
            if(cursorY < 0)
                cursorY = 8;
            break;
        case KEY_DOWN:
            cursorY++;
            if(cursorY > 8)
                cursorY = 0;
            break;
        default:
            if(isdigit(key)){
                if(!lockedBoard[9 * cursorY + cursorX])
                    board[9 * cursorY + cursorX] = key - 48;  //48 is the char offset to get the of the number characters
                    CheckBoard();
            }
    }

}

bool Sudoku::IsPositionValid(int index){

    int x = index % 9;
    int y = index / 9;

    // ROWS
    for(int i = 0; i < BOARD_SIZE; i++){
        if(board[9 * y + i] == board[9 * y + x] && i != x && board[9 * y + i] != 0)
            return false;
    }

    //COLUMNS
    for(int i = 0; i < BOARD_SIZE; i++){
        if(board[9 * i + x] == board[9 * y + x] && i != y && board[9 * i + x] != 0)
            return false;
    }

    // BOXES
    int xBoxStart = 3 * (x / 3);
    int yBoxStart = 3 * (y / 3);
    for(int i = xBoxStart; i < xBoxStart + 3; i++){
        for(int j = yBoxStart; j < yBoxStart + 3; j++){
            if(board[9 * j + i] == board[9 * y + x] && (9 * j + i) != (9 * y + x) && board[9 * j + i] != 0)
                return false;
        }
    }
    return true;

}

void Sudoku::CheckBoard(){
    for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        errorBoard[i] = !IsPositionValid(i);
    }
}

bool Sudoku::HasWon(){
    for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        if (board[i] == 0) 
            return false;
        if (errorBoard[i])
            return false;
    }
    return true;
}

void Sudoku::Run(){
    
    while(!HasWon()){
        DisplayNCurses();
        GetInput();
    }
    endwin();
}


