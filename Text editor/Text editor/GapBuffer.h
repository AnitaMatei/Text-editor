#ifndef GAPBUFFER_H_
#define GAPBUFFER_H_

#include <vector>


class GapBuffer {
	//gap buffer data structure to store text

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
	std::string getText();
	//returns a string of the character in the buffer


};




#endif //GAPBUFFER_H_
