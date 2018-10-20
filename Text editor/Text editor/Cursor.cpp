#include "Cursor.h"

Cursor::Cursor()
	:drawableBody(sf::Vector2f(1, 21)) 
{
	drawableBody.setPosition(0, 0);
	drawableBody.setFillColor(sf::Color(230,230,230));
}

void Cursor::draw(sf::RenderWindow &drawingWindow) {
	drawingWindow.draw(drawableBody);
}

void Cursor::update(sf::Vector2f position, sf::Vector2i linePosition) {
	drawableBody.setPosition(position.x, position.y);
	cursorPosition = linePosition;
}

void Cursor::checkInput(sf::Event &sfmlEvent) {
}