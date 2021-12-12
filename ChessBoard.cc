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

    // int turn_count = 0 // AFTER EACH ALLOWED MOVE, INCREMEMNT BY 1 AND MODULUS RESULT BY 2

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

    // Invalid if moving to same square
    if ( start_row == dest_row && start_col == dest_col ){
        return false;
    }

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
bool ChessBoard::check(int king_row, int king_col, int turn_count){

    char user_colour;
    char opponent_colour;

    // i.e. if white turn
    if (turn_count == 0){
        user_colour = 'W';
        opponent_colour = 'B';
    }

    // i.e. if black turn
    else{
        user_colour = 'B';
        opponent_colour = 'W';
    }

    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j ++){
            // Checking all pieces (legal moves prevents piece taking own colour)
            // user needs to be told if they're king in check or check mate, i.e. whether opponents moves can hit it
            // checking whether opponents piece can hit users king
            if ( board[i][j] != nullptr  && board[i][j]->colour == opponent_colour ){ // THIS MIGHT LEAD TO ERRORS DEPENDING ON HOW USE CHECK 
                cout << endl << "position: " << i << " " << j << " has a piece of colour: " << opponent_colour << endl; 
                if ( valid_move(i, j, king_row, king_col) ){
                return true;
                }
            }
        }
    }
    return false;
}

// If there is an adjacent square to the king that is not in check, return false
bool ChessBoard::adjacent_squares_check(int king_row, int king_col, int turn_count){

    // Space above
    if ( king_row != 0 ){
        
        // Space above
        // If the space above is not in check, 
        // then the king has a space to move to if in check
        // so adjacent squares are not all in check, i.e. return false
        if ( valid_move(king_row, king_col, king_row - 1, king_col)){

            cout << endl << "Valid move above...";
            cout << endl << "to row: " << (king_row-1) << " column: " << king_col << endl << endl;

            move_piece(king_row, king_col, king_row - 1, king_col);
            // move is valid, now must temporarily update board accordingly before running check 
            // on this would be square
            // so we need a function that updates the position
            // and another function that returns it to the original state

            print_board();

            if ( !check( king_row - 1, king_col, turn_count ) ){
            cout << endl <<  "Not in check..." << endl;
            return false;
            }
        }
    }

     // space above diagonally to left
    if ( king_row != 0 || king_col != 0 ){ 

        if ( valid_move(king_row, king_col, king_row - 1, king_col -1 ) ){
        
            move_piece(king_row, king_col, king_row - 1, king_col - 1);

            if( !check( king_row - 1, king_col - 1, turn_count ) ){
            cout << endl << "can move above diagonally left!" << endl;
            return false;
             }
        }
    }

    // space above diagonally to right
    if ( king_row != 0 || king_col != 7 ){

        if ( valid_move(king_row, king_col, king_row - 1, king_col + 1) ){ 
            
            move_piece(king_row, king_col, king_row - 1, king_col + 1);
            
            if (!check( king_row - 1, king_col + 1, turn_count) ){
            cout << endl << "can move above diagonally right!" << endl;
            return false;
            }
        }
    }

    // space to left
    if ( king_col != 0 ){

        if ( valid_move(king_row, king_col, king_row, king_col - 1) ){
            
            move_piece(king_row, king_col, king_row, king_col - 1);
            
            if ( !check( king_row, king_col - 1, turn_count) ){
            cout << endl << "can move left!" << endl;
            return false;
            }
        }
    }

    // space to right
    if ( king_col != 7 ){
        cout << endl << "king col not equal to 7" << endl;
        if ( valid_move(king_row, king_col, king_row, king_col + 1) ){

            move_piece(king_row, king_col, king_row, king_col + 1);

            cout << endl << "move is valid..." << endl;
            cout << "neighbour row " << king_row << " & column " << (king_col+1);
            if ( !check( king_row, king_col + 1, turn_count) == false ){
            cout << endl << "can move right!" << endl;
            return false;
            }
        }
    }

    // space below diagonally to left
    if ( king_row != 7 || king_col != 0 ){

        if ( valid_move(king_row, king_col, king_row + 1, king_col - 1) ){

            move_piece(king_row, king_col, king_row + 1, king_col - 1);

            if ( !check( king_row + 1, king_col - 1, turn_count ) ){
            cout << endl << "can down diagonally left!" << endl;
            return false;
            }
        }
    }

    // space below diagonally to right
    if ( king_row != 7 || king_col != 7 ){

        if ( valid_move(king_row, king_col, king_row + 1, king_col + 1) ){
            
            move_piece(king_row, king_col, king_row + 1, king_col + 1);

            if ( !check( king_row + 1, king_col + 1, turn_count ) ){
                cout << endl << "can move down diagonally right!" << endl;
                return false;
            }
        }
    }

    // space below
    if ( king_row != 7 ){
        
        if ( valid_move(king_row, king_col, king_row + 1, king_col) ){
            
            
            if ( !check( king_row + 1, king_col, turn_count) ){
                cout << endl << "can move below!" << endl;
                return false;
            }
        }
    }

    // If all adjacent squares in check
    cout << endl << endl << "we can conclude that all adjacent squares to the king are in check!" << endl;
    return true;
}

void ChessBoard::move_piece(int start_row, int start_col, int dest_row, int dest_col){

    char piece_type = board[start_row][start_col]->get_piece_type();
    char colour = board[start_row][start_col]->get_colour();

    board[start_row][start_col] = nullptr;

    // Pawns
    if ( colour == 'B' && piece_type == 'P'){
        board[dest_row][dest_col] = new Pawn(colour, piece_type);
    }
    if ( colour == 'W' && piece_type == 'P'){
        board[dest_row][dest_col] = new Pawn(colour, piece_type);
    }

    // Castles
    if ( colour == 'B' && piece_type == 'C'){
        board[dest_row][dest_col] = new Castle(colour, piece_type);
    }
    if ( colour == 'W' && piece_type == 'C'){
        board[dest_row][dest_col] = new Castle(colour, piece_type);
    }

    // Knights
    if ( colour == 'B' && piece_type == 'c'){
        board[dest_row][dest_col] = new Knight(colour, piece_type);
    }
    if ( colour == 'W' && piece_type == 'c'){
        board[dest_row][dest_col] = new Knight(colour, piece_type);
    }

    // Bishops
    if ( colour == 'B' && piece_type == 'B'){
        board[dest_row][dest_col] = new Bishop(colour, piece_type);
    }
    if ( colour == 'W' && piece_type == 'B'){
        board[dest_row][dest_col] = new Bishop(colour, piece_type);
    }

    // Queens 
    if ( colour == 'B' && piece_type == 'Q'){
        board[dest_row][dest_col] = new Queen(colour, piece_type);
    }
    if ( colour == 'W' && piece_type == 'Q'){
        board[dest_row][dest_col] = new Queen(colour, piece_type);
    }

    // Kings
    if ( colour == 'B' && piece_type == 'K'){
        board[dest_row][dest_col] = new King(colour, piece_type);
    }
    if ( colour == 'W' && piece_type == 'K'){
        board[dest_row][dest_col] = new King(colour, piece_type);
    }

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
//   board[0][1] = new Knight('B', 'c');
//   board[0][6] = new Knight('B', 'c');

//   board[7][1] = new Knight('W', 'c');
//   board[7][6] = new Knight('W', 'c');

//   // Bishops
//   board[0][2] = new Bishop('B', 'B');
//   board[0][5] = new Bishop('B', 'B');

//   board[7][2] = new Bishop('W', 'B');
//   board[7][5] = new Bishop('W', 'B');

//   // Queens
//   board[0][3] = new Queen('B', 'Q');
//   board[7][3] = new Queen('W', 'Q');

//   // Kings
//   board[0][4] = new King('B', 'K');
//   board[7][4] = new King('W', 'K');

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

  // Kings
  board[0][4] = new King('B', 'K');
  board[7][4] = new King('W', 'K');
  board[3][3] = new King('W', 'K');

  board[2][2] = new Pawn('B', 'P');
  board[2][3] = nullptr;
  board[2][4] = new Pawn('B', 'P');
  board[3][2] = new Pawn('B', 'P');
  board[3][4] = new Pawn('B', 'P');
  board[4][2] = new Pawn('B', 'P');
  board[4][3] = new Pawn('B', 'P');
  board[4][4] = new Pawn('B', 'P');

}