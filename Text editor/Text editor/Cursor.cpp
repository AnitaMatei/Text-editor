#include "Cursor.h"

Cursor::Cursor()
	:drawableBody(sf::Vector2f(1, 21)) 
{
	drawableBody.setPosition(0, 0);
	drawableBody.setFillColor(sf::Color::Black);
}

void Cursor::draw(sf::RenderWindow &drawingWindow) {
	drawingWindow.draw(drawableBody);
}

void Cursor::update() {
	drawableBody.setPosition(10 * position.x, 21 * position.y);
}

void Cursor::checkInput(sf::Event &sfmlEvent) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		if (position.x > 0)
			position.x--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		position.x++;
	}
}