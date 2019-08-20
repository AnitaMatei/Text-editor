#include "TextDocument.h"

TextDocument::TextDocument(sf::RenderWindow& drawingWindow)
	:gapBuffer(),
	cursor(),
	gui(drawingWindow.getSize()),
	sndGapBuffer(),
	keysPressed(5)
{
	font.loadFromFile("Fonts/VeraMono.ttf");
	drawableText.setFont(font);
	drawableText.setFillColor(sf::Color(102, 153, 153));
	drawableText.setCharacterSize(15);
	drawableText.setPosition(sf::Vector2f(0, 25));

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
	handleArrowPresses(sfmlEvent);
	
	for (int i = 0; i < keysPressed.size(); i++) {
		if (keysPressed[i]) {
			switch (i) {
			case 1:
				gapBuffer.moveGapUp();
				break;
			case 2:
				gapBuffer.moveGap(-1);
				break;
			case 3:
				gapBuffer.moveGapDown();
				break;
			case 4:
				gapBuffer.moveGap(1);
				break;
			}
		}
	}

	if (sfmlEvent.type == sf::Event::TextEntered) {
		if (handleSpecialUnicode(sfmlEvent))
			gapBuffer.insertText(sfmlEvent.text.unicode);	
	}
	
}

void TextDocument::saveFile(std::string fileName) {
	std::string text = gapBuffer.getText();
	std::ofstream fout(fileName);
	if (fout.is_open()) {
		for (int i = 0; i < text.size(); i++) {
			fout << text[i];
		}
		fout.close();
		std::cout << "Saved!"<<std::endl;
	}
	else {
		std::cout << "Destination can't be found!" << std::endl;
	}
}

void TextDocument::openFile(std::string fileName) {
	std::string text;
	std::ifstream fin(fileName);
	if (fin.is_open()) {
		int i = 0;
		while (!fin.eof()) {
			//we definitely don't want to jump over white spaces, so we need to use noskipws when reading
			char temp;
			if(fin >> std::noskipws >> temp)
				text += temp;
		}
		gapBuffer.setText(text);
		fin.close();
		std::cout << "Opened file!" << std::endl;
	}
	else {
		std::cout << "Destination can't be found!" << std::endl;
	}
}

bool TextDocument::handleSpecialUnicode(sf::Event &sfmlEvent) {

	switch (sfmlEvent.text.unicode) {
	case 19:	//ctrl+s
		saveFile(readInputFileName());
		break;
	case 13:	//space
		gapBuffer.insertText('\n');
		break;
	case 8:		//backspace
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
	case 1:
		saveFile(readInputFileName());
		break;
	case 2:
		openFile(readOutputFileName());
		break;
	default:
		break;
	}
}
void TextDocument::handleArrowPresses(sf::Event& sfmlEvent) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		keysPressed[0] = 1;
	else keysPressed[0] = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		keysPressed[1] = 1;
	else keysPressed[1] = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		keysPressed[2] = 1;
	else keysPressed[2] = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		keysPressed[3] = 1;
	else keysPressed[3] = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		keysPressed[4] = 1;
	else keysPressed[4] = 0;
}

std::string TextDocument::readOutputFileName()
{
	std::cout << "Enter the location of the file you want to open:";
	std::string fileName;
	std::cin >> fileName;
	return fileName;
}

std::string TextDocument::readInputFileName()
{
	std::cout << "Enter the path where you want to save the text file:";
	std::string fileName;
	std::cin >> fileName;
	return fileName;
}
