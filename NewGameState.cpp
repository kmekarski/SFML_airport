#include "NewGameState.h"

void NewGameState::initVariables()
{

}

void NewGameState::initBackground()
{
	this->background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));

	if (!this->backgroundTexture.loadFromFile("Resources/images/Backgrounds/main_menu_background.png"))
	{
		throw "ERROR::NEW_GAME_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}


void NewGameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/CW_BITMP.ttf"))
	{
		throw("ERROR::NEWGAMESTATE::COULD NOT LOAD FONT");
	}

}

void NewGameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE DOWN"] = this->supportedKeys->at("S");
	this->keybinds["MOVE RIGHT"] = this->supportedKeys->at("D");
}

void NewGameState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(128, 564, 200, 80, &this->font, "Start",
		Color(130, 130, 130, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
		Color(0, 0, 0, 200), Color(200, 200, 200, 200));


	this->buttons["EXIT_STATE"] = new Button(958, 564, 200, 80, &this->font, "Quit",
		Color(130, 130, 130, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
		Color(0, 0, 0, 200), Color(200, 200, 200, 200));

}

NewGameState::NewGameState(RenderWindow* window, map<string, int>* supportedKeys,
	stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	this->window->draw(this->background);

	this->renderButtons(this->window);

	bool ok = false;
	regex reg("^[a-zA-Z0-9]{1,}$");
	while (!ok)
	{
		cout << "ENTER AIRPORT NAME: ";
		cin >> name;

		smatch matches;
		regex_search(name, matches, reg);
		if (matches.empty() || matches[0] != name)
		{
			cout << "\nWRONG AIRPORT NAME. IT CANNOT CONTAIN SPECIAL CHARACTERS.\n";
		}
		else
		{
			ok = true;
		}
	}
}


NewGameState::~NewGameState()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}


}

void NewGameState::endState()
{
}

void NewGameState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void NewGameState::updateButtons()
{


	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new AnimationState(this->window, this->supportedKeys, this->states, Vector2u(36, 1), 0.03f, name, false));
		this->quit = true;
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void NewGameState::update(const float& dt)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (Mouse::isButtonPressed(Mouse::Left))
		curPress = true;
	else
		curPress = false;

	if (prevPress && !curPress)
	{

		updateButtons();
	}


	prevPress = curPress;
	this->updateMousePositions();
	this->updateInput(dt);



}

void NewGameState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void NewGameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);
}