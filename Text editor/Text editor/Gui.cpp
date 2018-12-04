#include "Gui.h"

Gui::Gui(sf::Vector2u screenRes)
	:menuBar()
{
	menuBar.setFillColor(sf::Color(211,211,211));
	menuBar.setSize(sf::Vector2f(screenRes.x,20));
	font.loadFromFile("Fonts/VeraMono.ttf");

	sf::Text temp;
	menuNames.push_back(temp);
	int buttonSeparation = 15; //nr of pixels between buttons

	menuNames[0].setFont(font);
	menuNames[0].setCharacterSize(15);
	menuNames[0].setString("Save");
	menuNames[0].setFillColor(sf::Color::Black);
	menuNames[0].setPosition(sf::Vector2f(0, 0));
	menuNameBoxes.push_back(menuNames[0].getGlobalBounds());

	menuNames.push_back(temp);
	menuNames[1].setFont(font);
	menuNames[1].setCharacterSize(15);
	menuNames[1].setString("Open");
	menuNames[1].setFillColor(sf::Color::Black);
	menuNames[1].setPosition(sf::Vector2f(menuNames[0].getLocalBounds().width+buttonSeparation, 0));
	menuNameBoxes.push_back(menuNames[1].getGlobalBounds());
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
			if (menuNameBoxes[i].contains(mousePos.x, mousePos.y)) {
				switch (i) {
				case 0:
					return 1;
					break;
				case 1:
					return 2;
					break;
				}
			
			}
		}
	}

	return 0;
}
