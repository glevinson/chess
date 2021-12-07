main: ChessMain.o ChessBoard.o
	g++ -g ChessMain.o ChessBoard.o -o main

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cc ChessBoard.h
	g++ -Wall -g -c ChessBoard.cc

clean:
	rm -f *.o main