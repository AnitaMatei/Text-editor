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

void Cursor::update(sf::Vector2f position) {
	drawableBody.setPosition(position.x, position.y);
}

void Cursor::checkInput(sf::Event &sfmlEvent) {
}