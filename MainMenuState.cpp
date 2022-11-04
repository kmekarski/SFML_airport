#include "MainMenuState.h"

void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));

	if (!this->backgroundTexture.loadFromFile("Resources/images/Backgrounds/main_menu_background.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/CW_BITMP.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}

}

void MainMenuState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE DOWN"] = this->supportedKeys->at("S");
	this->keybinds["MOVE RIGHT"] = this->supportedKeys->at("D");
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(128, 564, 200, 80, &this->font, "New Game",
		Color(130, 130, 130, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
		Color(0, 0, 0, 200), Color(200, 200, 200, 200));
	this->buttons["LOAD_STATE"] = new Button(540, 564, 200, 80, &this->font, "Load Game",
		Color(130, 130, 130, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
		Color(0, 0, 0, 200), Color(200, 200, 200, 200));
	this->buttons["EXIT_STATE"] = new Button(958, 564, 200, 80, &this->font, "Quit",
		Color(130, 130, 130, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
		Color(0, 0, 0, 200), Color(200, 200, 200, 200));

}

MainMenuState::MainMenuState(RenderWindow* window, map<string, int>* supportedKeys,
	stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}


}


void MainMenuState::endState()
{

}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::updateButtons()
{


	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new NewGameState(this->window, this->supportedKeys, this->states));
	}
	if (this->buttons["LOAD_STATE"]->isPressed())
	{
		this->states->push(new AnimationState(this->window, this->supportedKeys, this->states, Vector2u(36, 1), 0.03f, true));
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void MainMenuState::update(const float& dt)
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

void MainMenuState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(RenderTarget* target)
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
