#ifndef CURSOR_H_
#define CURSOR_H_

#include <iostream>
#include "SFML/Graphics.hpp"

class Cursor {

	sf::RectangleShape drawableBody;
	sf::Vector2i cursorPosition;
	//the position of the cursor on the text, not on the screen

public:
	Cursor();

	void draw(sf::RenderWindow&);
	void update(sf::Vector2f, sf::Vector2i);
	//the arguments represents the position where the cursor should be placed and the position of the cursor in the text
	void checkInput(sf::Event&);
	
};


#endif //CURSOR_H_