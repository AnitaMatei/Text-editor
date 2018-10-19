#ifndef CURSOR_H_
#define CURSOR_H_

#include <iostream>
#include "SFML/Graphics.hpp"

class Cursor {

	sf::RectangleShape drawableBody;


public:
	Cursor();

	void draw(sf::RenderWindow&);
	void update(sf::Vector2f);
	//the argument represents the position where the cursor should be placed
	void checkInput(sf::Event&);
	
};


#endif //CURSOR_H_