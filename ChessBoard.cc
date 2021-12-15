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
// how make sure they finish in 
void ChessBoard::submitMove(string source_square_str, string destination_square_str){
// entering a string above should automatically include the sentinel
// Which marks the end of a string

    char source_square[3], destination_square[3];

    source_square[0] = source_square_str[0];
    source_square[1] = source_square_str[1];
    source_square[2] = '\0';

    destination_square[0] = destination_square_str[0];
    destination_square[1] = destination_square_str[1];
    destination_square[2] = '\0';

    // turn_count = 0 (white) & turn_count = 1 (black)
    if (turn_count == 0){
        user_king_pos[0] = W_king_pos[0];
        user_king_pos[1] = W_king_pos[1];
        
        opponent_king_pos[0] = B_king_pos[0];
        opponent_king_pos[1] = B_king_pos[1];
    }

    if (turn_count == 1){
        user_king_pos[0] = B_king_pos[0];
        user_king_pos[1] = B_king_pos[1];

        opponent_king_pos[0] = W_king_pos[0];
        opponent_king_pos[1] = W_king_pos[1];
    }

// Convert board positions to index:

    int source[2], destination[2];
    convert_to_index(source_square, destination_square, source, destination);

     // Check actually moving a piece
     if ( board[source[0]][source[1]] == nullptr ){
        cout << "There is no piece at position " << source_square[0] 
             << source_square[1] << "!" ;
        return;
    }

     // Check if moving wrong colour
    if ( wrong_turn(source[0], source[1], turn_count) ){
        cout << endl << "It is not " << print_piece_colour( (turn_count+1)%2 ) 
             << "'s turn to move" << endl;
        return;
    }

    // must add possibility of stalemate
    // must 

    if ( valid_move( source[0], source[1], destination[0], destination[1] ) ){
        cout << endl << print_piece_colour(turn_count) << "'s " 
            << print_piece_type(board[source[0]][source[1]]->get_piece_type());
        cout << " moves from " << source_square[0] << source_square[1] << " to " 
             << destination_square[0] << destination_square[1];
        if ( board[ destination[0] ][ destination[1] ] != nullptr ){
            cout << " taking " << print_piece_colour( (turn_count+1)%2 ) << "'s " ;
            cout << print_piece_type( board[ destination[0] ][ destination[1] ]->get_piece_type());
        }
        move_piece( source[0], source[1], destination[0], destination[1] );

         // cannot do move if leaves users king in check & replace the piece if has to
         // this check will also change the threatening pieces, so need to reset them
        if ( check(user_king_pos[0], user_king_pos[1], turn_count)){
            cout << endl << "User's king is in check, invalid move" << endl;
            // insert piece lost if required
            move_piece( destination[0], destination[1], source[0], source[1] );
            return;
        }

    }
    else{
        cout << endl << print_piece_colour(turn_count) << "'s " 
             << print_piece_type ( board[ source[0] ][ source[1] ]->get_piece_type() )
             << " cannot move to " << destination_square[0] 
             << destination_square[1] << "!" << endl;
        return;
    }

    // turn_count should alternate between 0 & 1 (white & black)
    turn_count = (turn_count + 1) % 2;

    // Check if opposition in check-mate
    if ( check_mate( opponent_king_pos[0], opponent_king_pos[1], turn_count )){
        return;
    }

    // Check if opposition in check
    if ( check( opponent_king_pos[0], opponent_king_pos[1], turn_count ) ){

        cout << endl << print_piece_colour(turn_count) << " is in check";
    }

    // need check-mate after here for the appropriate turn-count
}

// Converts postion from (column,row) to (row, column) making it compatible with our board:
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

void ChessBoard::print_board(){

cout << "\n       0  1  2  3  4  5  6  7 ";
cout << "\n       A  B  C  D  E  F  G  H ";
cout << "\n   * * * * * * * * * * * * *" << endl;
    for(int i = 0; i<8; i++){
        cout << i << " " << (8-i) << " * ";
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

    char opponent_colour;

    // i.e. if white turn
    if (turn_count == 0){
        opponent_colour = 'B';
    }

    // i.e. if black turn
    else{
        opponent_colour = 'W';
    }

    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j++){
            // Checking all pieces (legal moves prevents piece taking own colour)
            // user needs to be told if they're king in check or check mate, i.e. whether opponents moves can hit it
            // checking whether opponents piece can hit users king
            if ( board[i][j] != nullptr  && board[i][j]->get_colour() == opponent_colour ){
                if ( valid_move(i, j, king_row, king_col) ){
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

    cout << endl << "colours allocated" << endl;
    // Iterating through the finding every user's piece
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ( board[i][j] != nullptr && board[i][j]->get_colour() == user_colour ){
                cout << endl << "checking piece corresponding to turn: " << turn_count << " at position " << i << j << endl;
                // Checks if there is any square on the board that piece at (i,j) can move to
                for (int n = 0; n < 8; n++){
                    for (int m = 0; m < 8; m++){
                        if (valid_move(i,j,n,m) && i != n && j != m){ 
                            if ( board[i][j]->get_piece_type() == 'K' ){  // king cannot move into check !!

                            }
                            cout << endl << "valid move to " << i << j << endl;
                            return false;
                        }
                    }
                }
                cout << endl << "no valid moves..." << endl;
            }
        }
    }
    return true;
}

bool ChessBoard::check_mate( int king_row, int king_col, int turn_count ){

    char opponent_colour, threat_piece;
    int threat_position[2];

    if (turn_count == 0){
        opponent_colour = 'B';
    }

    if (turn_count == 1){
        opponent_colour = 'W';
    }

    // print_board();

    // King must be in check to be in check-mate
    if ( !check(king_row, king_col, turn_count) ){
        return false;
    }

    // Can king move into adjacent square without being in check
    if ( !adjacent_squares_check(king_row, king_col, turn_count) ){
        return false;
    }

    // Save threat position
    threat_position[0] = this->threat_position[0];
    threat_position[1] = this->threat_position[1];
    threat_piece = board[ threat_position[0] ][ threat_position[1] ]->get_piece_type();

    bool can_capture_threat = false;

    // Can piece threatening the king be taken
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ( board[i][j] != nullptr && board[i][j]->get_piece_type() != 'K' && valid_move( i, j, this->threat_position[0], this->threat_position[1]) ){
                can_capture_threat = true;
                 // temporarily move piece
                move_piece( i, j, this->threat_position[0], this->threat_position[1] );
                if ( check( king_row, king_col, turn_count ) ){ // if king can't move, a piece that puts it in check is removed & king still in check => check mate
                    return true;
                }
                // undo move
                this->threat_position[0] = threat_position[0];
                this->threat_position[1] = threat_position[1];
                
                move_piece ( this->threat_position[0], this->threat_position[1], i, j);
                insert_piece( this->threat_position[0], this->threat_position[1], opponent_colour, threat_piece);
                // print_board();
            }

            if (can_capture_threat == true){
                break;
            }

        }

        if (can_capture_threat == true){
            break;
        }

    }

// If valid block or take, need to take or block, check if it is still in check, then undo the move

    // If threatening piece is a knight, check-mate after above 2 tests
    if (board[threat_position[0]][threat_position[1]]->get_piece_type() == 'c'){
        return true; // (CHECK) !!!!
    } 

    // Can threatening piece be blocked
    if ( can_block( king_row, king_col, threat_position[0], threat_position[1], turn_count) ){
        
        // checking still in check after blocking piece
        move_piece(blocking_piece_position[0], blocking_piece_position[1], blocking_position[0], blocking_position[1]);
    
        if ( !check( king_row, king_col, turn_count) ){
            move_piece(blocking_position[0], blocking_position[1], blocking_piece_position[0], blocking_piece_position[1]);
            return false;
        }

        // blocking still results in check, i.e. check-mate
        return true;
    }

    // check-mate if King in check, opponent piece being taken doesnt affect checkmate & there is no blocking possible
    cout << endl << print_piece_colour(turn_count) << " is in checkmate" << endl;
    return true;
}



// Checks if can block the path of a threatening piece
bool ChessBoard::can_block( int king_row, int king_col, int threat_row, int threat_col, int turn_count){
    
    int row_diff = abs(king_row - threat_row);
    int col_diff = abs(king_col - threat_col);

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

// will want to see if same colour as the king can block a space
bool ChessBoard::can_block_space( int row, int col, int turn_count){

    char blocking_colour;

    if (turn_count == 0){
        blocking_colour = 'W';
    }

    if (turn_count == 1){
        blocking_colour = 'B';
    }

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){

            if ( board[i][j] != nullptr && board[i][j]->get_piece_type() != 'K' 
                 && board[i][j]->get_colour() == blocking_colour  && valid_move( i, j, row, col ) ){
                // cout << endl << "can block space from piece at position: " << i << j << endl;
                blocking_piece_position[0] = i;
                blocking_piece_position[1] = j;
                return true;
            }
        }
    }
    return false;
}

// WORKS
// returns true if king can move to a space without being in check
bool ChessBoard::can_king_move( int king_row, int king_col, int dest_row, int dest_col, int turn_count){

    char opponent_colour, opponent_piece;
    bool space_empty = false;

    // As the checks below will distort the check positions
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
    this->threat_position[0] = threat_position[0];
    this->threat_position[1] = threat_position[1];
    return false;
}

// If king can move to adjacent square without being in check, then not all adjacent
// squares to the king are in check
// WORKS
bool ChessBoard::adjacent_squares_check(int king_row, int king_col, int turn_count){
    
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
}

void ChessBoard::load_board(Piece* board[8][8]){

  cout << "A new chess game is started!";

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

// void ChessBoard::load_board(Piece* board[8][8]){

//   cout << "A new chess game is started!";

//   // Bottom white, Top black

//   for (int file = 0; file < 8; file++){

//     // Pawns
//     board[1][file] = nullptr;

//     board[6][file] = nullptr;

//     // Set unfilled positions to NULL
//     for (int rank = 0; rank < 8; rank++){
//       board[rank][file] = nullptr;
//     }
//   }

//   board[0][0] = new King('W', 'K');
//   board[6][5] = new Queen('W', 'Q');
//   board[7][7] = new King('B', 'K');
  
// }

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
