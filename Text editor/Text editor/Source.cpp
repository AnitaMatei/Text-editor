#include <SFML/Graphics.hpp>
#include "TextEditor.h"

int main()
{

	std::vector<char> caine;
	std::cout << caine.capacity();
	TextEditor myTextEditor(1280, 720);
	myTextEditor.start();

	return 0;
}