#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

enum entity_states { E_IDLE = 0, E_HOVER, E_ACTIVE };

class Entity
{
private:
	short unsigned buttonState;

	Color idleColor;
	Color hoverColor;
	Color activeColor;



protected:


public:
	Entity();
	virtual ~Entity();
	//RectangleShape shape;
	Sprite shape;
	Vector2f movementSpeed;

	const bool isPressed() const;

	//Functions
	virtual void update(const float& dt, Vector2f mousePos);
	virtual void render(RenderTarget* target);
};

#endif