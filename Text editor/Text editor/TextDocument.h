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
	sf::RenderWindow *pDrawingWindow;

	GapBuffer gapBuffer;
	Cursor cursor;
	Gui gui;

	GapBuffer sndGapBuffer;
	std::vector<bool> keysPressed;
	//0 = shift, 1 = up, 2 = left, 3 = down, 4 = right

	void saveFile(std::string);
	void openFile(std::string);
	bool handleSpecialUnicode(sf::Event&);
	void handleGuiInput(sf::Event&);
	void handleArrowPresses(sf::Event&);
	std::string readOutputFileName();
	std::string readInputFileName();

public:
	TextDocument(sf::RenderWindow&);

	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void update(float);
	void checkInput(sf::Event&);


};


#endif //TEXTDOCUMENT_H_