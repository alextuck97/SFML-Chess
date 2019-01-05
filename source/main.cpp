#include <iostream>
#include <SFML\Graphics.hpp>
#include "..\header\GameWrapper.h"

int main(void)
{
	
	sf::Font font1, font2;
	PieceColor winner = Unaffiliated;
	font1.loadFromFile("resources/NeonMachine.ttf");
	font2.loadFromFile("resources/BRLNSB.ttf");
	Game game(font1, font2, winner);
	game.run();


	return 0;
}