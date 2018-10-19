#include "TextDocument.h"

TextDocument::TextDocument() 
	:gapBuffer(),
	cursor()
{
	font.loadFromFile("Fonts/arial.ttf");
	drawableText.setFont(font);
	drawableText.setFillColor(sf::Color::Yellow);
	drawableText.setCharacterSize(21);

}

void TextDocument::draw(sf::RenderWindow &drawingWindow) {
	drawingWindow.draw(drawableText);

	cursor.draw(drawingWindow);
}

void TextDocument::update() {
	drawableText.setString(gapBuffer.getText());
	
	cursor.update(drawableText.findCharacterPos(gapBuffer.getPreLength()));
}

void TextDocument::checkInput(sf::Event &sfmlEvent) {

	cursor.checkInput(sfmlEvent);

	if (sfmlEvent.type == sf::Event::TextEntered) {
		gapBuffer.insertText(sfmlEvent.text.unicode);
		std::cout << sfmlEvent.text.unicode;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		gapBuffer.moveGap(-1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		gapBuffer.moveGap(1);
	}
}