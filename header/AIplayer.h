#ifndef AI_PLAYER_H
#define AI_PLAYER_H



#include <algorithm>
#include <stdlib.h>
#include "Moves.h"
#include "GameStateIdentifiers.h"



//Struct for holding the value of a particular piece occupying a space
struct SpaceValue
{
	SpaceValue(int king, int bishop, int knight, int pawn, int rook, int queen);

	

	int king;
	int bishop;
	int knight;
	int pawn;
	int rook;
	int queen;
};

typedef std::vector<std::vector<SpaceValue>> ValueBoard;

class AI
{
public:


	AI() { gameBoard = Gameboard(0);
		   aiColor = White;
	     }

	AI(const Gameboard & gameBoard, PieceColor aiColor, Moves & moves);
	~AI();

	//Return 1)The piece to be moved 2)Where it will be moved
	std::pair<sf::Vector2i, sf::Vector2i> getMoveAndGetSelected();
	PieceColor getColor() { return this->aiColor; }

private:
    std::pair<sf::Vector2i, sf::Vector2i> findMoveHelper(std::list<GamePiece> * enemyPieces, std::list<GamePiece> * friendPieces);

	std::pair<sf::Vector2i, sf::Vector2i> findMove(std::list<GamePiece> * enemyPieces, std::list<GamePiece> * friendPieces,
		std::vector<std::vector<std::list<sf::Vector2f> *>> & possMoves);

	int rateMove(GamePiece & piece, sf::Vector2f & move, std::list<GamePiece> & enemyPieces, std::vector<std::vector<std::list<sf::Vector2f> *>> & possMoves);

	std::pair<std::list<GamePiece> *, std::list<GamePiece> *> getFriendandEnemyPieces();
	

	sf::Vector2f getKingPos(std::list<GamePiece> * friendPieces);

	void initValueBoard();

	int getSpaceValue(sf::Vector2f & move, GamePiece & piece);


private:

	Gameboard gameBoard;
	ValueBoard valueBoard;
	PieceColor aiColor;
	Moves moves;

};

#endif // !AI_PLAYER_H