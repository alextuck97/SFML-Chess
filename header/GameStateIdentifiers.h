#ifndef GAME_STATE_IDS_H
#define GAME_STATE_IDS_H
#include <vector>
#include <SFML\Graphics.hpp>



//Piece starting orientation
enum Orientation
{	
	NA,
	Left,
	Right,
	Royalty,
};

enum Pieces
{
	None,
	Pawn,
	Knight,
	Rook,
	Bishop,
	Queen,
	King
};

enum PieceColor
{
	Black,
	White,
	Unaffiliated
};

struct GamePiece
{
	GamePiece(Pieces piece, Orientation orientation, sf::Vector2f &position, PieceColor color,int value, bool inPlay);

	Pieces piece;
	Orientation orientation;
	sf::Vector2f position;
	PieceColor color;
	int value;
	bool inPlay;
};

typedef  std::vector<std::vector<GamePiece*>> Gameboard;



#endif // !GAME_STATE_IDS_H
