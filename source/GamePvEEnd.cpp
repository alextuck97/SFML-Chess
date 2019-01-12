#include "..\header\GamePvEEnd.h"


PvEEndState::PvEEndState(StateStack & stack, Context context) : GameEndState(stack, context)
{

}

void PvEEndState::mouseButtonPressed(const sf::Event &event)
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
				State::requestStackPush(States::GamePvE);
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