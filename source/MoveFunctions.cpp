#include "..\header\MoveFunctions.h"


std::list<sf::Vector2f> * KnightMoves::operator() (const sf::Vector2f & position, PieceColor color)
{
	//Need to delete this list somewhere
	std::list<sf::Vector2f> * possibleMoves = new std::list<sf::Vector2f>;

	sf::Vector2f newPos;		
	//Get all positive and negative combinations of |x| = 2, |y| = 1
	int x = 2;
	int y = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			newPos = sf::Vector2f(position.x + x, position.y + y);
			if (newPos.x < 8 && newPos.x >= 0)
			{
				if (newPos.y < 8 && newPos.y >= 0)
					if (gameBoard[newPos.y][newPos.x]->color != color)//Game board is not initialized. Perhaps better to have a wrapper
						possibleMoves->push_back(newPos);           //Where all functions are defined that also has a gameboard
			}
			y *= -1;
		}
		x *= -1;
	}

	//Get all positive and negative combinations of |x| = 1, |y| = 2
	x = 1;
	y = 2;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			newPos = sf::Vector2f(position.x + x, position.y + y);
			if (newPos.x < 8 && newPos.x >= 0)
			{
				if (newPos.y < 8 && newPos.y >= 0)//Check if valid before pushback
					if (gameBoard[newPos.y][newPos.x]->color != color)
						possibleMoves->push_back(newPos);
			}
			y *= -1;
		}
		x *= -1;
	}	
	
	return possibleMoves;
}



std::list<sf::Vector2f> * RookMoves::operator() (const sf::Vector2f & position, PieceColor color)//, const Gameboard & gameBoard)
{
	std::list<sf::Vector2f> * possibleMoves = new std::list<sf::Vector2f>;
	
	sf::Vector2f newPos = position;
	sf::Vector2f displacement = sf::Vector2f(-1, 0);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);
	
	displacement = sf::Vector2f(1, 0);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(0, 1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(0, -1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	return possibleMoves;
}

std::list<sf::Vector2f> * BishopMoves::operator() (const sf::Vector2f & position, PieceColor color)
{
	std::list<sf::Vector2f> * possibleMoves = new std::list<sf::Vector2f>;

	sf::Vector2f newPos = position;
	sf::Vector2f displacement = sf::Vector2f(1, 1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(1, -1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(-1, -1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(-1, 1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);
	
	return possibleMoves;
}

std::list<sf::Vector2f> * QueenMoves::operator() (const sf::Vector2f & position, PieceColor color)
{
	std::list<sf::Vector2f> * possibleMoves = new std::list<sf::Vector2f>;

	sf::Vector2f newPos = position;

	//Diagonal
	sf::Vector2f displacement = sf::Vector2f(1, 1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(1, -1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(-1, -1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(-1, 1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	//Horizontal/vertical
	displacement = sf::Vector2f(-1, 0);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(1, 0);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(0, 1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	displacement = sf::Vector2f(0, -1);
	horizDiag.getUDLRandDiag(position, displacement, color, *possibleMoves);

	return possibleMoves;
}

std::list<sf::Vector2f> * KingMoves::operator() (const sf::Vector2f & position, PieceColor color)
{
	std::list<sf::Vector2f> * possibleMoves = new std::list<sf::Vector2f>;

	sf::Vector2f newPos = position;
	sf::Vector2f displacement = sf::Vector2f(1, 1);
	
	//Find legal diagonal moves
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			newPos = position + displacement;
			if (newPos.x < 8 && newPos.x >= 0)
			{
				if (newPos.y < 8 && newPos.y >= 0)//Check if valid before pushback
					if (gameBoard[newPos.y][newPos.x]->color != color)
						possibleMoves->push_back(newPos);
			}
			displacement.y *= -1;
			
		}
		displacement.x *= -1;
	}

	//Find legal up down  moves
	displacement = sf::Vector2f(1, 0);
	for (int i = 0; i < 2; i++)
	{
		newPos = position + displacement;
		if (newPos.x < 8 && newPos.x >= 0)
		{
			if (newPos.y < 8 && newPos.y >= 0)//Check if valid before pushback
				if (gameBoard[newPos.y][newPos.x]->color != color)
					possibleMoves->push_back(newPos);
		}
		displacement.x *= -1;
	}

	//Legal left right moves
	displacement = sf::Vector2f(0, 1);
	for (int i = 0; i < 2; i++)
	{
		newPos = position + displacement;
		if (newPos.x < 8 && newPos.x >= 0)
		{
			if (newPos.y < 8 && newPos.y >= 0)//Check if valid before pushback
				if (gameBoard[newPos.y][newPos.x]->color != color)
					possibleMoves->push_back(newPos);
		}
		displacement.y *= -1;
	}

	return possibleMoves;
}

std::list<sf::Vector2f> * PawnMoves::operator() (const sf::Vector2f & position, PieceColor color)
{
	std::list<sf::Vector2f> * possibleMoves = new std::list<sf::Vector2f>;

	sf::Vector2f newPos = position;
	sf::Vector2f displacement = sf::Vector2f(0, 1);
	//Get legal moves for black pawns
	if (color == Black)
	{ //Find moves 
		for (int i = 0; i < 2; i++)
		{ 
			newPos += displacement;
			if (newPos.x < 8 && newPos.x >= 0)
			{
				if (newPos.y < 8 && newPos.y >= 0)//Check if valid before pushback
					if (gameBoard[newPos.y][newPos.x]->color == Unaffiliated)
						possibleMoves->push_back(newPos);
			}
			if (position.y != 1)//Check if pawn is at its starting position
				break;
		}

		//Find capture moves
		displacement = sf::Vector2f(1, 1);
		
		for (int i = 0; i < 2; i++)
		{	
			newPos = position;
			newPos += displacement;
			if (newPos.x < 8 && newPos.x >= 0)
			{
				if (newPos.y < 8 && newPos.y >= 0)//Check if valid before pushback
					if (gameBoard[newPos.y][newPos.x]->color == White)
						possibleMoves->push_back(newPos);
			}
			displacement.x *= -1;
		}
	}
	//Find valid white pawn moves
	else {
		displacement.y *= -1;
		for (int i = 0; i < 2; i++)
		{
			newPos += displacement;
			if (newPos.x < 8 && newPos.x >= 0)
			{
				if (newPos.y < 8 && newPos.y >= 0)//Check if valid before pushback
					if (gameBoard[newPos.y][newPos.x]->color == Unaffiliated)
						possibleMoves->push_back(newPos);
			}
			if (position.y != 6)//Check if pawn at starting position
				break;
		}

		//Find capture moves
		displacement = sf::Vector2f(1, -1);

		for (int i = 0; i < 2; i++)
		{
			newPos = position;
			newPos += displacement;
			if (newPos.x < 8 && newPos.x >= 0)
			{
				if (newPos.y < 8 && newPos.y >= 0)//Check if valid before pushback
					if (gameBoard[newPos.y][newPos.x]->color == Black)
						possibleMoves->push_back(newPos);
			}
			displacement.x *= -1;
		}
	}

	return possibleMoves;
}

