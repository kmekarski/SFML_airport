#include "Entity.h"

Entity::Entity()
{
	//this->shape.setSize(Vector2f(50.f, 50.f));

	idleColor = Color(0,0,0,255);
	hoverColor = Color(0, 0, 0, 130);
	activeColor = Color(0, 0, 0, 80);
}

Entity::~Entity()
{

}


void Entity::update(const float& dt, Vector2f mousePos)
{
	this->buttonState = E_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = E_HOVER;

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->buttonState = E_ACTIVE;
		}
	}
}

void Entity::render(RenderTarget* target)
{
	target->draw(this->shape);

}

const bool Entity::isPressed() const
{
	if (this->buttonState == E_ACTIVE)
		return true;
	return false;
}
