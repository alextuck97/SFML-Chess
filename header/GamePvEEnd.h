#ifndef GAME_PVE_END_H
#define GAME_PVE_END_H

#include "GameEndState.h"


class PvEEndState : public GameEndState
{

public:
	PvEEndState(StateStack & stack, Context context);

	~PvEEndState() {}


private:
	void mouseButtonPressed(const sf::Event &event);




};



#endif