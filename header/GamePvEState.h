#ifndef GAME_PVE_STATE_H
#define GAME_PVE_STATE_H


#include "GamePvPState.h"
#include "AIplayer.h"

class GamePvEState : public GamePvPState
{


public:
	GamePvEState(StateStack & stack, Context context);

	~GamePvEState();

	void mouseButtonPressed(const sf::Event & event);
	bool update(sf::Time dt);

private:
	//Set the color of player and AI randomly
	void initPlayerColor();

	const sf::Time nextUpdate = sf::seconds(3);

	void endGame(const std::pair<Pieces, PieceColor> &piece);
	
	sf::Time elapsedTime = sf::Time();

private:

	PieceColor playerColor;
	PieceColor aiColor;

	AI ai; 

	



};


#endif