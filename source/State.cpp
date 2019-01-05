#include "..\header\State.h"
#include "..\header\StateStack.h"

State::State(StateStack & stack, Context context) : mStack(&stack), mContext(context)
{

}

State::~State()
{

}

State::Context::Context(sf::RenderWindow & window, sf::Font &font1, sf::Font &font2, PieceColor & winner) : window(&window), 
font1(&font1),font2(&font2), whoWon(&winner)
{
	//font1->loadFromFile("NeonMachine.ttf");
	
}

State::Context State::getContext() const
{
	return mContext;
}

void State::setWinner(PieceColor winner)
{
	*(mContext).whoWon = winner;
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}


void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}
