#ifndef MOVES_H
#define MOVES_H

/*
Class for finding all possible moves given a GamePiece struct

getMoves() - takes a gamepiece, returns its legal moves
*/

#include <map>
#include "MoveFunctions.h"

class Moves
{
public:
	Moves();

	Moves(const Gameboard & gameBoard);

	~Moves() {}

	//Return list of all possible moves given a piece
	std::list<sf::Vector2f> * getMoves(const GamePiece & piece);

	//Return a pointer to the specified move function
	MoveFunction * getMoveFunction(Pieces piece);

private:

	//Register move functions in a map of PieceIDs
	template<typename T>
	void registerMoveFunction(Pieces pieceID)
	{
		moves[pieceID] = new T(gameBoard);//Need to make all contructors for mvFuncs universal. And return more refs, less ptrs
	}
	

	std::map<Pieces, MoveFunction*> moves;

	Gameboard gameBoard;



};

#endif // !MOVES_H