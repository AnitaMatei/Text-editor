#include "Gui.h"

Gui::Gui(sf::Vector2u screenRes)
	:menuBar()
{
	menuBar.setFillColor(sf::Color(169,169,169));
	menuBar.setSize(sf::Vector2f(screenRes.x,15));
	font.loadFromFile("Fonts/VeraMono.ttf");

	sf::Text temp;
	menuNames.push_back(temp);

	menuNames[0].setFont(font);
	menuNames[0].setCharacterSize(12);
	menuNames[0].setString("Save");
	menuNames[0].setFillColor(sf::Color::Black);
	menuNames[0].setPosition(sf::Vector2f(0, 0));
	menuNameBoxes.push_back(menuNames[0].getGlobalBounds());
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(menuBar);
	for (int i = 0; i < menuNames.size(); i++)
		target.draw(menuNames[i]);
}

int Gui::checkInput(sf::Event& sfmlEvent, sf::RenderWindow& drawingWindow) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sf::Vector2i mousePos(sf::Mouse::getPosition(drawingWindow));

		for (int i = 0; i < menuNameBoxes.size(); i++) {
			if (menuNameBoxes[i].contains(mousePos.x,mousePos.y)) {
				return 2;
			}
		}
	}

	return 1;
}
