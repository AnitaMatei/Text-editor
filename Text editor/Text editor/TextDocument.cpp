#include "TextDocument.h"

TextDocument::TextDocument() :gapBuffer() {
	font.loadFromFile("Fonts/arial.ttf");
	drawableText.setFont(font);
	drawableText.setFillColor(sf::Color::White);
	drawableText.setCharacterSize(21);
}

void TextDocument::draw(sf::RenderWindow &drawingWindow) {
	drawingWindow.draw(drawableText);
}

void TextDocument::update() {
	drawableText.setString(gapBuffer.getText());
}

void TextDocument::checkInput(sf::Event &sfmlEvent) {

	if (sfmlEvent.type == sf::Event::TextEntered) {
		gapBuffer.insertText(sfmlEvent.text.unicode);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		gapBuffer.moveGap(-1);
	}
}