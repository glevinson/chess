# if something has - then can normally put at the start
# -o expects an argument after, whereas -g does not expect an argument after it

chess: ChessMain.o ChessBoard.o pawn.o castle.o bishop.o knight.o queen.o king.o piece.o
	g++ -g -Wall -o chess ChessMain.o ChessBoard.o pawn.o castle.o bishop.o knight.o queen.o king.o piece.o

piece.o: piece.cpp piece.h
	g++ -Wall -g -c piece.cpp

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	g++ -Wall -g -c ChessBoard.cpp

pawn.o: pawn.cpp pawn.h
	g++ -Wall -g -c pawn.cpp

castle.o: castle.cpp castle.h
	g++ -Wall -g -c castle.cpp

bishop.o: bishop.cpp bishop.h
	g++ -Wall -g -c bishop.cpp

knight.o: knight.cpp knight.h
	g++ -Wall -g -c knight.cpp

queen.o: queen.cpp queen.h
	g++ -Wall -g -c queen.cpp

king.o: king.cpp king.h
	g++ -Wall -g -c king.cpp

clean:
	rm -f *.o chess