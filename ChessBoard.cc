#include<iostream>
#include<cstdlib>

#include"ChessBoard.h"
#include"pawn.h"
#include"castle.h"
#include"bishop.h"
#include"knight.h"
#include"king.h"
#include"queen.h"

using namespace std;

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

bool ChessBoard::valid_move(int start_row, int start_col, int dest_row, int dest_col){

    // Invalid if no piece at source square
    if (board[start_row][start_col] == nullptr){
        return false;
    }

    // King, (kings legal function must make sure it does not move into check)

    // All other pieces
    if ( board[start_row][start_col]->possible_move(start_col, start_row, dest_col, dest_row) && 
         board[start_row][start_col]->legal_move(start_row, start_col, dest_row, dest_col, board)){

            //  if (board[start_row][start_col]->colour == 'B' && check(B_king_pos)){
            //      return false;
            //  }

            // if (board[start_row][start_col]->colour == 'B' && check(B_king_pos)){
            //      return false;
            //  }

            //  // if that puts own king in check, return false
            //  // else return true

        return true;
    }

    return false;
}

// iterates through the whole board and sees what pieces can hit the kings ciurrent location
bool ChessBoard::check(int king_pos[2]){
    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j ++){
            // Only checking opposition pieces
            if ( board[i][j] != nullptr && board[i][j]->colour != board[king_pos[0]][king_pos[1]]->colour){
                if ( valid_move(i, j, king_pos[0], king_pos[1]) ){
                return true;
                }
            }
        }
    }
    return false;
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
//   board[0][1] = new Knight('B', 'ḵ');
//   board[0][6] = new Knight('B', 'ḵ');

//   board[7][1] = new Knight('W', 'ḵ');
//   board[7][6] = new Knight('W', 'ḵ');

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
    board[1][file] = nullptr;
    board[6][file] = nullptr;

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
  board[0][1] = new Knight('B', 'c');
  board[0][6] = new Knight('B', 'c');

  board[7][1] = new Knight('W', 'c');
  board[7][6] = new Knight('W', 'c');

  // Bishops
  board[0][2] = new Bishop('B', 'B');
  board[0][5] = new Bishop('B', 'B');

  board[7][2] = new Bishop('W', 'B');
  board[7][5] = new Bishop('W', 'B');

  // Queens
  board[0][3] = new Queen('B', 'Q');
  board[7][3] = new Queen('W', 'Q');
  board[5][2] = new Queen('B', 'Q');

  // Kings
  board[0][4] = new King('B', 'K', 0, 4);
  board[5][5] = new King('W', 'K', 7, 4);

  board[1][7] = new Pawn('B', 'P');
  board[5][3] = new Pawn('B', 'P');
  board[1][3] = new Pawn('B', 'P');
//   board[4][5] = new Knight('B', 'c');

  board[7][4] = nullptr;

  board[4][5] = new Pawn('B', 'P');
  board[4][6] = new Queen('W', 'P');
  board[5][6] = new Bishop('B', 'P');
  board[6][6] = new Knight('W', 'P');
  board[6][5] = new Pawn('W', 'P');
  board[5][4] = new Bishop('B', 'P');
  board[6][4] = new Knight('B', 'P');
  board[4][4] = new Pawn('B', 'P');

}