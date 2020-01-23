#include "Level.h"
#include <string>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "Error loading font\n";
	}
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);

	circle.setFillColor(sf::Color::Black);
	circle.setRadius(12);
	circle.setPosition(-24, -24);

	input->setMouseRDown(false);

}

Level::~Level()
{
	input = nullptr;
}

int mousedragx1;
int mousedragy1;
int mousedragx2;
int mousedragy2;
int dragTotalx;
int dragTotaly;
bool mouseDrag=true;
bool mouseDragEnd = false;

// handle user input
void Level::handleInput()
{
	bool jPressed = false;
	bool kPressed = false;
	bool lPressed = false;

	if (input->isKeyPressed(sf::Keyboard::W)) {
		std::cout << "W was pressed\n";
	}


	if(input->isKeyDown(sf::Keyboard::J)) {
		jPressed = true;
	}
	if (input->isKeyDown(sf::Keyboard::K)) {
		kPressed = true;
	}
	if (input->isKeyDown(sf::Keyboard::L)) {
		lPressed = true;
	}

	if (!input->isKeyDown(sf::Keyboard::J)) {
		input->setKeyUp(sf::Keyboard::J);
	}
	if (!input->isKeyDown(sf::Keyboard::K)) {
		input->setKeyUp(sf::Keyboard::K);
	}
	if (!input->isKeyDown(sf::Keyboard::L)) {
		input->setKeyUp(sf::Keyboard::L);
	}

	if (jPressed && kPressed && lPressed) {
		std::cout << "JKL is pressed!\n";
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
	}

	

	if (input->isKeyPressed(sf::Keyboard::Escape)) {
		exit(1);
	}


	if(input->isMouseLDown() && mouseDrag) {
		mousedragx1 = input->getMouseX();
		mousedragy1 = input->getMouseY();
		mouseDrag = false;
		mouseDragEnd = true;
	}

	if (!input->isMouseLDown() && mouseDragEnd) {
		mousedragx2 = input->getMouseX();
		mousedragy2 = input->getMouseY();
		if (mousedragx1 > mousedragx2) {
			dragTotalx = mousedragx1 - mousedragx2;
		}
		else if (mousedragx1 <= mousedragx2) {
			dragTotalx = mousedragx2 - mousedragx1;
		}
		
		if (mousedragy1 > mousedragy2) {
			dragTotaly = mousedragy1 - mousedragy2;
		}
		else if (mousedragy1 <= mousedragy2) {
			dragTotaly = mousedragy2 - mousedragy1;
		}

		std::cout << "You dragged " << dragTotalx << " on the x coords, and " << dragTotaly << " on the y coords\n";

		mouseDragEnd = false;
		mouseDrag = true;
	}
	

	
}

int mousex;
int mousey;
// Update game objects
void Level::update()
{
	if (input->isMouseRDown()) {
		circle.setPosition(input->getMouseX()-12, input->getMouseY()-12);
		input->setMouseRDown(false);
	}

	mousex = input->getMouseX();
	mousey = input->getMouseY();
	text.setString("The mouse is at " + std::to_string(mousex) + ", " + std::to_string(mousey));
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(text);

	window->draw(circle);
	
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}