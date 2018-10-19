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
	buffer[preLength] = text;
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

		for (int i = 0; i < direction; i++) {
			buffer[gapLength + preLength - i-1] = buffer[preLength-i];
			buffer[preLength - i] = ' ';
		}

		postLength += preLength - direction;
		preLength -= direction;
	}
	else {
		//if we move the gap forward, the text is copied to the beginning of the gap and initial position replaced with the buffer
		
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