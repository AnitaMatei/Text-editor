#ifndef TEXTDOCUMENT_H_
#define TEXTDOCUMENT_H_

#include <iostream>
#include "SFML/Graphics.hpp"
#include "GapBuffer.h"
#include "Cursor.h"
#include "Gui.h"
#include <fstream>

class TextDocument : public sf::Drawable {

	sf::Font font;
	sf::Text drawableText;
	sf::Vector2u screenResolution;
	sf::RenderWindow *pDrawingWindow;

	GapBuffer gapBuffer;
	Cursor cursor;
	Gui gui;

	GapBuffer sndGapBuffer;
	bool highlightedText;
	//the second gap buffer will place its gap at the second end of the highlighted text

	void saveToFile(std::string);
	bool handleKeyCombinations(sf::Event&);
	void handleGuiInput(sf::Event&);

public:
	TextDocument(sf::RenderWindow&);

	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void update(float);
	void checkInput(sf::Event&);
	void openFile(std::string);


};


#endif //TEXTDOCUMENT_H_