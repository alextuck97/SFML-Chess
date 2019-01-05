#ifndef HORIZ_DIAG_MOVES
#define HORIZ_DIAG_MOVES

#include <SFML\Graphics.hpp>
#include <list>
#include "GameStateIdentifiers.h"

/*
Helper class for piece move functions that require finding all horizontal/diagonal moves (Rook, etc.).
Finds potential moves based off a displacement value.
*/

class HorizDiagMoves
{
public:
	HorizDiagMoves() {};

	HorizDiagMoves(const Gameboard & gameBoard);

	~HorizDiagMoves() {};

	//Find all legal moves in the direction of the displacement vector
	void getUDLRandDiag(const sf::Vector2f & position, sf::Vector2f & displacement, PieceColor color,
		std::list<sf::Vector2f> & possibleMoves);


private: 
	Gameboard gameBoard;//Watch this declaration

	//std::list<sf::Vector2f> possibleMoves;

};



#endif // !HORIZ_DIAG_MOVES

