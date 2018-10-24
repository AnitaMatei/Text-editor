#ifndef CURSOR_H_
#define CURSOR_H_

#include <iostream>
#include "SFML/Graphics.hpp"

class Cursor : public sf::Drawable{

	sf::RectangleShape drawableBody;
	sf::Vector2i cursorPosition;
	//the position of the cursor on the text, not on the screen
	float timePassed;
	int canDraw;
	//1 for drawing, -1 is not drawing

public:
	Cursor();

	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void update(sf::Vector2f, sf::Vector2i, float);
	//the arguments represents the position where the cursor should be placed and the position of the cursor in the text
	void checkInput(sf::Event&);
	
};


#endif //CURSOR_H_