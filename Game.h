#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	RenderWindow *window;
	Event sfEvent;

	Clock dtClock;
	float dt;

	stack <State*> states;

	map <string, int> supportedKeys;

	//Initializers
	void initWindow();
	void initStates();
	void initKeys();


public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update

	//Render

	//Core
	void updateDt();
	void updateSMFLEvents();
	void update();
	void render();
	void run();
};

#endif