#include "..\header\Menu.h"

MainMenu::MainMenu(StateStack & stack, Context context) : State(stack, context)
{
	setChess();
	setPlay();
	setHelp();
}


void MainMenu::draw()
{
	drawMenu();
}

bool MainMenu::update(sf::Time dt)
{

	return true;
}


bool MainMenu::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::Resized)
	{
		getContext().window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{

		mouseButtonPressed(event);
		return false;
	}
	return true;
}



void MainMenu::mouseHoverHighlight(sf::Text &message)
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

void MainMenu::setChess()
{
	chess.setString("Chess");
	chess.setFont(*getContext().font1);
	chess.setColor(sf::Color::Red);
}

void MainMenu::setPlay()
{
	play.setString("Play");
	play.setFont(*getContext().font2);
	play.setColor(sf::Color::White);
}
void MainMenu::setHelp()
{
	help.setString("Help");
	help.setFont(*getContext().font2);
	help.setColor(sf::Color::Blue);
}


void MainMenu::drawMenu()
{
	int x = getContext().window->getSize().x;
	int y = getContext().window->getSize().y;

	chess.setCharacterSize(x * .07);
	chess.setPosition(x * .38, y * .3);

	play.setCharacterSize(x * .05);
	play.setPosition(x * .43, y * .42);

	help.setCharacterSize(x * .05);
	help.setPosition(x * .43, y * .50);

	mouseHoverHighlight(play);
	mouseHoverHighlight(help);

	getContext().window->draw(chess);
	getContext().window->draw(play);
	getContext().window->draw(help);
}

void MainMenu::mouseButtonPressed(const sf::Event &event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*(getContext().window)));
		sf::FloatRect playBounds = play.getGlobalBounds();
		sf::FloatRect helpBounds = help.getGlobalBounds();

		if (mousePos.x > playBounds.left && mousePos.x < playBounds.left + playBounds.width)
		{
			if (mousePos.y > playBounds.top && mousePos.y < playBounds.top + playBounds.height)
			{
				State::requestStackPush(States::Game);
			}
		}
	}
}