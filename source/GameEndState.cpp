#include "..\header\GameEndState.h"


GameEndState::GameEndState(StateStack & stack, Context context) : State(stack, context)
{
	
	setGOMessage();
	setNo();
	setYes();
	setPlayAgain();
}

GameEndState::~GameEndState()
{

}

void GameEndState::draw()
{
	drawMessages();
}

bool GameEndState::update(sf::Time dt)
{
	
	return true;
}

bool GameEndState::handleEvent(const sf::Event & event)
{

	if (event.type == sf::Event::Resized)
	{
		getContext().window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		//check where it was pressed
		//draw the legal moves

		mouseButtonPressed(event);
		return false;
	}

	return true;
}

void GameEndState::setGOMessage()
{
	int x = getContext().window->getSize().x;
	int y = getContext().window->getSize().y;

	gameOverMessage.setFont(*getContext().font1);
	gameOverMessage.setFillColor(sf::Color::Red);

	if (*getContext().whoWon == Black)
	{
		gameOverMessage.setString("Black Wins");
	}
	else
		gameOverMessage.setString("White Wins");

	gameOverMessage.setCharacterSize(x * 0.07);
	gameOverMessage.setPosition(x * .28, y * .25);
}

void GameEndState::setYes()
{
	int x = getContext().window->getSize().x;
	int y = getContext().window->getSize().y;

	yes.setFont(*getContext().font2);
	yes.setFillColor(sf::Color::Red);

	yes.setString("Yes");
	
	yes.setCharacterSize(x * 0.05);
	
}

void GameEndState::setNo()
{
	int x = getContext().window->getSize().x;
	int y = getContext().window->getSize().y;

	no.setFont(*getContext().font2);
	no.setFillColor(sf::Color::Red);
	
	no.setString("No");
	
	no.setCharacterSize(x * 0.05);
	
}

void GameEndState::setPlayAgain()
{
	int x = getContext().window->getSize().x;
	int y = getContext().window->getSize().y;

	PlayAgain.setFont(*getContext().font2);
	PlayAgain.setFillColor(sf::Color::Red);

	PlayAgain.setString("Play again?");

	PlayAgain.setCharacterSize(x * 0.05);
}


void GameEndState::mouseButtonPressed(const sf::Event &event)
{
	
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*(getContext().window)));
		sf::FloatRect yesBounds = yes.getGlobalBounds();
		sf::FloatRect noBounds = no.getGlobalBounds();

		//sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*(getContext().window)));
		//Check if mouse in yes bounds
		if (mousePos.x > yesBounds.left && mousePos.x < yesBounds.left + yesBounds.width)
		{
			if (mousePos.y > yesBounds.top && mousePos.y < yesBounds.top + yesBounds.height)
			{
				State::requestStackPop();
				State::requestStackPop();
				State::requestStackPush(States::Game);
			}
		}
		//Check if mouse in no bounds. Pop out to menu state
		if (mousePos.x > noBounds.left && mousePos.x < noBounds.left + noBounds.width)
		{
			if (mousePos.y > noBounds.top && mousePos.y < noBounds.top + noBounds.height)
			{
				State::requestStackPop();
				State::requestStackPop();
			}
		}
	
	}

}

void GameEndState::drawMessages()
{
	int x = getContext().window->getSize().x;
	int y = getContext().window->getSize().y;

	PlayAgain.setCharacterSize(x * 0.05);
	PlayAgain.setPosition(x * .355, y * .38);

	no.setCharacterSize(x * 0.05);
	no.setPosition(x * .465, y * .55);

	yes.setCharacterSize(x * 0.05);
	yes.setPosition(x * .46, y * .47);

	gameOverMessage.setCharacterSize(x * 0.07);
	gameOverMessage.setPosition(x * .28, y * .25);

	mouseHoverHighlight(yes);
	mouseHoverHighlight(no);

	getContext().window->draw(gameOverMessage);
	getContext().window->draw(no);
	getContext().window->draw(yes);
	getContext().window->draw(PlayAgain);
}


void GameEndState::mouseHoverHighlight(sf::Text &message)
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*(getContext().window)));

	sf::FloatRect messageBounds = message.getGlobalBounds();

	if (mousePos.x > messageBounds.left && mousePos.x < messageBounds.left + messageBounds.width 
		&& mousePos.y > messageBounds.top && mousePos.y < messageBounds.top + messageBounds.height)
	{
		message.setColor(sf::Color::Green);	
	}
	else
		message.setColor(sf::Color::Red);
}