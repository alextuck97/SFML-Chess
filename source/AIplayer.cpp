#include "..\header\AIplayer.h"

SpaceValue::SpaceValue(int king, int bishop, int knight, int pawn, int rook, int queen)
{
	this->king = king;
	this->bishop = bishop;
	this->knight = knight;
	this->pawn = pawn;
	this->rook = rook;
	this->queen = queen;
}



AI::AI(const Gameboard & gameBoard, PieceColor aiColor, Moves & moves) : valueBoard(8)
{
	this->gameBoard = gameBoard;
	this->aiColor = aiColor;
	this->moves = moves;

	initValueBoard();

}


AI::~AI()
{

}




std::pair<sf::Vector2i, sf::Vector2i> AI::getMoveAndGetSelected()
{
	std::pair<sf::Vector2i, sf::Vector2i> pieceAndMove;

	std::list<GamePiece> * enemyPieces = nullptr;
	std::list<GamePiece> * friendPieces = nullptr;
    
	std::tie(friendPieces, enemyPieces) = this->getFriendandEnemyPieces();
	
	pieceAndMove = findMoveHelper(enemyPieces, friendPieces);
	
	
	
	delete(enemyPieces);
	delete(friendPieces);
	
	return pieceAndMove;
}


std::pair<sf::Vector2i, sf::Vector2i> AI::findMoveHelper(std::list<GamePiece> * enemyPieces, std::list<GamePiece> * friendPieces)
{
	GamePiece bestPiece(None, NA, sf::Vector2f(0, 0), this->aiColor,0, true);
	sf::Vector2f bestMove(0, 0);

	sf::Vector2f kingPos = this->getKingPos(friendPieces);

    int bestScore = 0;
	std::vector<std::vector<std::list<sf::Vector2f> *>> possibleMovesHolder(8);

	//Initialize possible moves holder to nullptr
	for (auto itr1 = possibleMovesHolder.begin(); itr1 != possibleMovesHolder.end(); itr1++)
	{
		for (int i = 0; i < 8; i++)
		{
			itr1->push_back(nullptr);
		}
	}

	
	//Add all possible moves to move holder so they can be easily accessed by the coordinates of corresponding piece
	for (auto itr = enemyPieces->begin(); itr != enemyPieces->end(); itr++)
	{
		possibleMovesHolder[itr->position.y][itr->position.x] = this->moves.getMoves(*itr);	
	}
	for (auto itr = friendPieces->begin(); itr != friendPieces->end(); itr++)
	{
		possibleMovesHolder[itr->position.y][itr->position.x] = this->moves.getMoves(*itr);
	}
	

	

	//(pieceCoords, boardCoords)
	return findMove(enemyPieces, friendPieces, possibleMovesHolder);
}

//Function tht goes through all the moves and finds the best one
std::pair<sf::Vector2i, sf::Vector2i> AI::findMove(std::list<GamePiece> * enemyPieces, std::list<GamePiece> * friendPieces,
	 std::vector<std::vector<std::list<sf::Vector2f> *>> & possMoves)
{
	int rating = -INFINITY;//Guarantees a rating is always picked
	
	int newRating = 0;

	//List of all moves with high rating. Moves is randomly selected if many moves have same rating
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> bestMoves;

	for (auto piece = friendPieces->begin(); piece != friendPieces->end(); piece++)
	{
		std::list<sf::Vector2f> * moves = possMoves[piece->position.y][piece->position.x];
		
		for (auto move = moves->begin(); move != moves->end(); move++)
		{
			newRating = rateMove(*piece, *move, *enemyPieces, possMoves);

			if (newRating > rating)
			{
				bestMoves.clear();
				rating = newRating;
				//Push piece and move to a list for random selection if more that one optimal move
				bestMoves.push_back(std::pair<sf::Vector2i, sf::Vector2i>(piece->position, *move));//Always push back first one to avoid empty list
			}
			else if (newRating == rating)
			{
				bestMoves.push_back(std::pair<sf::Vector2i, sf::Vector2i>(piece->position, *move));
			}

		}
	}
	srand(time(NULL));
	int randNum = rand() % bestMoves.size();

	
	
	return bestMoves[randNum];
}

//Function that assigns a value to the move
int AI::rateMove(GamePiece & piece, sf::Vector2f & move, std::list<GamePiece> & enemyPieces, std::vector<std::vector<std::list<sf::Vector2f> *>> & possMoves)
{
	int rating = getSpaceValue(move, piece);

	for (auto epiece = enemyPieces.begin(); epiece != enemyPieces.end(); epiece++)
	{   //Check if move allows capture of a piece
		if (epiece->position == move)
		{
			rating += epiece->value;
		}

		//Check if the move is in enemy pieces possible moves
		bool found = (std::find(possMoves[epiece->position.y][epiece->position.x]->begin(), possMoves[epiece->position.y][epiece->position.x]->end(), move) != possMoves[epiece->position.y][epiece->position.x]->end());

		if (found)
		{
			rating -= piece.value;
		}

		//Create a new piece with its location as the move, and look at the new potential moves
		std::list<sf::Vector2f>* newMoves = this->moves.getMoves(GamePiece(piece.piece, piece.orientation, move, piece.color, piece.value, piece.inPlay));

		for (auto newMove = newMoves->begin(); newMove != newMoves->end(); newMove++)
		{
			if (epiece->position == *newMove)
			{
				rating += epiece->value / 2;
			}
		}

	}



	return rating;
}

std::pair<std::list<GamePiece> *, std::list<GamePiece> *> AI::getFriendandEnemyPieces()
{
	std::list<GamePiece> * friendPieces = new std::list<GamePiece>;
	std::list<GamePiece> * enemyPieces = new std::list<GamePiece>;

	for (auto row = gameBoard.begin(); row != gameBoard.end(); row++)
	{
		for (auto square = row->begin(); square != row->end(); square++)
		{
			if ((*square)->color == aiColor)
			{
				friendPieces->push_back(**square);
			}
			else if ((*square)->color != aiColor && (*square)->color != Unaffiliated)
			{
				enemyPieces->push_back(**square);
			}
		}
	}

	return std::pair<std::list<GamePiece> *, std::list<GamePiece> *>(friendPieces, enemyPieces);
}

int AI::getSpaceValue(sf::Vector2f & move, GamePiece & piece)
{
	switch (piece.piece) {
	case King:
		return valueBoard[move.y][move.x].king;

	case Knight:
		return valueBoard[move.y][move.x].knight;

	case Bishop:
		return valueBoard[move.y][move.x].bishop;

	case Pawn:
		return valueBoard[move.y][move.x].pawn;

	case Queen:
		return valueBoard[move.y][move.x].queen;

	case Rook:
		return valueBoard[move.y][move.x].rook;
	}
}

sf::Vector2f AI::getKingPos(std::list<GamePiece> * friendPieces)
{//Return the position of the king
	for (auto itr = friendPieces->begin(); itr != friendPieces->end(); itr++)
	{
		if (itr->piece == King)
		{
			return itr->position;
		}
	}
	return sf::Vector2f(-1, -1);
}

//Assign values to the board spaces
void AI::initValueBoard()
{
	//Assign valye to row 0
	for (int i = 0; i < 8; i++)
		valueBoard[0].push_back(SpaceValue(i / 2, 0, 0, 0, 0, 0));

	//Assign value to row 1
	valueBoard[1].push_back(SpaceValue(0, 5, 0, 0, 5, 5));
	valueBoard[1].push_back(SpaceValue(0, 10, 0, 0, 0, 10));

	for(int i = 0; i < 4; i++)
		valueBoard[1].push_back(SpaceValue(0, 0, 0, 0, 6, 0));

	valueBoard[1].push_back(SpaceValue(0, 10, 0, 0, 0, 10));
	valueBoard[1].push_back(SpaceValue(0, 5, 0, 0, 5, 5));

	//Assign value to row 2
	valueBoard[2].push_back(SpaceValue(0, 8, 0, 1, 3, 8));
	valueBoard[2].push_back(SpaceValue(0, 8, 0, 0, 5, 8));
	valueBoard[2].push_back(SpaceValue(0, 10, 6, 3, 2, 10));
	valueBoard[2].push_back(SpaceValue(0, 5, 7, 3, 2, 5));
	valueBoard[2].push_back(SpaceValue(0, 5, 7, 3, 2, 5));
	valueBoard[2].push_back(SpaceValue(0, 10, 6, 3, 2, 10));
	valueBoard[2].push_back(SpaceValue(0, 8, 0, 0, 5, 8));
	valueBoard[2].push_back(SpaceValue(0, 8, 0, 1, 3, 8));

	//Assign value row 3
	valueBoard[3].push_back(SpaceValue(0, 0, 0, 5, 7, 7));
	valueBoard[3].push_back(SpaceValue(0, 6, 6, 5, 7, 7));
	valueBoard[3].push_back(SpaceValue(0, 4, 10, 8, 5, 4));
	valueBoard[3].push_back(SpaceValue(0, 4, 9, 10, 5, 4));
	valueBoard[3].push_back(SpaceValue(0, 4, 9, 10, 5, 4));
	valueBoard[3].push_back(SpaceValue(0, 4, 10, 8, 5, 4));
	valueBoard[3].push_back(SpaceValue(0, 6, 6, 5, 7, 7));
	valueBoard[3].push_back(SpaceValue(0, 0, 0, 5, 7, 7));

	//Assign value row 4
	valueBoard[4].push_back(SpaceValue(0, 0, 0, 5, 7, 7));
	valueBoard[4].push_back(SpaceValue(0, 6, 6, 5, 7, 7));
	valueBoard[4].push_back(SpaceValue(0, 4, 10, 8, 5, 4));
	valueBoard[4].push_back(SpaceValue(0, 4, 9, 10, 5, 4));
	valueBoard[4].push_back(SpaceValue(0, 4, 9, 10, 5, 4));
	valueBoard[4].push_back(SpaceValue(0, 4, 10, 8, 5, 4));
	valueBoard[4].push_back(SpaceValue(0, 6, 6, 5, 7, 7));
	valueBoard[4].push_back(SpaceValue(0, 0, 0, 5, 7, 7));

	//Assign value to row 5
	valueBoard[5].push_back(SpaceValue(0, 8, 0, 1, 3, 8));
	valueBoard[5].push_back(SpaceValue(0, 8, 0, 0, 5, 8));
	valueBoard[5].push_back(SpaceValue(0, 10, 6, 3, 2, 10));
	valueBoard[5].push_back(SpaceValue(0, 5, 7, 3, 2, 5));
	valueBoard[5].push_back(SpaceValue(0, 5, 7, 3, 2, 5));
	valueBoard[5].push_back(SpaceValue(0, 10, 6, 3, 2, 10));
	valueBoard[5].push_back(SpaceValue(0, 8, 0, 0, 5, 8));
	valueBoard[5].push_back(SpaceValue(0, 8, 0, 1, 3, 8));

	//Assign value to row 6
	valueBoard[6].push_back(SpaceValue(0, 5, 0, 0, 5, 5));
	valueBoard[6].push_back(SpaceValue(0, 10, 0, 0, 0, 10));

	for (int i = 0; i < 4; i++)
		valueBoard[6].push_back(SpaceValue(0, 0, 0, 0, 6, 0));

	valueBoard[6].push_back(SpaceValue(0, 10, 0, 0, 0, 10));
	valueBoard[6].push_back(SpaceValue(0, 5, 0, 0, 5, 5));

	//Assign valye to row 7
	for (int i = 0; i < 8; i++)
		valueBoard[7].push_back(SpaceValue(i / 2, 0, 0, 0, 0, 0));
}