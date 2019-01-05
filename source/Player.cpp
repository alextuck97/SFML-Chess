#include "..\header\Player.h"




Player::Player(Gameboard & gameBoard) : gameBoard(gameBoard)
{
	whoseTurn = White;
}


sf::Vector2i Player::clickSquare(sf::Vector2f mousePos, sf::Vector2u winDimensions)
{
	//sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*(getContext().window)));

	//Transform mouse position into integer coords used in gameboard matrix
	mousePos.x -= winDimensions.x * 0.15;//event.size.width * 0.15;
	mousePos.y -= winDimensions.y * 0.033;//event.size.height * .033;

	mousePos.x /= (winDimensions.x * .0875);
	mousePos.y /= (winDimensions.y * 0.1167);

	return sf::Vector2i(mousePos.x, mousePos.y);
}

PieceColor Player::getWhoseTurn()
{
	return whoseTurn;
}

void Player::switchTurn()
{
	if (whoseTurn == White)
		whoseTurn = Black;
	else
		whoseTurn = White;
}

void Player::setSelectedPiece(sf::Vector2i piece)
{
	selectedPiece = piece;
}

sf::Vector2i Player::getSelectedPiece()
{
	return selectedPiece;
}

