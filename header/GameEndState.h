#ifndef GAME_END_STATE_H
#define GAME_END_STATE_H

#include "State.h"

//State displayed when a player wins

class GameEndState : public State
{

public:
	GameEndState(StateStack & stack, Context context);

	~GameEndState();

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event & event);

private:
	//Initialize the game over message
	void setGOMessage();

	void setYes();

	void setNo();

	void setPlayAgain();

	void mouseButtonPressed(const sf::Event &event);

	//Resize messages too
	void drawMessages();

	//Change message color if mouse over it
	void mouseHoverHighlight(sf::Text &message);

private:
	sf::Text gameOverMessage;

	sf::Text yes;
	sf::Text no;
	sf::Text PlayAgain;



};



#endif // !GAME_END_STATE_H

