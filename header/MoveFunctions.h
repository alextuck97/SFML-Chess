#ifndef MOVE_FUNCTIONS_H
#define MOVE_FUNCTIONS_H

#include <list>
#include <SFML\Graphics.hpp>
#include "GameStateIdentifiers.h"
#include "HorizDiagMoves.h"

/*
Collection of function objects for each piece. Each object inherits from
an abstract base class. 
operator() is defined for each function, which returns a pointer to a list of vector2f.
*/

//Move functions and horiz diag seems to be working 7/25/18

//Abstract base class 
class MoveFunction{
public:
	MoveFunction() {};
	MoveFunction(const Gameboard & gameBoard) : gameBoard(gameBoard) , horizDiag(gameBoard) {};
	//MoveFunction(const Gameboard & gameBoard, std::list<sf::Vector2f> & possibleMoves) : gameBoard(gameBoard),
		//horizDiag(gameBoard, possibleMoves) {};
	virtual std::list<sf::Vector2f> * operator() (const sf::Vector2f & position, PieceColor color) = 0;//, const Gameboard & gameBoard) = 0;
	
	HorizDiagMoves horizDiag;	

private:
	Gameboard gameBoard;
};

class KnightMoves : public MoveFunction{
public:
	KnightMoves() {};
	KnightMoves(const Gameboard & gameBoard) : gameBoard(gameBoard) {};
	virtual std::list<sf::Vector2f> * operator() (const sf::Vector2f & position, PieceColor color);

private:
	Gameboard gameBoard;
};

class RookMoves : public MoveFunction{
public:
	RookMoves() {};
	RookMoves(const Gameboard & gameBoard) : gameBoard(gameBoard) , horizDiag(gameBoard) {};
	//RookMoves(const Gameboard & gameBoard, std::list<sf::Vector2f> & possibleMoves) : MoveFunction(gameBoard, possibleMoves) {};
	virtual std::list<sf::Vector2f> * operator() (const sf::Vector2f & position, PieceColor color);//, const Gameboard & gameBoard);

	HorizDiagMoves horizDiag;

private:
	Gameboard gameBoard;
};

class BishopMoves : public MoveFunction{
public:
	BishopMoves() {};
	BishopMoves(const Gameboard & gameBoard) : gameBoard(gameBoard), horizDiag(gameBoard) {};
	//BishopMoves(const Gameboard & gameBoard, std::list<sf::Vector2f> & possibleMoves) : MoveFunction(gameBoard, possibleMoves) {};
	virtual std::list<sf::Vector2f> * operator() (const sf::Vector2f & position, PieceColor color);

	HorizDiagMoves horizDiag;

private:
	Gameboard gameBoard;
};

class QueenMoves : public MoveFunction{
public:
	QueenMoves() {};
	QueenMoves(const Gameboard & gameBoard) : gameBoard(gameBoard), horizDiag(gameBoard) {};
	//QueenMoves(const Gameboard & gameBoard, std::list<sf::Vector2f> & possibleMoves) : MoveFunction(gameBoard, possibleMoves) {};
	virtual std::list<sf::Vector2f> * operator() (const sf::Vector2f & position, PieceColor color);

	HorizDiagMoves horizDiag;

private:
	Gameboard gameBoard;
};

class KingMoves : public MoveFunction{
public:
	KingMoves() {};
	KingMoves(const Gameboard & gameBoard) : gameBoard(gameBoard) {};
	
	virtual std::list<sf::Vector2f> * operator() (const sf::Vector2f & position, PieceColor color);

private:
	Gameboard gameBoard;
};

class PawnMoves : public MoveFunction{
public:
	PawnMoves() {};
	PawnMoves(const Gameboard & gameBoard) : gameBoard(gameBoard) {};
	
	virtual std::list<sf::Vector2f> * operator() (const sf::Vector2f & position, PieceColor color);

private:
	Gameboard gameBoard;
};





#endif










