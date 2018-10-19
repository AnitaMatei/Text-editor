#include "TextEditor.h"

TextEditor::TextEditor(int x, int y) 
	: drawingWindow(sf::VideoMode(x,y),"Text Editor"),
	resX(x), resY(y),
	myDoc()
{
	drawingWindow.setVerticalSyncEnabled(true);
}

void TextEditor::draw() {
	drawingWindow.clear(sf::Color::Red);
	myDoc.draw(drawingWindow);
	//drawingWindow.draw();
	drawingWindow.display();
}

void TextEditor::update() {
	myDoc.update();
}

void TextEditor::checkInput() {
	while (drawingWindow.pollEvent(sfmlEvent)) {

		if (sfmlEvent.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			drawingWindow.close();
		//the window closes if you press X or escape key
		myDoc.checkInput(sfmlEvent);
	
	}	
}

void TextEditor::start() {

	while (drawingWindow.isOpen()) {
		checkInput();

		update();

		draw();
	}


}