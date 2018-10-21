#include "TextEditor.h"

TextEditor::TextEditor(int x, int y) 
	: drawingWindow(sf::VideoMode(x,y),"Text Editor"),
	resX(x), resY(y),
	myDoc()
{
	drawingWindow.setVerticalSyncEnabled(true);
	//myDoc.openFile("text.txt");
}

void TextEditor::draw() {
	drawingWindow.clear(sf::Color(38,38,38));
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
		
		if (sfmlEvent.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, sfmlEvent.size.width, sfmlEvent.size.height);
			drawingWindow.setView(sf::View(visibleArea));
		}

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