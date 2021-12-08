#include<iostream>
#include<cstdlib>

#include"ChessBoard.h"
// #include"piece.h"

using namespace std;

//************************************************************************

// Piece Class Member Functions

//************************************************************************

char Piece::get_colour(){
    return colour;
}

char Piece::get_piece_type(){
    return piece_type;
};

bool Piece::legal_right(int row, int start_col, int dest_col, Piece* board[8][8]){

    cout << endl <<  "hi" << endl;

    for (int col = (start_col + 1); col < dest_col; col++){

        if (board[row][col] != nullptr){
            cout << "row " << row << " column " << col << " has a piece in it!" << endl;
            return false;
        }
        cout << "row " << row << " column " << col << " doesn't have a piece in it!" << endl;
    }
    return true;
}

bool Piece::legal_left(int row, int start_col, int dest_col, Piece* board[8][8]){

    for (int col = (start_col - 1); col > dest_col; col--){

        if (board[row][col] != nullptr){
                return false;
        }
    }
    return true;
}

bool Piece::legal_up(int start_row, int dest_row, int col, Piece* board[8][8]){
    for (int row = (start_row - 1); row > dest_row; row--){

            if (board[row][col] != nullptr){
                return false;
            }
    }
    return true;
}

bool Piece::legal_down(int start_row, int dest_row, int col, Piece* board[8][8]){
    for (int row = (start_row + 1); row < dest_row; row++){
        
            if (board[row][col] != nullptr){
                cout << "row " << row << " column " << col << " has a piece in it!" << endl;
                return false;
            }
        cout << "row " << row << " column " << col << " doesn't have a piece in it!" << endl;
        }
    return true;
}

bool Piece::legal_right_up_diagonal(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]){
    int steps = abs(dest_row-start_row);
    cout << endl << "steps: " << steps << endl;

    for (int n = 1; n < steps; n++){
        // cout << "value of n: " << n << endl;
        if (board[ (start_row-n) ][ (start_col+n) ] != nullptr){
            cout << "row " << (start_row-n) << " column " << (start_col+n) << " has a piece in it!" << endl;
            return false;
        }
        cout << "row " << (start_row-n) << " column " << (start_col+n) << " doesn't have a piece in it!" << endl;
    }
    return true;
}

bool Piece::legal_left_up_diagonal(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]){
    int steps = abs(dest_row-start_row);
    // cout << endl << "steps: " << steps << endl;

    for (int n = 1; n < steps; n++){
        // cout << "value of n: " << n << endl;
        if (board[ (start_row-n) ][ (start_col-n) ] != nullptr){
            // cout << "row " << (start_row-n) << " column " << (start_col+n) << " has a piece in it!" << endl;
            return false;
        }
        // cout << "row " << (start_row-n) << " column " << (start_col+n) << " doesn't have a piece in it!" << endl;
    }
    return true;
}


//************************************************************************

// Castle Class Member Functions

//************************************************************************

bool Castle::possible_move(int start_col, int start_row, int dest_col, int dest_row){
// Q: dont have the override in the implementation?

    // Moving horizontally
    if ( start_row == dest_row && start_col != dest_col ){
        return true;
    }

    // Moving vertically
    if ( start_col == dest_col && start_row != dest_row ){
        return true;
    }

    // No other moves are possible
    return false;

}

// WORKS
bool Castle::legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]){

    // Not taking own piece
    if ( board[dest_row][dest_col] != nullptr &&
         board[start_row][start_col]->colour == board[dest_row][dest_col]->colour ){
        cout << endl << "landed on piece with same colour" << endl;
        return false;
    }

    // Checking no pieces in path:

    // When moving right
    if ( start_row == dest_row && dest_col > start_col) {
        cout << endl << "moving right!" << endl;
        return legal_right(dest_row, start_col, dest_col, board);
    }

     // When moving left
    if ( start_row == dest_row && dest_col < start_col) {
        cout << endl << "moving left!" << endl;
        return legal_right(start_col, dest_col, dest_row, board);
    }

    // When moving up
    if ( start_col == dest_col && dest_row < start_row) {
        cout << endl << "moving up!" << endl;
        return legal_up(start_row, dest_row, dest_col, board);
    }

     // When moving down
    if ( start_col == dest_col && dest_row > start_row) {
        cout << endl << "moving down!" << endl;
        return legal_down(start_row, dest_row, dest_col, board);
    }
    cout << endl << "Problem - not moving vertically or horizontally!" << endl;
}

//************************************************************************

// Knight Class Member Functions

//************************************************************************

bool Knight::possible_move(int start_col, int start_row, int dest_col, int dest_row){

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
    return false;// Not taking own piece
    // if ( board[start_row][start_col]->colour == board[dest_row][dest_col]->colour ){
    //     return false;
    // }
}

//************************************************************************

// Bishop Class Member Functions

//************************************************************************

bool Bishop::possible_move(int start_col, int start_row, int dest_col, int dest_row){

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

bool Queen::possible_move(int start_col, int start_row, int dest_col, int dest_row){

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

bool King::possible_move(int start_col, int start_row, int dest_col, int dest_row){

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

void ChessBoard::print_board(){

cout << "\n     0  1  2  3  4  5  6  7 ";
cout << "\n  * * * * * * * * * * * * *" << endl;
    for(int i = 0; i<8; i++){
        cout << i << " * ";
        for(int j = 0; j<8; j++){
            if (board[i][j] == nullptr){
                cout << "//" << " ";
            }
            else{
                cout <<board[i][j]->get_colour() << board[i][j]->get_piece_type() << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


// void ChessBoard::load_board(Piece* board[8][8]){

//   // Bottom white, Top black

//   for (int file = 0; file < 8; file++){

//     // Pawns
//     board[1][file] = new Pawn('B', 'P');

//     board[6][file] = new Pawn('W', 'P');

//     // Set unfilled positions to NULL
//     for (int rank = 2; rank < 6; rank++){
//       board[rank][file] = nullptr;
//     }
//   }

//   // Castles
//   board[0][0] = new Castle('B', 'C');
//   board[0][7] = new Castle('B', 'C');

//   board[7][0] = new Castle('W', 'C');
//   board[7][7] = new Castle('W', 'C');

//   // Knights
//   board[0][1] = new Knight('b', 'k');
//   board[0][6] = new Knight('b', 'k');

//   board[7][1] = new Knight('w', 'k');
//   board[7][6] = new Knight('w', 'k');

//   // Bishops
//   board[0][2] = new Bishop('B', 'B');
//   board[0][5] = new Bishop('B', 'B');

//   board[7][2] = new Bishop('W', 'B');
//   board[7][5] = new Bishop('W', 'B');

//   // Queens
//   board[0][3] = new Queen('B', 'Q');
//   board[7][3] = new Queen('W', 'Q');

//   // Kings
//   board[0][4] = new King('B', 'K', 0, 4);
//   board[7][4] = new King('W', 'K', 7, 4);

// }

void ChessBoard::load_test_board(Piece* board[8][8]){

  // Bottom white, Top black

  for (int file = 0; file < 8; file++){

    // Pawns
    board[1][file] = new Pawn('B', 'P');

    board[6][file] = new Pawn('W', 'P');

    // Set unfilled positions to NULL
    for (int rank = 2; rank < 6; rank++){
      board[rank][file] = nullptr;
    }
  }

  // Castles
  board[0][0] = new Castle('B', 'C');
  board[0][7] = new Castle('B', 'C');

  board[7][0] = new Castle('W', 'C');
  board[7][7] = new Castle('W', 'C');

  // Knights
  board[0][1] = new Knight('b', 'k');
  board[0][6] = nullptr;

  board[7][1] = new Knight('w', 'k');
  board[7][6] = new Knight('w', 'k');

  // Bishops
  board[0][2] = new Bishop('B', 'B');
  board[0][5] = new Bishop('B', 'B');

  board[4][1] = new Bishop('W', 'B');
  board[7][2] = new Bishop('W', 'B');
  board[7][5] = new Bishop('W', 'B');

  // Queens
  board[0][3] = new Queen('B', 'Q');
  board[7][3] = new Queen('W', 'Q');

  // Kings
  board[0][4] = new King('B', 'K', 0, 4);
  board[7][4] = new King('W', 'K', 7, 4);

}