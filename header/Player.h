#ifndef PLAYER_H
#define PLAYER_H
#include <SFML\Graphics.hpp>
#include "GameStateIdentifiers.h"

class Player //: public State
{
public:

	Player() { whoseTurn = Black; }

	explicit Player(Gameboard & gameBoard);

	//void movePiece();

	//Returns the coordinates of the square a player clicks, in terms of the board
	sf::Vector2i clickSquare(sf::Vector2f mousePos, sf::Vector2u winDimension);

	PieceColor getWhoseTurn();

	void setSelectedPiece(sf::Vector2i piece);

	sf::Vector2i getSelectedPiece();

	void switchTurn();

private:
	
	sf::Vector2i selectedPiece;

	Gameboard gameBoard;

	PieceColor whoseTurn;
	 
};


#endif // !PLAYER_H
