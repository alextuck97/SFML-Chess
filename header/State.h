#ifndef STATE_H
#define STATE_H


#include <SFML\Graphics.hpp>
#include <memory>

#include "GameStateIdentifiers.h"

namespace States
{
	enum ID
	{
		None,
		Title,
		Menu,
		GamePvP,
		GamePvE,
		GamePvEEnd,
		GameEnd
	};
}

class StateStack;//Forward declaration to avoid looping dependencies
//Can do things with pointers and references to the type, but since
//it is incomplete cannot do anything with its members


class State
{
public:
	typedef std::unique_ptr<State> Ptr;
	struct Context
	{   //Add Universal fonts here
		Context(sf::RenderWindow & window, sf::Font & font1, sf::Font & font2, PieceColor & winner);
		sf::RenderWindow * window;
		sf::Font *font1;
		sf::Font *font2;
		PieceColor * whoWon;

		void setWinner(PieceColor winner) {
			*whoWon = winner;
		}
	};

	State(StateStack & stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event & event) = 0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();
	

	Context getContext() const;
	void setWinner(PieceColor winner);
	

private:
	StateStack * mStack;
	Context mContext;


};


#endif // !STATE_H
