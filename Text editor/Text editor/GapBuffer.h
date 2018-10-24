#ifndef GAPBUFFER_H_
#define GAPBUFFER_H_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


class GapBuffer {
	//gap buffer data structure implemented specifically to store text

	std::vector<char> buffer;
	//the vector where the text itself will be held
	int preLength, postLength;
	//the length of the text before the gap and after it
	int gapMaxLength;

	void createGap();

public:
	GapBuffer();

	void insertText(char);
	void deleteText();
	void moveGap(int);
	//it moves the gap backward or forward; -x to move x spaces backward, x to move x spaces forward 
	void moveGapUp();
	void moveGapDown();
	std::string getText();
	//returns a string of the character in the buffer
	sf::Vector2i getGapPosition();
	//returns the start of the gapBuffer, where the cursor would be
	void setText(std::string);
	int getCurrLine();
	//returns the line the gap currently is on, starting from 0
	int getFirstCharOnLine(int);
	//returns the index of the first char on a particular line

	GapBuffer operator=(GapBuffer&);

	int getPreLength() { return preLength; }


};




#endif //GAPBUFFER_H_
