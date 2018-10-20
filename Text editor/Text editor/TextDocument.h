#ifndef TEXTDOCUMENT_H_
#define TEXTDOCUMENT_H_

#include <iostream>
#include "SFML/Graphics.hpp"
#include "GapBuffer.h"
#include "Cursor.h"
#include <fstream>

class TextDocument {

	sf::Font font;
	sf::Text drawableText;
	GapBuffer gapBuffer;

	Cursor cursor;

	void saveToFile(std::string);

public:
	TextDocument();

	void draw(sf::RenderWindow&);
	void update();
	void checkInput(sf::Event&);


};


#endif //TEXTDOCUMENT_H_