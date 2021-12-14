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

    // cout << endl << "king positions updated" << endl;

// Convert board positions to index:

    int source[2], destination[2];
    convert_to_index(source_square, destination_square, source, destination);

    if ( valid_move( source[0], source[1], destination[0], destination[1] ) ){
        // cout << endl << "valid move" << endl;
        cout << endl;
        print_piece_colour(turn_count);
        cout << "'s ";
        print_piece_type( board[source[0]][source[1]]->get_piece_type() );
        cout << " moves from " << source_square[0] << source_square[1] << " to " << destination_square[0] << destination_square[1];
        if ( board[ destination[0] ][ destination[1] ] != nullptr ){
            cout << " taking ";
            print_piece_colour( (turn_count+1)%2 );
            cout << "'s ";
            print_piece_type( board[ destination[0] ][ destination[1] ]->get_piece_type() );
        }
        move_piece( source[0], source[1], destination[0], destination[1] );
        // print_board();
        // cout << endl << "successfully moved" << endl;

         // if user's king in check
        if ( check(user_king_pos[0], user_king_pos[1], turn_count)){
            cout << endl << "User's king is in check, invalid move" << endl;
            move_piece( destination[0], destination[1], source[0], source[1] );
            // print_board();
            return;
        }

    }
    else{
        cout << endl << endl << "Invalid move!" << endl << endl;
        return;
    }

    // cout << endl << endl << "Turn: " << turn_count << endl << endl;
    // print_board();

    // cout << endl << "turn_count after change: " << turn_count << endl;

    // turn_count should alternate between 0 & 1 (white & black)
    turn_count = (turn_count + 1) % 2;

    // Check if opposition in check-mate
    if ( check_mate( opponent_king_pos[0], opponent_king_pos[1], turn_count )){
        // cout << endl << endl << "player corresponding to turn count: " << turn_count << " is in check-mate" << endl << endl;
        return;
    }

    // Check if opposition in check
    if ( check( opponent_king_pos[0], opponent_king_pos[1], turn_count ) ){

        cout << endl;
        print_piece_colour(turn_count);
        cout << " is in check";
    }

    // cout << endl << "Get beyond check-mate" << endl;

    // need check-mate after here for the appropriate turn-count
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

    // cout << endl << "Outputted Source Position: " << source[0] << source[1];
    // cout << endl << "Outputted Destination Position: " << destination[0] << destination[1];
    // cout << endl;

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

void ChessBoard::print_piece_type(char piece_type){

    // Pawn
    if ( piece_type == 'P' ){
        cout << "Pawn";
        return;
    }

    // Castle
    if ( piece_type == 'C' ){
        cout << "Castle";
        return;
    }
    
    // Bishop
    if ( piece_type == 'B' ){
        cout << "Bishop";
        return;
    }

    // Knight
    if ( piece_type == 'c' ){
        cout << "Knight";
        return;
    }

    // Queen
     if ( piece_type == 'Q' ){
        cout << "Queen";
        return;
    }

    // King
    if ( piece_type == 'K' ){
        cout << "King";
        return;
    }

}

void ChessBoard::print_piece_colour(int turn_count){

    // White
    if ( turn_count == 0 ){
        cout << "White";
        return;
    }

    // Black
    if (turn_count == 1){
        cout << "Black";
        return;
    }

    cout << endl << "Incorrect turn count of " << turn_count << endl;

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
        for (int j = 0; j < 8; j++){
            // Checking all pieces (legal moves prevents piece taking own colour)
            // user needs to be told if they're king in check or check mate, i.e. whether opponents moves can hit it
            // checking whether opponents piece can hit users king
            if ( board[i][j] != nullptr  && board[i][j]->colour == opponent_colour ){ // THIS MIGHT LEAD TO ERRORS DEPENDING ON HOW USE CHECK 
                // cout << endl << "position: " << i << " " << j << " has a piece of colour: " << opponent_colour << endl; 
                if ( valid_move(i, j, king_row, king_col) ){
                    // cout << "check: valid move from " << i << j << " to " << king_row << king_col;
                    threat_position[0] = i;
                    threat_position[1] = j;
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::check_mate( int king_row, int king_col, int turn_count ){

    char user_colour, opponent_colour, threat_piece;
    bool space_empty;
    int threat_position[2];

    if (turn_count == 0){
        user_colour = 'W';
        opponent_colour = 'B';
    }

    if (turn_count == 1){
        user_colour = 'B';
        opponent_colour = 'W';
    }

    // cout << endl << "assigned the colours" << endl;

    // print_board();

    // King must be in check to be in check-mate
    if ( !check(king_row, king_col, turn_count) ){
        // cout << endl << "king is not in check in the first place!" << endl;
        return false;
    }
    // cout << endl << "king is in check" << endl;

    // print_board(); // For some reason, adjacent_squares_check is being problematic

    // Can king move into adjacent square without being in check
    if ( !adjacent_squares_check(king_row, king_col, turn_count) ){
        // cout << endl << "King can move into an adjacent square - so not in check-mate" << endl;
        return false;
    }
    // cout << endl << "King cannot move into an adjacent square" << endl;

    // Save threat position
    threat_position[0] = this->threat_position[0];
    threat_position[1] = this->threat_position[1];
    threat_piece = board[ threat_position[0] ][ threat_position[1] ]->get_piece_type();

    // cout << endl << "threat position: " << this->threat_position[0] << this->threat_position[1] << endl;

    bool can_capture_threat = false;

    // Can piece threatening the king be taken
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            // cout << endl << "checking valid moves from " << i << j << " to threat position: " << threat_position[0] << threat_position[1] << endl;
            if ( board[i][j] != nullptr && board[i][j]->get_piece_type() != 'K' && valid_move( i, j, this->threat_position[0], this->threat_position[1]) ){
                // cout << endl << "valid move" << endl;
                can_capture_threat = true;
                // print_board();
                // cout << endl << "piece at position: " << i << j
                //      << " can take threat piece at position: " << this->threat_position[0] << this->threat_position[1] << endl;
                // temporarily move piece
                move_piece( i, j, this->threat_position[0], this->threat_position[1] );
                // cout << endl << "temporarily move piece" << endl;
                // print_board();
                if ( check( king_row, king_col, turn_count ) ){ // if king can't move, a piece that puts it in check is removed & king still in check => check mate
                    // // undo move
                    // this->threat_position[0] = threat_position[0];
                    // this->threat_position[1] = threat_position[1];
                    // cout << endl << "king no longer in check" << endl;
                    // cout << endl << "undo move..." << endl;
                    // move_piece ( this->threat_position[0], this->threat_position[1], i, j);
                    // // replace taken piece
                    // insert_piece( this->threat_position[0], this->threat_position[1], opponent_colour, threat_piece);
                    // print_board();
                    // cout << endl << "check mate - at which point we don't care about updating the board!" << endl;
                    return true;
                }
                // undo move
                this->threat_position[0] = threat_position[0];
                this->threat_position[1] = threat_position[1];
                // cout << endl << "king still in check" << endl;
                // cout << endl << "undo move..." << endl;
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
        // cout << endl << "threatening piece is a knight & puts king in check-mate" << endl;
        return true; // (CHECK) !!!!
    } 

    // Can threatening piece be blocked
    if ( can_block( king_row, king_col, threat_position[0], threat_position[1], turn_count) ){
        // cout << endl << "threatening piece can be blocked, orginal board" << endl;
        // print_board();

        // checking still in check after blocking piece
        move_piece(blocking_piece_position[0], blocking_piece_position[1], blocking_position[0], blocking_position[1]);
        // cout << endl << endl << "checking still in check after blocking piece" << endl;
        // print_board();
        if ( !check( king_row, king_col, turn_count) ){
            // cout << endl << "block results in king not being in check-mate anymore" << endl;
            move_piece(blocking_position[0], blocking_position[1], blocking_piece_position[0], blocking_piece_position[1]);
            // print_board();
            return false;
        }

        // blocking still results in check, i.e. check-mate
        // cout << endl << "block still results in check, so king is in check-mate" << endl;
        // print_board();
        return true;
    }

    // check-mate if King in check, opponent piece being taken doesnt affect checkmate & there is no blocking possible
    cout << endl;
    print_piece_colour(turn_count);
    cout << " is in checkmate" << endl;
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
                // cout << endl << "threat to left" << endl;
                if ( can_block_space( king_row, (king_col - n), turn_count) ){
                    blocking_position[0] = king_row;
                    blocking_position[1] = (king_col - n);
                    return true;
                }
            }
            // Threat to right
            if (threat_col > king_col){ 
                // cout << endl << "threat to right" << endl;
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

        // cout << endl << "vertical threat" << endl;
        for (int m = 1; m < row_diff; m++){

            // cout << endl << "king row: " << king_row << " threat row: " << threat_row << endl;
            // Threat above
            if ( threat_row < king_row ){
                // cout << endl << "Threat above" << endl;
                if ( can_block_space( (king_row - m), king_col, turn_count ) ){
                    blocking_position[0] = (king_row - m);
                    blocking_position[1] = king_col;
                    return true;
                }
            }

            // Threat below
            if ( threat_row > king_row ){
                // cout << endl << "Threat below with row difference: " << row_diff << endl;
                // cout << "value of m: " << m << " so checking space: " << (king_row+m) << king_col << endl;
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
            // cout << endl << "threat above right" << endl;
            if ( can_block_space( (king_row - w), (king_col + w), turn_count ) ){
                blocking_position[0] = (king_row - w);
                blocking_position[1] = (king_col + w);
                return true;
            }
        }

        // above left
        if ( threat_row < king_row && threat_col < king_col ){
            // cout << endl << "threat above left" << endl;
            if ( can_block_space( (king_row - w), (king_col - w), turn_count ) ){
                blocking_position[0] = (king_row - w);
                blocking_position[1] = (king_col - w);
                return true;
            }
        }

        // below right
        if ( threat_row > king_row && threat_col > king_col ){
            // cout << endl << "threat below right" << endl;
            if ( can_block_space( (king_row + w), (king_col + w), turn_count ) ){
                blocking_position[0] = (king_row + w);
                blocking_position[1] = (king_col + w);
                return true;
            }
        }

        // below left
        if ( threat_row > king_row && threat_col < king_col ){
            // cout << endl << "threat below left" << endl;
            if ( can_block_space( (king_row + w), (king_col - w), turn_count ) ){
                blocking_position[0] = (king_row + w);
                blocking_position[1] = (king_col - w);
                return true;
            }
        }
   }

    // cout << endl << "space cannot be blocked" << endl;
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
            // if (board[i][j] != nullptr){
            // cout << endl << "Checking square: " << i << j << " with piece type " << board[i][j]->get_piece_type() << " and colour " << board[i][j]->get_colour() << endl;
            // cout << "piece type: " << board[i][j]->get_piece_type() << endl;
            // cout << "piece colour: " << board[i][j]->get_colour() << endl;
            // cout << "valid move? " << valid_move(i, j , row, col) << endl << endl;
            // }

            if ( board[i][j] != nullptr && board[i][j]->get_piece_type() != 'K' 
                 && board[i][j]->get_colour() == blocking_colour  && valid_move( i, j, row, col ) ){
                // cout << endl << "can block space from piece at position: " << i << j << endl;
                blocking_piece_position[0] = i;
                blocking_piece_position[1] = j;
                return true;
            }
        }
    }
    // cout << endl << "cannot block" << endl;
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
        // cout << endl << "Valid move to row: " << dest_row << " & column: " << dest_col << endl << endl;
        if (space_empty == false){
            opponent_piece = board[dest_row][dest_col]->get_piece_type();
        }
        // Temporarily move king into space
        move_piece(king_row, king_col, dest_row, dest_col);
        // print_board();
        // Check if King in that space is now in check
        if ( !check( dest_row, dest_col, turn_count ) ){
            // cout << endl <<  "Not in check..." ;
            // Move King back
            move_piece(dest_row, dest_col, king_row, king_col);
            // Put piece in adjacent back
            if (space_empty == false){
                insert_piece(dest_row, dest_col, opponent_colour, opponent_piece );
            }
            // cout << "answer: ";
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
    // cout << endl << "answer: ";
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
        // cout << endl << endl << "threat position: " << threat_position[0] << threat_position[1] << endl;
        return false;
    }

     // space above diagonally to left
    if ( ( king_row != 0 && king_col != 0 ) && can_king_move(king_row, king_col, king_row - 1, king_col - 1, turn_count)){
        // cout << endl << endl << "threat position: " << threat_position[0] << threat_position[1] << endl;
        return false;
    }

    // space above diagonally to right
    if ( ( king_row != 0 && king_col != 7 ) && can_king_move(king_row, king_col, king_row - 1, king_col + 1, turn_count)){
        // cout << endl << endl << "threat position: " << threat_position[0] << threat_position[1] << endl;
        return false;
    }

    // space to left
    if ( king_col != 0 && can_king_move(king_row, king_col, king_row, king_col - 1, turn_count) ){
        // cout << endl << endl << "threat position: " << threat_position[0] << threat_position[1] << endl;
        return false;
    }

    // space to right
    if ( king_col != 7 && can_king_move(king_row, king_col, king_row, king_col + 1, turn_count)){
        // cout << endl << endl << "threat position: " << threat_position[0] << threat_position[1] << endl;
        return false;
    }

    // space below diagonally to left
    if ( ( king_row != 7 && king_col != 0 ) && can_king_move(king_row, king_col, king_row + 1, king_col - 1, turn_count)){
        // cout << endl << endl << "threat position: " << threat_position[0] << threat_position[1] << endl;
        return false;
    }

    // space below diagonally to right
    if (( king_row != 7 && king_col != 7 ) && can_king_move(king_row, king_col, king_row + 1, king_col + 1, turn_count)){
        // cout << endl << endl << "threat position: " << threat_position[0] << threat_position[1] << endl;
        return false;
    }

    // space below
    if ( king_row != 7 && can_king_move(king_row, king_col, king_row + 1, king_col, turn_count)){
        // cout << endl << endl << "threat position: " << threat_position[0] << threat_position[1] << endl;
        return false;
    }

    // If all adjacent squares in check
    // cout << endl << endl << "we can conclude that all adjacent squares to the king are in check!" << endl;
    // cout << endl << endl << "threat position: " << threat_position[0] << threat_position[1] << endl;
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

void ChessBoard::load_board(Piece* board[8][8]){

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