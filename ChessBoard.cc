#include<iostream>
#include<cstdlib>
#include"ChessBoard.h"

using namespace std;

//************************************************************************

// Piece Class Member Functions

//************************************************************************

char Piece::get_colour(){
    return colour;
}

//************************************************************************

// Castle Class Member Functions

//************************************************************************

bool Castle::valid_move(int start_col, int start_row, int dest_col, int dest_row){
// Q: dont have the override in the implementation?

    // Moving horizontally
    if ( start_row == dest_row && start_col != dest_col ){
        return true;
    }

    // Moving vertically
    if ( start_col == dest_col && start_row != dest_row ){
        return true;
    }

    // No other moves are valid
    return false;

}

//************************************************************************

// Knight Class Member Functions

//************************************************************************

bool Knight::valid_move(int start_col, int start_row, int dest_col, int dest_row){

    // Moving 2 spaces horizontally & 1 space vertically
    if (dest_row == start_row - 2 || dest_row == start_row + 2){
        if (dest_col == start_col - 1 || dest_col == start_col + 1){
            return true;
        }
    }
    
    // Moving 2 spaces vertically & 1 space horiztonally
    if (dest_col == start_col - 2 || dest_col == start_col + 2){
        if (dest_row == start_row - 1 || dest_row == start_row + 1){
            return true;
        }
    }

    // No other possible moves
    return false;
}

//************************************************************************

// Bishop Class Member Functions

//************************************************************************

bool Bishop::valid_move(int start_col, int start_row, int dest_col, int dest_row){

    // if move diagonally, the difference between start row & destination row should
    // equal the difference between start column & destination column
    if ( abs(start_row - dest_row) == abs(start_col - dest_col) ){
        return true;
    }

    // No other possible moves
    return false;
}

//************************************************************************

// Queen Class Member Functions

//************************************************************************

bool Queen::valid_move(int start_col, int start_row, int dest_col, int dest_row){

    // Moving diagonally
    if ( abs(start_row - dest_row) == abs(start_col - dest_col) ){
        return true;
    }

    // Moving horizontally
    if ( start_row == dest_row && start_col != dest_col ){
        return true;
    }

    // Moving vertically
    if ( start_col == dest_col && start_row != dest_row ){
        return true;
    }

    // No other possible moves
    return false;
}

//************************************************************************

// King Class Member Functions

//************************************************************************

bool King::valid_move(int start_col, int start_row, int dest_col, int dest_row){

    // Moving 1 space horizontally
    if ( start_col == dest_col && abs(start_row - dest_row) == 1){
        return true;
    }

    // Moving 1 space vertically
    if ( start_row == dest_row && abs(start_col - dest_col) == 1){
        return true;
    }

    // No other possible moves
    return false;

}

//************************************************************************

// ChessBoard Member Functions:

//************************************************************************


// how make sure they finish in 
void ChessBoard::submitMove(char source_square[3], char destination_square[3]){
// entering a string above should automatically include the sentinel
// Which marks the end of a string

// TESTS FOR ERROR INPUTS

// Convert board positions to index:

int source[2], destination[2];
convert_to_index(source_square, destination_square, source, destination);

}

void ChessBoard::convert_to_index(char source_square[3], char destination_square[3], int source[2], int destination[2]){

    // cout << endl << "inputted source_square " << source_square[0] << source_square[1] << source_square[2];
    // cout << endl << "inputted destination_square " << destination_square[0] << destination_square[1] << destination_square[2];
    // cout << endl;

    // Converts postion from (column,row) to (row, column) making it compatible with our board:

    char inverted_source_square[2], inverted_destination_square[2];

    inverted_source_square[0] = source_square[1];
    inverted_source_square[1] = source_square[0];

    inverted_destination_square[0] = destination_square[1];
    inverted_destination_square[1] = destination_square[0];

    // Converts rank (top to bottom) from 8-1 to 0-7:
    source[0] = (8 - (inverted_source_square[0] - '0'));
    destination[0] = 8 - (inverted_destination_square[0] - '0');

    // Converts file (left to right) from A-Z to 0-7:
    source[1] = inverted_source_square[1] - 'A';
    destination[1] = inverted_destination_square[1] - 'A';

    cout << endl << "Outputted Source Position: " << source[0] << source[1];
    cout << endl << "Outputted Destination Position: " << destination[0] << destination[1];
    cout << endl;

}


void ChessBoard::load_board(Piece* board[8][8]){

  // Bottom white, Top black

  for (int file = 0; file < 8; file++){

    // Pawns
    board[1][file] = new Pawn('B');

    board[7][file] = new Pawn('W');

    // Set unfilled positions to NULL
    for (int rank = 2; rank < 6; rank++){
      board[rank][file] = NULL;
    }
  }

  // Castles
  board[0][0] = new Castle('B');
  board[0][7] = new Castle('B');

  board[7][0] = new Castle('W');
  board[7][7] = new Castle('W');

  // Knights
  board[0][1] = new Knight('B');
  board[0][6] = new Knight('B');

  board[7][1] = new Knight('W');
  board[7][6] = new Knight('W');

  // Bishops
  board[0][2] = new Bishop('B');
  board[0][5] = new Bishop('B');

  board[7][2] = new Bishop('W');
  board[7][5] = new Bishop('W');

  // Queens
  board[0][3] = new Queen('B');
  board[7][3] = new Queen('W');

  // Kings
  board[0][4] = new King('B');
  board[7][4] = new King('W');

}