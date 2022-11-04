#include "Button.h"

Button::Button(float x, float y, float width, float height,
	Font* font, string text,
	Color idleColor, Color hoverColor, Color activeColor,
	Color idleTextColor, Color hoverTextColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, height));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(36);
	this->text.setPosition(
		this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->idleTextColor = idleTextColor;
	this->hoverTextColor = hoverTextColor;

	this->shape.setFillColor(this->idleColor);

}

Button::~Button()
{

}


//Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_HOVER)
		return true; 
	return false;
}

//Functions



void Button::update(Vector2f mousePos)
{
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE; 
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
	{
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->idleTextColor);
	}
		break;

	case BTN_HOVER:
	{
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->hoverTextColor);
	}
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;

	default:
		this->shape.setFillColor(Color::Red);
		break;
	}
}


void Button::render(RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

void Button::setText(string s)
{
	this->text.setString(s);
}

void Button::vanish()
{
	this->idleTextColor = Color::Transparent;
	this->hoverTextColor = Color::Transparent;
}


void Button::show()
{
	this->idleTextColor = idleTextColor2;
	this->hoverTextColor = hoverTextColor2;
}

RectangleShape Button::getShape()
{
	return this->shape;
}
