#ifndef TEXTEDITOR_H_
#define TEXTEDITOR_H_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextDocument.h"

class TextEditor {

	sf::RenderWindow drawingWindow;
	sf::Event sfmlEvent;
	int resX, resY;

	TextDocument myDoc;

	void draw();
	//draws on the window
	void update();
	//updates objects, like the text
	void checkInput();
	//checks if a button press happened and takes action

public:
	TextEditor(int, int);

	void start();
	//main loop for the program where the drawing, updating and checking for input happens



};


#endif //TEXTEDITOR_H_