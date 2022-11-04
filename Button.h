#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
private:
	short unsigned buttonState;
	RectangleShape shape;
	Font* font;
	Text text;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

	Color idleTextColor;
	Color hoverTextColor;







public:
	Color idleTextColor2;
	Color hoverTextColor2;
	Button(float x, float y, float width, float height, 
		Font* font, string text,
		Color idleColor, Color hoverColor, Color activeColor,
		Color idleTextColor, Color hoverTextColor);
	~Button();
	//Accessors
	const bool isPressed() const;
	//Functions
	void update(Vector2f mousePos);
	void render(RenderTarget* target);
	void setText(string s);
	void vanish();
	void show();

	RectangleShape getShape();

};

#endif