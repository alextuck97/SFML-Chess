#include <SFML\Graphics.hpp>

#include "State.h"

class MainMenu : public State
{

public:

	MainMenu(StateStack & stack, Context context);

	~MainMenu() {};

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event & event);

private:
	void mouseHoverHighlight(sf::Text &message);

	void setChess();
	void setPvP();
	void setPvE();

	void drawMenu();

	//Click play or help
	void mouseButtonPressed(const sf::Event &event);

	sf::Text chess;
	sf::Text pvp;
	sf::Text pve;



};