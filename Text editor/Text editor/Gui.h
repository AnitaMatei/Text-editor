#ifndef GUI_H_
#define GUI_H_

#include "SFML/Graphics.hpp"

class Gui : public sf::Drawable{

	sf::RectangleShape menuBar;
	std::vector<sf::Text> menuNames;
	sf::Font font;
	std::vector<sf::FloatRect> menuNameBoxes;


public:
	Gui(sf::Vector2u);

	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void update();
	int checkInput(sf::Event&, sf::RenderWindow&);
	//based on what it returns an action will happen
};


#endif //GUI_H_