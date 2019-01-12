#include "..\header\Menu.h"

MainMenu::MainMenu(StateStack & stack, Context context) : State(stack, context)
{
	setChess();
	setPvP();
	setPvE();
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

void MainMenu::setPvP()
{
	pvp.setString("Player vs Player");
	pvp.setFont(*getContext().font2);
	pvp.setColor(sf::Color::White);
}
void MainMenu::setPvE()
{
	pve.setString("Player vs Computer");
	pve.setFont(*getContext().font2);
	pve.setColor(sf::Color::Blue);
}


void MainMenu::drawMenu()
{
	int x = getContext().window->getSize().x;
	int y = getContext().window->getSize().y;
	
	chess.setCharacterSize(x * .07);
	pvp.setCharacterSize(x * .05);
	pve.setCharacterSize(x * .05);
	
	int chess_x = chess.getLocalBounds().width;
	int pvp_x = pvp.getLocalBounds().width;
	int pve_x = pve.getLocalBounds().width;

	chess.setPosition((x - chess_x) / 2, y * .3);
	pvp.setPosition((x - pvp_x)/2, y * .42);
	pve.setPosition((x - pve_x)/2, y * .50);

	mouseHoverHighlight(pvp);
	mouseHoverHighlight(pve);

	getContext().window->draw(chess);
	getContext().window->draw(pvp);
	getContext().window->draw(pve);
}

void MainMenu::mouseButtonPressed(const sf::Event &event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*(getContext().window)));
		sf::FloatRect pvpBounds = pvp.getGlobalBounds();
		sf::FloatRect pveBounds = pve.getGlobalBounds();

		if (mousePos.x > pvpBounds.left && mousePos.x < pvpBounds.left + pvpBounds.width)
		{
			if (mousePos.y > pvpBounds.top && mousePos.y < pvpBounds.top + pvpBounds.height)
			{
				State::requestStackPush(States::GamePvP);
			}
		}

		if (mousePos.x > pveBounds.left && mousePos.x < pveBounds.left + pveBounds.width)
		{
			if (mousePos.y > pveBounds.top && mousePos.y < pveBounds.top + pveBounds.height)
			{
				State::requestStackPush(States::GamePvE);
			}
		}
	}
}