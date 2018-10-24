#include "TextDocument.h"

TextDocument::TextDocument(sf::RenderWindow& drawingWindow) 
	:gapBuffer(),
	cursor(),
	gui(drawingWindow.getSize()),
	sndGapBuffer()
{
	font.loadFromFile("Fonts/VeraMono.ttf");
	drawableText.setFont(font);
	drawableText.setFillColor(sf::Color::White);
	drawableText.setCharacterSize(12);
	drawableText.setPosition(sf::Vector2f(0, 15));
	this->screenResolution = screenResolution;
	highlightedText = false;

	pDrawingWindow = &drawingWindow;
}

void TextDocument::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(drawableText);
	target.draw(gui);
	target.draw(cursor);
}

void TextDocument::update(float deltaTime) {
	drawableText.setString(gapBuffer.getText());

	cursor.update(drawableText.findCharacterPos(gapBuffer.getPreLength()),gapBuffer.getGapPosition(),deltaTime);
}

void TextDocument::checkInput(sf::Event &sfmlEvent) {

	cursor.checkInput(sfmlEvent);
	handleGuiInput(sfmlEvent);

	if (sfmlEvent.type == sf::Event::TextEntered) {
		if (handleKeyCombinations(sfmlEvent))
			gapBuffer.insertText(sfmlEvent.text.unicode);	
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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		gapBuffer.moveGapDown();
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

void TextDocument::openFile(std::string fileName) {
	std::string text;
	std::ifstream fin(fileName);
	int i = 0;
	while (!fin.eof()) {
		fin >> text;
	}

	gapBuffer.setText(text);
	fin.close();
}

bool TextDocument::handleKeyCombinations(sf::Event &sfmlEvent) {
	switch (sfmlEvent.text.unicode) {
	case 19:
		saveToFile("file.txt");
		break;
	case 13:
		gapBuffer.insertText('\n');
		break;
	case 8:
		gapBuffer.deleteText();
		break;
	default:
		return true;
		break;
	}
	return false;
}

void TextDocument::handleGuiInput(sf::Event& sfmlEvent) {
	switch (gui.checkInput(sfmlEvent,*pDrawingWindow)) {
	case 2:
		saveToFile("file.txt");
		break;
	default:
		break;
	}
}