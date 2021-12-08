chess: ChessMain.o ChessBoard.o
	g++ -g ChessMain.o ChessBoard.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cc ChessBoard.h
	g++ -Wall -g -c ChessBoard.cc

clean:
	rm -f *.o chess


# main: ChessMain.o ChessBoard.o pawn.o castle.o bishop.o knight.o queen.o knight.o
# 	g++ -g ChessMain.o ChessBoard.o pawn.o castle.o bishop.o knight.o queen.o knight.o -o main

# ChessMain.o: ChessMain.cpp ChessBoard.h
# 	g++ -Wall -g -c ChessMain.cpp

# ChessBoard.o: ChessBoard.cc ChessBoard.h
# 	g++ -Wall -g -c ChessBoard.cc

# pawn.o: pawn.cc pawn.h
# 	g++ -Wall -g -c pawn.cc

# castle.o: castle.cc castle.h
# 	g++ -Wall -g -c castle.cc

# bishop.o: bishop.cc bishop.h
# 	g++ -Wall -g -c bishop.cc

# knight.o: knight.cc knight.h
# 	g++ -Wall -g -c knight.cc

# queen.o: queen.cc queen.h
# 	g++ -Wall -g -c queen.cc

# king.o: king.cc king.h
# 	g++ -Wall -g -c king.cc

# clean:
# 	rm -f *.o main