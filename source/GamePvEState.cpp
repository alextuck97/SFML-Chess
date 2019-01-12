#include "../header/GamePvEState.h"


GamePvEState::GamePvEState(StateStack & stack, Context context) : GamePvPState(stack, context)
{

	initPlayerColor();

	this->ai = AI(this->getGameBoard(), this->aiColor, this->getMoves());
	

	


}


GamePvEState::~GamePvEState()
{
	
}

bool GamePvEState::update(sf::Time dt)
{
/*
Calls the ai to select a piece to move, and the place to move the piece
*/
	

	if (getThePlayers().getWhoseTurn() == this->aiColor)
	{
		elapsedTime += dt;
		if (elapsedTime > nextUpdate) 
		{
			sf::Vector2i piece;
			sf::Vector2i boardCoords;
			std::pair<sf::Vector2i, sf::Vector2i> pieceAndMove = ai.getMoveAndGetSelected();

			std::tie(piece, boardCoords) = pieceAndMove;

			getThePlayers().setSelectedPiece(piece);

			if (this->getGameBoard()[boardCoords.y][boardCoords.x]->color == Unaffiliated)
			{
				movePiece(boardCoords);
			}
			else if (this->getGameBoard()[boardCoords.y][boardCoords.x]->color == this->playerColor)
			{
				std::pair<Pieces, PieceColor> capPiece = capturePiece(boardCoords);
				endGame(capPiece);
			}

			getThePlayers().switchTurn();
			elapsedTime = sf::Time::Zero;
		}
		
	}

	

	return true;
}



void GamePvEState::mouseButtonPressed(const sf::Event & event)
{
	if (this->getThePlayers().getWhoseTurn() == this->playerColor)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*(getContext().window)));
			sf::Vector2i boardCoords = this->getThePlayers().clickSquare(mousePos, getContext().window->getSize());

			if (boardCoords.y <= 7 && boardCoords.y >= 0)
			{
				//Get the possible moves if the clicked square has the players piece
				if (this->getThePlayers().getWhoseTurn() == this->getGameBoard()[boardCoords.y][boardCoords.x]->color)
				{
					if (this->getPossibleMoves() != nullptr) { this->getPossibleMoves()->clear(); }
					
					this->setPossibleMoves(getMoves().getMoves(*this->getGameBoard()[boardCoords.y][boardCoords.x]));
					getThePlayers().setSelectedPiece(boardCoords);
				}
				//Clicked square does not have players piece, so check if the clicked square is a legal move
				//If so move piece
				else if (inPossibleMoves(boardCoords) && this->getGameBoard()[boardCoords.y][boardCoords.x]->color == Unaffiliated)
				{
					//Swap the players selected piece with boardCoords
					movePiece(boardCoords);
					getThePlayers().switchTurn();
				}
				else if (inPossibleMoves(boardCoords))
				{
					//Capture a piece!
					std::pair<Pieces, PieceColor> capPiece = capturePiece(boardCoords);
					endGame(capPiece);
					getThePlayers().switchTurn();
				}
			}
		}
	}
}

void GamePvEState::endGame(const std::pair<Pieces, PieceColor> &piece)
{

	if (piece.first == King)
	{

		if (piece.second == White)
			setWinner(Black);
		else
			setWinner(White);

	//Instantiate the game end state
		requestStackPush(States::GamePvEEnd);//Game PvE End
	}
}

void GamePvEState::initPlayerColor()
{
	srand(time(NULL));
	PieceColor color = PieceColor(rand() % 2);

	this->playerColor = color;

	if (this->playerColor == White)
	{
		this->aiColor = Black;
	}
	else
	{
		this->aiColor = White;
	}

}