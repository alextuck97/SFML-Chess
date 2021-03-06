#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <iostream>
#include <list>

#include "State.h"
#include "GameStateIdentifiers.h"
#include "Moves.h"
#include "Player.h"

class GamePvPState : public State
{
public:

	GamePvPState(StateStack & stack, Context context);

	~GamePvPState();

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event & event);

	std::list<sf::Vector2f> * getMoves(GamePiece piece);
	
	Gameboard & getGameBoard() { return this->gameBoard; }


	//Initialize both players pieces to starting positions
	void initializeBoard();

	void initTextureMap();

	void drawGameBoard();
	
	void drawPiece(const GamePiece & gamePiece, float x, float y);

	void drawPossibleMoves();

	//Switches black to white or white to black
	void swapColor(sf::RectangleShape & boardSquare);
	
	//Handles what happens when the mouse is clicked
	virtual void mouseButtonPressed(const sf::Event & event);

	//Return true if the selected square is a possible move
	bool inPossibleMoves(sf::Vector2i selectedMove);

	//Capture and return  the captured piece
	std::pair<Pieces, PieceColor> capturePiece(sf::Vector2i boardCoords);

	//Move piece to board coords
	void movePiece(sf::Vector2i boardCoords);

	//Takes a piece, checks if its a king and ends the game if so
	virtual void endGame(const std::pair<Pieces, PieceColor> &piece);

	Player & getThePlayers() { return this->thePlayers; }

	std::list<sf::Vector2f> * getPossibleMoves() { return this->possibleMoves; }

	void setPossibleMoves(std::list<sf::Vector2f> * newMoves) { this->possibleMoves = newMoves; }

	Moves & getMoves() { return mMoves; }

private:

	Gameboard gameBoard;

	Moves mMoves;

	std::map<std::pair<Pieces, PieceColor>, sf::IntRect> textureRects;

	Player thePlayers;

	sf::Texture pieceTexture;

	sf::Font gameFont;

	sf::Text text;

	//Flag to tell if game is over or not
	bool gameOver = false;

	//Contains the possible moves for drawing
	std::list<sf::Vector2f> * possibleMoves;
};





#endif // !GAME_STATE_H
