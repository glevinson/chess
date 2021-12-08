#include"ChessBoard.h"
// #include"piece.h"
#include<cstdlib>
#include<iostream>

using namespace std;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";


	ChessBoard cb = ChessBoard();

	cb.print_board();

	// cout << "legal? " << cb.board[5][1]->legal_right_up_diagonal(5,1,3,5,cb.board) << endl;


	// UPCASTING MEANS CAN'T ACCESS POSITION
	// cout << endl <<  "King starting position: " << cb.board[0][4]->position[0] << cb.board[0][4]->position[1] << endl;

	// cb.submitMove("H3", "B2");

	// Checking King moves ok:

	// cout << "Should be valid King move " << cb.board[7][4]->valid_move(7,4,7,3) 
	// 	 << endl;

	// cout << "Should be valid King move " << cb.board[7][4]->valid_move(7,4,7,5) 
	// 	 << endl;

	// cout << "Should be invalid King move " << cb.board[7][4]->valid_move(7,4,5,4) 
	// 	 << endl;

	// cout << "Should be invalid King move " << cb.board[7][4]->valid_move(7,4,7,6) 
	// 	 << endl;

	// Checking Bishop moves

	// cout << "Should be valid Bishop move " << cb.board[7][5]->valid_move(7,5,5,3) 
	// 	 << endl;

	// cout << "Should be invalid Bishop move " << cb.board[7][5]->valid_move(7,5,0,2) 
	// 	 << endl;

	// cout << "Should be valid Bishop move " << cb.board[7][5]->valid_move(7,5,2,0) 
	// 	 << endl;

	// cout << "valid Knight move? " << cb.board[7][6]->valid_move(7,6,7,6) 
	// 	 << endl;
	

	// cout << cb.board[0][0]->get_colour()'' << endl; 



	// ChessBoard cb;
	// cout << '\n';
	//
	// cb.submitMove("D7", "D6");
	// cout << '\n';
	//
	// cb.submitMove("D4", "H6");
	// cout << '\n';
	//
	// cb.submitMove("D2", "D4");
	// cout << '\n';
	//
	// cb.submitMove("F8", "B4");
	// cout << '\n';
	//
	// cout << "=========================\n";
	// cout << "Alekhine vs. Vasic (1931)\n";
	// cout << "=========================\n\n";
	//
	// cb.resetBoard();
	// cout << '\n';
	//
	// cb.submitMove("E2", "E4");
	// cb.submitMove("E7", "E6");
	// cout << '\n';
	//
	// cb.submitMove("D2", "D4");
	// cb.submitMove("D7", "D5");
	// cout << '\n';
	//
	// cb.submitMove("B1", "C3");
	// cb.submitMove("F8", "B4");
	// cout << '\n';
	//
	// cb.submitMove("F1", "D3");
	// cb.submitMove("B4", "C3");
	// cout << '\n';
	//
	// cb.submitMove("B2", "C3");
	// cb.submitMove("H7", "H6");
	// cout << '\n';
	//
	// cb.submitMove("C1", "A3");
	// cb.submitMove("B8", "D7");
	// cout << '\n';
	//
	// cb.submitMove("D1", "E2");
	// cb.submitMove("D5", "E4");
	// cout << '\n';
	//
	// cb.submitMove("D3", "E4");
	// cb.submitMove("G8", "F6");
	// cout << '\n';
	//
	// cb.submitMove("E4", "D3");
	// cb.submitMove("B7", "B6");
	// cout << '\n';
	//
	// cb.submitMove("E2", "E6");
	// cb.submitMove("F7", "E6");
	// cout << '\n';
	//
	// cb.submitMove("D3", "G6");
	// cout << '\n';

	return 0;
}
