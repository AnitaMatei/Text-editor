#ifndef TEXTDOCUMENT_H_
#define TEXTDOCUMENT_H_

#include "SFML/Graphics.hpp"
#include "GapBuffer.h"

class TextDocument {

	sf::Font font;
	sf::Text drawableText;
	GapBuffer gapBuffer;
	


public:
	TextDocument();

	void draw(sf::RenderWindow&);
	void update();
	void checkInput(sf::Event&);

};


#endif //TEXTDOCUMENT_H_