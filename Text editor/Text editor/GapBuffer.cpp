#include "GapBuffer.h"

GapBuffer::GapBuffer() {
	gapMaxLength = 55;
	preLength = 0;
	//the cursor is placed at the beginning at first;
	createGap();

	nrLines = 0;
	postLength = 0;
	//buffer.push_back('\0');
}

void GapBuffer :: createGap() {
	for (int i = 0; i < gapMaxLength; i++)
	{
		buffer.insert(buffer.begin() + (i + preLength), ' ');
	}
}

void GapBuffer::insertText(char text) {
	if (buffer.size() == preLength)
		createGap();
	if (text == '\n')
		nrLines++;
	buffer[preLength] = text;
	preLength++;

	//std::cout << preLength << " " << postLength << std::endl;
}

void GapBuffer::deleteText() {
	if (preLength != 0) {
		if (buffer[preLength] == '\n')
			nrLines--;
		buffer[preLength] = ' ';
		preLength--;
	}
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

	int endlAppearances = 0, charsCurrLine=0, charsPrevLine=0, direction=0;
	bool keepGoing = true;


	for (int i = preLength - 1; i > 0 && keepGoing; i--) {
		//if we encountered an endline, we check wether the next character is the beginning of the text or another endline
		//if its another endline, we have to deduct the number of characters by 1

		if (buffer[i] == '\n')
			endlAppearances++;
		switch (endlAppearances) {
		case 0:
			//if we havent encountered any endlines, we keep counting how many chars there are on the current line
			charsCurrLine++;
			break;
		case 1:
			//if we've already encountered one endline, we make sure the next character isnt the end and keep counting the 
			//characters on the previous line

			if (i - 1 > 0 && buffer[i-1]!='\n')
				charsPrevLine++;
			else {
				if (buffer[i - 1] == '\n')
					charsPrevLine--;
				keepGoing = false;
			}
			break;
		}
	}

	if (charsCurrLine > charsPrevLine)
		direction = charsCurrLine + 1;
	else direction = charsPrevLine + 2;
	//if there are more chars on the current line than the previous one, we go to the last char on the previous line
	//otherwise, we move the gap charsCurrLine+charsPrevLine-charsCurrLine +2 = charsCurrLine + 2

	moveGap(-direction);
}

void GapBuffer::moveGapDown() {
	//functions similar to the moveGapUp function, only now we need to know how many characters there are both on left and right of the gap

	int charsCurrLineLeft = 0, charsCurrLineRight = 0, charsNextLine = 0, direction = 0, endlAppearances = 0;
	bool keepGoing = true;

	for (int i = preLength; i > 0;i--) {
		if (buffer[i - 1] == 0 || buffer[i - 1] == '\n')
		{
			break;
		}

		charsCurrLineLeft++;
	}
	for (int i = buffer.size() - postLength; i < buffer.size() && keepGoing; i++) {
		if (buffer[i] == '\n')
			endlAppearances++;
		switch (endlAppearances) {
		case 0:
			charsCurrLineRight++;
			break;
		case 1:
			if (i + 1 < buffer.size() && buffer[i + 1] != '\n')
				charsNextLine++;
			else {
				keepGoing = false;
			}
			break;
		}
	}

	if (charsCurrLineLeft >= charsNextLine) {
		direction = charsCurrLineRight + charsNextLine;

		if (charsNextLine != 0)
			direction++;
		//when we're not on the last line, we have to go one character further because of \n
	}
	else {
		direction = charsCurrLineRight + charsCurrLineLeft + 1;
	}

	moveGap(direction);

}

void GapBuffer::setText(std::string text) {

	//emptying the buffer
	std::vector<char> temp;		
	buffer = temp;
	preLength = 0;
	postLength = 0;
	createGap();

	for (int i = 0; i < text.size(); i++)
	{
		insertText(text[i]);
	}
}

int GapBuffer::getCurrLine() {
	int lines = 0;
	for (int i = 0; i < preLength; i++) {
		if (buffer[i] == '\n')
			lines++;
	}
	return lines;
}

int GapBuffer::getFirstCharOnLine(int thisLine) {
	int lines = 0, i = 0;
	while (lines < thisLine) {
		if (buffer[i] == '\n')
			lines++;
		i++;
	}
	return i;
}

GapBuffer GapBuffer::operator=(GapBuffer& gp) {
	preLength = gp.preLength;
	postLength = gp.postLength;
	gapMaxLength = gp.gapMaxLength;
	buffer = gp.buffer;

	return *this;
}