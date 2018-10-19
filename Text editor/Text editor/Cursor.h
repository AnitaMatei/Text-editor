#ifndef CURSOR_H_
#define CURSOR_H_

#include "SFML/Graphics.hpp"

class Cursor {

	sf::RectangleShape drawableBody;
	sf::Vector2i position;
	//the position in the text, [line;column]


public:
	Cursor();

	void draw(sf::RenderWindow&);
	void update();
	void checkInput(sf::Event&);

};


#endif //CURSOR_H_