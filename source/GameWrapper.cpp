#include "..\header\GameWrapper.h"

Game::Game(sf::Font & font1, sf::Font &font2, PieceColor & winner) : mWindow(VideoMode(800, 600), "Chess"), font1(font1),
font2(font2), mStack(State::Context(mWindow, font1, font2, winner))// mContext(mWindow),
{
	mStack.registerState<GamePvPState>(States::GamePvP);
	mStack.registerState<GamePvEState>(States::GamePvE);
	mStack.registerState<GameEndState>(States::GameEnd);
	mStack.registerState<MainMenu>(States::Menu);
	mStack.registerState<PvEEndState>(States::GamePvEEnd);
	mStack.pushState(States::Menu);
}



void Game::run()
{
	sf::Clock clock;
	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mWindow.close();
			else
			{
				mStack.handleEvent(event);
				
			}
		}
		mStack.update(dt);
		render();
	}

}


void Game::render()
{
	mWindow.clear();
	mStack.draw();//Stack has access to window through context
	mWindow.display();

}