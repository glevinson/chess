# if something has - then can normally put at the start
# -o expects an argument after, whereas -g does not expect an argument after it

chess: ChessMain.o ChessBoard.o pawn.o castle.o bishop.o knight.o queen.o king.o piece.o
	g++ -g -o chess ChessMain.o ChessBoard.o pawn.o castle.o bishop.o knight.o queen.o king.o piece.o

piece.o: piece.cc piece.h
	g++ -Wall -g -c piece.cc

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cc ChessBoard.h
	g++ -Wall -g -c ChessBoard.cc

pawn.o: pawn.cc pawn.h
	g++ -Wall -g -c pawn.cc

castle.o: castle.cc castle.h
	g++ -Wall -g -c castle.cc

bishop.o: bishop.cc bishop.h
	g++ -Wall -g -c bishop.cc

knight.o: knight.cc knight.h
	g++ -Wall -g -c knight.cc

queen.o: queen.cc queen.h
	g++ -Wall -g -c queen.cc

king.o: king.cc king.h
	g++ -Wall -g -c king.cc

clean:
	rm -f *.o main