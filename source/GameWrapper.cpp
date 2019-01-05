#include "..\header\GameWrapper.h"

Game::Game(sf::Font & font1, sf::Font &font2, PieceColor & winner) : mWindow(VideoMode(800, 600), "Chess"), font1(font1),
font2(font2), mStack(State::Context(mWindow, font1, font2, winner))// mContext(mWindow),
{
	mStack.registerState<GameState>(States::Game);
	mStack.registerState<GameEndState>(States::GameEnd);
	mStack.registerState<MainMenu>(States::Menu);
	mStack.pushState(States::Menu);
}



void Game::run()
{

	while (mWindow.isOpen())
	{
		
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

		render();
	}

}


void Game::render()
{
	mWindow.clear();
	mStack.draw();//Stack has access to window through context
	mWindow.display();

}