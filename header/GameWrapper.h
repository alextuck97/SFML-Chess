#include <SFML\Graphics.hpp>
#include "StateStack.h"
#include "GameState.h"
#include "GameEndState.h"
#include "Menu.h"


using namespace sf;

class Game
{

public:

	//Game();

	Game(sf::Font &font1, sf::Font &font2, PieceColor & winner);

	void run();
	
	

private:
	void render();



private:
	RenderWindow mWindow;
	Font font1;
	Font font2;
	StateStack mStack;

	//State::Context mContext;
	

};