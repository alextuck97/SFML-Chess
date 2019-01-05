#include "..\header\HorizDiagMoves.h"

HorizDiagMoves::HorizDiagMoves(const Gameboard & gameBoard)
{
	this->gameBoard = gameBoard;

	//this->possibleMoves = possibleMoves;
}

void HorizDiagMoves::getUDLRandDiag(const sf::Vector2f & position, sf::Vector2f & displacement, PieceColor color, std::list<sf::Vector2f> & possibleMoves)
{
	sf::Vector2f newPos = position;
	bool isSharedSpace = false;
	
	int i = 1;
	while (!isSharedSpace)//Need a way to exit if theres isnt a shared space
	{
		newPos += displacement;
		if (newPos.x < 8 && newPos.x >= 0)//Check x bounds
		{
			if (newPos.y < 8 && newPos.y >= 0)//Check y bounds
			{
				if (gameBoard[newPos.y][newPos.x]->color == Unaffiliated)//Open space, legal move
				{
					possibleMoves.push_back(newPos);
				}
				else if (gameBoard[newPos.y][newPos.x]->color != color)//Opposite color, legal move
				{
					possibleMoves.push_back(newPos);
					isSharedSpace = true;
				}
				else//Same color space, illegal move
				{
					isSharedSpace = true;
				}
			}
			//Break if out of y bounds
			else
				break;
		}
		//Break if out of x bounds
		else
			break;
		i++;
	}
}


