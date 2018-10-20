#include "TextDocument.h"

TextDocument::TextDocument() 
	:gapBuffer(),
	cursor()
{
	font.loadFromFile("Fonts/arial.ttf");
	drawableText.setFont(font);
	drawableText.setFillColor(sf::Color::White);
	drawableText.setCharacterSize(21);

}

void TextDocument::draw(sf::RenderWindow &drawingWindow) {
	drawingWindow.draw(drawableText);

	cursor.draw(drawingWindow);
}

void TextDocument::update() {
	drawableText.setString(gapBuffer.getText());
	
	cursor.update(drawableText.findCharacterPos(gapBuffer.getPreLength()),gapBuffer.getGapPosition());
}

void TextDocument::checkInput(sf::Event &sfmlEvent) {

	cursor.checkInput(sfmlEvent);
	if (sfmlEvent.type == sf::Event::TextEntered) {
		if (sfmlEvent.text.unicode == 19)
			saveToFile("file.txt");
		else gapBuffer.insertText(sfmlEvent.text.unicode);	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		gapBuffer.moveGap(-1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		gapBuffer.moveGap(1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))	{
		gapBuffer.moveGapUp();
	}
}

void TextDocument::saveToFile(std::string fileName) {
	std::string text = gapBuffer.getText();
	std::ofstream fout(fileName);

	for (int i = 0; i < text.size(); i++) {
		fout << text[i];
	}
	fout.close();
}