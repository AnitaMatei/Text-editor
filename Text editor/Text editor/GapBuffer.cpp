#include "GapBuffer.h"

GapBuffer::GapBuffer() {
	gapMaxLength = 2048;
	createGap();
	preLength = 0;
	//the cursor is placed at the beginning at first;
	postLength = 0;
}

void GapBuffer :: createGap() {
	for (int i = 0; i < gapMaxLength; i++)
	{
		buffer.insert(buffer.begin() + (i + preLength), ' ');
	}
}

void GapBuffer::insertText(char text) {
	if (text == 13)
		//if the unicode is 13(enter), we have to create a new line with \n
	{
		buffer[preLength] = '\n';
	}
	else if (text == 8) {
	//if the unicode is 8(backspace), we delete the character rather than adding it
		if (preLength > 0)
			deleteText();
		return;
	}
	else buffer[preLength] = text;
	
	preLength++;
}

void GapBuffer::deleteText() {
	buffer[preLength] = ' ';
	preLength--;
}

void GapBuffer::moveGap(int direction) {
	int gapLength = buffer.size() - (preLength + postLength);
	
	if (direction<0) {
		//if we move the gap backwards, we start copying the text from pos until the gap starts at the end of the gap

		direction *= -1;

		if (preLength == 0)
			return;

		if (preLength - direction <= 0)
			direction = preLength;

		for (int i = 1; i <= direction; i++) {
			buffer[gapLength + preLength - i] = buffer[preLength-i];
			buffer[preLength - i] = ' ';
		}

		postLength += direction;
		preLength -= direction;
	}
	else {
		//if we move the gap forward, the text is copied to the beginning of the gap and initial position replaced with the buffer
		if (postLength == 0)
			return;

		for (int i = 0; i < direction; i++) {
			buffer[preLength + i] = buffer[preLength + gapLength + i];
			buffer[preLength + gapLength + i] = ' ';
		}
		
		postLength -= direction;
		preLength += direction;
	}
}

std::string GapBuffer::getText() {
	std::string tempText;
	int gapLength = buffer.size() - (preLength + postLength);

	for (int i = 0; i < preLength; i++)
	{
		tempText += buffer[i];
	}
	for (int i = 0; i < postLength; i++)
	{
		tempText += buffer[i + preLength + gapLength];
	}

	return tempText;
}

sf::Vector2i GapBuffer::getGapPosition() {
	sf::Vector2i pos(0,0);

	for (int i = preLength - 1; i >= 0; i--) {
		//the x represents the column, so the number of character between the last line and the gap buffer
		if (buffer[i] == '\n')
			break;
		pos.x ++;
	}

	for (int i = 0; i < preLength; i++) {
		//the y represents the number of lines, so how many '\n' chars there were
		if (buffer[i] == '\n')
			pos.y++;
	}

	return pos;
}

void GapBuffer::moveGapUp() {
	//we go back until we hit 2 '\n' or the start of the text
	//the gap is moved x amount of characters from the 2nd '\n', where x is how many character there are on the current line

	int endlAppearances = 0, i, charsCurrLine=0, direction=0;
		


	for (i = preLength - 1; i > 0; i--) {
		if (buffer[i] == '\n')
			endlAppearances++;
		else if (i - 1 == 0)
		{
			if (endlAppearances == 1)
			{
				direction -= charsCurrLine;
				std::cout << charsCurrLine << std::endl;
				break;
			}
		}
		if (endlAppearances == 0)
			charsCurrLine++;
		if (endlAppearances == 2)
			break;
	}

	direction += preLength - i + 1;

	moveGap(-direction);

}