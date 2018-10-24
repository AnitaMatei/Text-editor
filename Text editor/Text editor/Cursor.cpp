#include "Cursor.h"

Cursor::Cursor()
	:drawableBody(sf::Vector2f(1, 21)) 
{
	drawableBody.setPosition(0, 0);
	drawableBody.setFillColor(sf::Color(230,230,230));
	timePassed = 0.f;
	canDraw = 1;
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	if(canDraw==1)
		target.draw(drawableBody);
}

void Cursor::update(sf::Vector2f position, sf::Vector2i linePosition, float deltaTime) {
	timePassed += deltaTime;

	if (timePassed > .5) {
		canDraw *=-1;
		timePassed = 0.f;
	}
	//every half a second the cursor will alternate between visible and invisible

	drawableBody.setPosition(position.x, position.y);
	cursorPosition = linePosition;
}

void Cursor::checkInput(sf::Event &sfmlEvent) {
}