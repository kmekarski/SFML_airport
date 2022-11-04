#include "AnimationState.h"


void AnimationState::initVariables()
{

}

void AnimationState::initBackground()
{
	this->background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));

	if (!this->backgroundTexture.loadFromFile("Resources/images/Backgrounds/game_animation.png"))
	{
		throw "ERROR::AnimationState::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void AnimationState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/CW_BITMP.ttf"))
	{
		throw("ERROR::AnimationState::COULD NOT LOAD FONT");
	}

}

void AnimationState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE DOWN"] = this->supportedKeys->at("S");
	this->keybinds["MOVE RIGHT"] = this->supportedKeys->at("D");
}

void AnimationState::initButtons()
{

}

AnimationState::AnimationState(RenderWindow* window, map<string, int>* supportedKeys,
	stack<State*>* states, Vector2u imageCount, float switchTime, string name, bool load)
	: State(window, supportedKeys, states)
{
	
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	this->name = name;
	this->load = load;

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = this->backgroundTexture.getSize().x / float(imageCount.x);
	uvRect.height = this->backgroundTexture.getSize().y / float(imageCount.y);


	background.setTextureRect(this->uvRect);



}
AnimationState::AnimationState(RenderWindow* window, map<string, int>* supportedKeys,
	stack<State*>* states, Vector2u imageCount, float switchTime, bool load)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	this->name = "!";
	this->load = load;

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = this->backgroundTexture.getSize().x / float(imageCount.x);
	uvRect.height = this->backgroundTexture.getSize().y / float(imageCount.y);


	background.setTextureRect(this->uvRect);
}

AnimationState::~AnimationState()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}


}


void AnimationState::endState()
{

}

void AnimationState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void AnimationState::updateButtons()
{

}

void AnimationState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();

	totalTime += dt;

	if (totalTime >= switchTime)
	{

		totalTime -= switchTime;
		currentImage.x++;
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.top = currentImage.y * uvRect.height;
		background.setTextureRect(this->uvRect);
		if (currentImage.x >= imageCount.x)
		{
			this->quit = true;
			this->states->push(new GameState(this->window, this->supportedKeys, this->states, name, load));
		}
	}

}

void AnimationState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void AnimationState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);


	/*Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);
	stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/

}
