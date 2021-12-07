#include<iostream>
#include<cstdlib>
#include"ChessBoard.h"

using namespace std;

//************************************************************************

// ChessBoard Member Functions:

//************************************************************************

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

  // Rooks
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
  board[0][4] = new Queen('B');
  board[7][3] = new Queen('W');

  // Kings
  board[0][3] = new King('B');
  board[7][4] = new King('W');

}

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

// Bishop Class

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