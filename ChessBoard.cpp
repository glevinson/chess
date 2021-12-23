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


int ChessBoard::get_turn_count() const{
    return turn_count;
}

void ChessBoard::alternate_turn_count( int turn_count ){
    this->turn_count = ( turn_count + 1 )%2;
}

void ChessBoard::submitMove(string source_square_str, 
                            string destination_square_str){

    // True if destination square is empty
    bool empty_destination = true;
    char source_square[3], destination_square[3];
    char opponent_colour;
    char opponent_piece;

    // Converting source & destination square strings to character arrays
    source_square[0] = source_square_str[0];
    source_square[1] = source_square_str[1];
    source_square[2] = '\0';

    destination_square[0] = destination_square_str[0];
    destination_square[1] = destination_square_str[1];
    destination_square[2] = '\0';

    // COULD CHANGE THIS !
    if (get_turn_count() == 0){
        opponent_colour = 'B';
    }

    if (get_turn_count() == 1){
        opponent_colour = 'W';
    }

    // Convert board positions to index:
    int source[2], destination[2];
    convert_to_index(source_square, destination_square, source, destination);

     // Test if moving a piece
     if ( board[source[0]][source[1]] == nullptr ){
        cout << "There is no piece at position " << source_square[0] 
             << source_square[1] << "!" ;
        return;
    }

     // Test if piece moving is the right colour
    if ( wrong_turn(source[0], source[1], get_turn_count()) ){
        cout << endl << "It is not " << print_piece_colour( (get_turn_count()+1)%2 )
             << "'s turn to move" << endl;
        return;
    }

    // Test if in stalemate
    if ( stalemate( get_turn_count() ) && !check( user_king_pos[0], 
         user_king_pos[1], get_turn_count() ) ){
        cout << endl << "Game over due to stalemate" << endl;
        return;
    }

    if ( valid_move( source[0], source[1], destination[0], destination[1] ) ){

        // Outputting the move to screen
        cout << endl << print_piece_colour(get_turn_count()) << "'s " 
            << print_piece_type(board[source[0]][source[1]]->get_piece_type());

        cout << " moves from " << source_square[0] << source_square[1] 
             << " to " << destination_square[0] << destination_square[1];

        // If taking a piece, outputting that information to screen
        if ( board[ destination[0] ][ destination[1] ] != nullptr ){

            empty_destination = false;
            opponent_piece = 
            board[ destination[0] ][ destination[1] ]->get_piece_type();

            cout << " taking " << print_piece_colour( (get_turn_count()+1)%2 ) 
                 << "'s " ;
            cout << print_piece_type( 
                board[destination[0]][destination[1]]->get_piece_type());
        }


        // Do the move & if piece moving is a King update position accordingly
        move_piece( source[0], source[1], destination[0], destination[1] );
         if ( board[destination[0]][destination[1]]->get_piece_type() == 'K' ){
            user_king_pos[0] = destination[0];
            user_king_pos[1] = destination[1];
        }

        // Undo move if results in user's king being in check & notifies user
        if ( check(user_king_pos[0], user_king_pos[1], get_turn_count())){
            cout << endl << "User's king is in check, invalid move" << endl;
            move_piece( destination[0], destination[1], source[0], source[1] );
            if ( empty_destination == false ){
                insert_piece( destination[0], destination[1], opponent_colour, opponent_piece );
            }

            // If piece moved was a king, updating its position accordingly
            if ( board[source[0]][source[1]]->get_piece_type() == 'K' ){
                user_king_pos[0] = source[0];
                user_king_pos[1] = source[1];
            }
            return;
        }

    }
    else{
        cout << endl << print_piece_colour(get_turn_count()) << "'s " 
             << print_piece_type ( board[ source[0] ][ source[1] ]->get_piece_type() )
             << " cannot move to " << destination_square[0] 
             << destination_square[1] << "!" << endl;
        return;
    }

    // Alternate turn_count
    alternate_turn_count(turn_count);

    // Check if opposition in check-mate
    if ( check_mate( opponent_king_pos[0], opponent_king_pos[1], get_turn_count() )){
        return;
    }

    // Check if the opposition in check
    if ( check( opponent_king_pos[0], opponent_king_pos[1], get_turn_count() ) ){
        cout << endl << print_piece_colour(get_turn_count()) << " is in check";
    }

    // Alternate user & opponent king positions
     int temp_x = opponent_king_pos[0];
     int temp_y = opponent_king_pos[1];

     opponent_king_pos[0] = user_king_pos[0];
     opponent_king_pos[1] = user_king_pos[1];

     user_king_pos[0] = temp_x;
     user_king_pos[1] = temp_y;
}

void ChessBoard::convert_to_index(char source_square[3], char destination_square[3], int source[2], int destination[2]){

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
}

string ChessBoard::print_piece_type(char piece_type){

    // Pawn
    if ( piece_type == 'P' ){
        return "Pawn";;
    }

    // Castle
    if ( piece_type == 'C' ){
        return "Castle";
    }
    
    // Bishop
    if ( piece_type == 'B' ){
        return "Bishop";
    }

    // Knight
    if ( piece_type == 'c' ){
        return "Knight";
    }

    // Queen
     if ( piece_type == 'Q' ){
        return "Queen";
    }

    // King
    return "King";

}

string ChessBoard::print_piece_colour(int turn_count){

    // White
    if ( turn_count == 0 ){
        return "White";
    }

    // Black
    return "Black";
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

    if ( board[start_row][start_col]->possible_move(start_col, start_row, dest_col, dest_row) && 
         board[start_row][start_col]->legal_move(start_row, start_col, dest_row, dest_col, board)){

        return true;
    }

    return false;
}

bool ChessBoard::check(int king_row, int king_col, int turn_count){

    char opponent_colour;

    // i.e. if white turn
    if (turn_count == 0){
        opponent_colour = 'B';
    }

    // i.e. if black turn
    else{
        opponent_colour = 'W';
    }

    /* Iterates through board finding any opposition pieces can 'capture' 
       the user's king */
    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j++){
            if ( board[i][j] != nullptr  && board[i][j]->get_colour() == opponent_colour ){
                if ( valid_move(i, j, king_row, king_col) ){
                    // Threat position updated to threatening opposition piece position
                    threat_position[0] = i;
                    threat_position[1] = j;
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::stalemate( int turn_count ){

    char user_colour;

    if ( turn_count == 0 ){
        user_colour = 'W';
    } 

    else{
        user_colour = 'B';
    }

    // Iterating through the finding every user's piece
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ( board[i][j] != nullptr && board[i][j]->get_colour() == user_colour ){
                // Checks if there is any square on the board that piece at (i,j) can move to
                for (int n = 0; n < 8; n++){
                    for (int m = 0; m < 8; m++){
                        // King cannot move into check
                        if ( board[i][j]->get_piece_type() == 'K' && can_king_move(i,j,n,m,turn_count) ){
                            return false;
                        }
                        // Not stalemate if a valid move exists
                        if ( board[i][j]->get_piece_type() != 'K' && valid_move(i,j,n,m) && i != n && j != m){ 
                            return false;
                        }
                    }
                }
            }
        }
    }
    // If no valid move possible, the user is in stalemate
    return true;
}


bool ChessBoard::check_mate( int king_row, int king_col, int turn_count ){

    char opponent_colour, threat_piece;
    int threat_position[2];

     // True if it is possible to take opposition piece that puts user King in check
    bool can_capture_threat = false;

    if (turn_count == 0){
        opponent_colour = 'B';
    }

    if (turn_count == 1){
        opponent_colour = 'W';
    }

//************************************************
    // King must be in check to be in check-mate
//************************************************

    if ( !check(king_row, king_col, turn_count) ){
        return false;
    }

//***********************************************************
// Can king move into adjacent square without being in check
//***********************************************************
    if ( !adjacent_squares_check(king_row, king_col, turn_count) ){
        return false;
    }

    // Save threat position
    threat_position[0] = this->threat_position[0];
    threat_position[1] = this->threat_position[1];
    threat_piece = board[ threat_position[0] ][ threat_position[1] ]->get_piece_type();

//******************************************
// Can piece threatening the king be taken:
//******************************************

    /* Iterates through whole board to see if there is a user piece that can take 
       the oppositions threatening piece */

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ( board[i][j] != nullptr && board[i][j]->get_piece_type() != 'K' && valid_move( i, j, this->threat_position[0], this->threat_position[1]) ){
                can_capture_threat = true;
                 // temporarily move piece
                move_piece( i, j, this->threat_position[0], this->threat_position[1] );
                // checkmate if check still after a threatening piece is taken
                if ( check( king_row, king_col, turn_count ) ){ 
                    return true;
                }
                // undo move:

                this->threat_position[0] = threat_position[0];
                this->threat_position[1] = threat_position[1];
        
                move_piece ( this->threat_position[0], this->threat_position[1], i, j);
                insert_piece( this->threat_position[0], this->threat_position[1], opponent_colour, threat_piece);
            }

            if (can_capture_threat == true){
                break;
            }

        }

        if (can_capture_threat == true){
            break;
        }

    }

//****************************************************************
// If threatening piece is a knight check-mate after above 2 tests
//****************************************************************

    if (board[threat_position[0]][threat_position[1]]->get_piece_type() == 'c'){
        return true;
    } 

//***********************************
// Can threatening piece be blocked:
//***********************************

    if ( can_block( king_row, king_col, threat_position[0], threat_position[1], turn_count) ){
        
        // Test if still in check after block
        move_piece(blocking_piece_position[0], blocking_piece_position[1], blocking_position[0], blocking_position[1]);
    
        if ( !check( king_row, king_col, turn_count) ){
            // Undo move if not in check
            move_piece(blocking_position[0], blocking_position[1], blocking_piece_position[0], blocking_piece_position[1]);
            return false;
        }

        // check-mate if king still in check after threatening piece blocked
        return true;
    }

    // check-mate if King still in check after above tests
    cout << endl << print_piece_colour(turn_count) << " is in checkmate" << endl;
    return true;
}


bool ChessBoard::can_block( int king_row, int king_col, int threat_row, int threat_col, int turn_count){
    
    int row_diff = abs(king_row - threat_row);
    int col_diff = abs(king_col - threat_col);

    /* Iterates through the spaces inbetween the threatening piece and the king in check & tests 
       if any pieces corresponding to the king's colour can validally move to one of the spaces */

    // Horizontal and at least two squares away (so there is space to block)
    if ( row_diff == 0 && col_diff > 1 ){

        for (int n = 1; n < col_diff; n++){

            // Threat to left
            if (threat_col < king_col){
                if ( can_block_space( king_row, (king_col - n), turn_count) ){
                    blocking_position[0] = king_row;
                    blocking_position[1] = (king_col - n);
                    return true;
                }
            }
            // Threat to right
            if (threat_col > king_col){ 
                if ( can_block_space( king_row, (king_col + n), turn_count) ){
                    blocking_position[0] = king_row;
                    blocking_position[1] = (king_col + n);
                    return true;
                }
            }
        }
    }

    // Vertical and at least two square away
    if ( col_diff == 0 && row_diff > 1 ){

        for (int m = 1; m < row_diff; m++){

            // Threat above
            if ( threat_row < king_row ){
                if ( can_block_space( (king_row - m), king_col, turn_count ) ){
                    blocking_position[0] = (king_row - m);
                    blocking_position[1] = king_col;
                    return true;
                }
            }

            // Threat below
            if ( threat_row > king_row ){
                if ( can_block_space( (king_row + m), king_col, turn_count) ){
                    blocking_position[0] = (king_row + m);
                    blocking_position[1] = king_col;
                    return true;
                }
            }
        }
    }

   // Diagonally

   for ( int w = 1; w < row_diff; w++){

        // above right
        if ( threat_row < king_row && threat_col > king_col ){
            if ( can_block_space( (king_row - w), (king_col + w), turn_count ) ){
                blocking_position[0] = (king_row - w);
                blocking_position[1] = (king_col + w);
                return true;
            }
        }

        // above left
        if ( threat_row < king_row && threat_col < king_col ){
            if ( can_block_space( (king_row - w), (king_col - w), turn_count ) ){
                blocking_position[0] = (king_row - w);
                blocking_position[1] = (king_col - w);
                return true;
            }
        }

        // below right
        if ( threat_row > king_row && threat_col > king_col ){
            if ( can_block_space( (king_row + w), (king_col + w), turn_count ) ){
                blocking_position[0] = (king_row + w);
                blocking_position[1] = (king_col + w);
                return true;
            }
        }

        // below left
        if ( threat_row > king_row && threat_col < king_col ){
            if ( can_block_space( (king_row + w), (king_col - w), turn_count ) ){
                blocking_position[0] = (king_row + w);
                blocking_position[1] = (king_col - w);
                return true;
            }
        }
   }
    return false;
}

bool ChessBoard::can_block_space( int row, int col, int turn_count){

    char blocking_colour;

    if (turn_count == 0){
        blocking_colour = 'W';
    }

    if (turn_count == 1){
        blocking_colour = 'B';
    }

    /* Iterates through whole board, returning true if it finds a piece of the same colour 
       as the current turns king that could move to the square "(row, col)" */

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){

            if ( board[i][j] != nullptr && board[i][j]->get_piece_type() != 'K' 
                 && board[i][j]->get_colour() == blocking_colour  && valid_move( i, j, row, col ) ){
                blocking_piece_position[0] = i;
                blocking_piece_position[1] = j;
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::can_king_move( int king_row, int king_col, int dest_row, int dest_col, int turn_count){

    char opponent_colour, opponent_piece;
    // True if destination square is empty
    bool space_empty = false;

    // Saving the threat positions as moving the King below will distort them
    int threat_position[2];
    threat_position[0] = this->threat_position[0];
    threat_position[1] = this->threat_position[1];

    if (board[dest_row][dest_col] == nullptr){
        space_empty = true;
    }

    if (turn_count == 0){
        opponent_colour = 'B';
    }

    if (turn_count == 1){
        opponent_colour = 'W';
    }
    
    // Check if adjacent space is a valid move
    if ( valid_move( king_row, king_col, dest_row, dest_col) ){
        
        if (space_empty == false){
            opponent_piece = board[dest_row][dest_col]->get_piece_type();
        }
        // Temporarily move king into space
        move_piece(king_row, king_col, dest_row, dest_col);
        // Check if King in that space is now in check
        if ( !check( dest_row, dest_col, turn_count ) ){
            // Move King back
            move_piece(dest_row, dest_col, king_row, king_col);
            // Put piece in adjacent back
            if (space_empty == false){
                insert_piece(dest_row, dest_col, opponent_colour, opponent_piece );
            }
            // Update threat position to orignal values
            this->threat_position[0] = threat_position[0];
            this->threat_position[1] = threat_position[1];

            return true;
        }
        // Undo move
        move_piece(dest_row, dest_col, king_row, king_col);
        if (space_empty == false){
                insert_piece(dest_row, dest_col, opponent_colour, opponent_piece );
            }
    }
    // Update threat position to orignal values
    this->threat_position[0] = threat_position[0];
    this->threat_position[1] = threat_position[1];
    return false;
}

bool ChessBoard::adjacent_squares_check(int king_row, int king_col, int turn_count){
    
    /* If there is an adjacent square to the King that it can move to without being in check,
       then not all the squares adjacent to the King are in check; function returns false */

    // Space above
    if ( king_row != 0 && can_king_move(king_row, king_col, king_row - 1, king_col, turn_count) ){
        return false;
    }

     // space above diagonally to left
    if ( ( king_row != 0 && king_col != 0 ) && can_king_move(king_row, king_col, king_row - 1, king_col - 1, turn_count)){
        return false;
    }

    // space above diagonally to right
    if ( ( king_row != 0 && king_col != 7 ) && can_king_move(king_row, king_col, king_row - 1, king_col + 1, turn_count)){
        return false;
    }

    // space to left
    if ( king_col != 0 && can_king_move(king_row, king_col, king_row, king_col - 1, turn_count) ){
        return false;
    }

    // space to right
    if ( king_col != 7 && can_king_move(king_row, king_col, king_row, king_col + 1, turn_count)){
        return false;
    }

    // space below diagonally to left
    if ( ( king_row != 7 && king_col != 0 ) && can_king_move(king_row, king_col, king_row + 1, king_col - 1, turn_count)){
        return false;
    }

    // space below diagonally to right
    if (( king_row != 7 && king_col != 7 ) && can_king_move(king_row, king_col, king_row + 1, king_col + 1, turn_count)){
        return false;
    }

    // space below
    if ( king_row != 7 && can_king_move(king_row, king_col, king_row + 1, king_col, turn_count)){
        return false;
    }

    // If all adjacent squares in check
    return true;
}

void ChessBoard::insert_piece(int dest_row, int dest_col, char colour, char piece_type){
   
    // Pawn
    if ( piece_type == 'P'){
        board[dest_row][dest_col] = new Pawn(colour, piece_type);
    }

    // Castle
    if ( piece_type == 'C'){
        board[dest_row][dest_col] = new Castle(colour, piece_type);
    }

    // Knight
    if ( piece_type == 'c'){
        board[dest_row][dest_col] = new Knight(colour, piece_type);
    }

    // Bishop
    if ( piece_type == 'B'){
        board[dest_row][dest_col] = new Bishop(colour, piece_type);
    }

    // Queen
    if ( piece_type == 'Q'){
        board[dest_row][dest_col] = new Queen(colour, piece_type);
    }

    // King
    if ( piece_type == 'K'){
        board[dest_row][dest_col] = new King(colour, piece_type);
    }
}

void ChessBoard::move_piece(int start_row, int start_col, int dest_row, int dest_col){

    char piece_type = board[start_row][start_col]->get_piece_type();
    char colour = board[start_row][start_col]->get_colour();

    board[start_row][start_col] = nullptr;

    insert_piece( dest_row, dest_col, colour, piece_type );
}

void ChessBoard::resetBoard(){
    turn_count = 0;
    load_board(board);

    user_king_pos[0] = 7;
    user_king_pos[1] = 4;

    opponent_king_pos[0] = 0;
    opponent_king_pos[1] = 4;
}

void ChessBoard::load_board(Piece* board[8][8]){

  cout << "A new chess game is started!";

  // Bottom white, Top black

  for (int file = 0; file < 8; file++){

    // Pawns
    board[1][file] = new Pawn('B', 'P');

    board[6][file] = new Pawn('W', 'P');

    // Set unfilled squares to NULL
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

}

// TESTS

bool ChessBoard::wrong_turn( int start_row, int start_col, int turn_count ){

    // Cannot move Black if it is White's turn
    if ( turn_count == 0 && board[start_row][start_col]->get_colour() == 'B' ){
        return true;
    }

     // Cannot move White if it is Black's turn
    if ( turn_count == 1 && board[start_row][start_col]->get_colour() == 'W' ){
        return true;
    }

    return false;

}
