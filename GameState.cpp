#include "GameState.h"

void GameState::initVariables(bool load)
{



	sc.runway = 1;
	sc.maxRunway = 1;
	sc.limitRunway = 4;
	sc.landing = 1;
	sc.maxLanding = 1;
	sc.limitLanding = 4;
	sc.hangar = 0;
	sc.maxHangar = 5;
	sc.limitHangar = 15;

	for (int i = 1; i <= 4; i++)
	{

		//planeShadow[i].shape.setSize(Vector2f(200, 106));
		planeShadowTexture[i].loadFromFile("Resources/images/plane" + to_string(i) + ".png");
		planeShadow[i].shape.setTexture(planeShadowTexture[i]);

		planeShadow[i].shape.setPosition(-200, 720);
		planeShadow[i].movementSpeed = Vector2f(0, 0);

		//heliShadow[i].shape.setSize(Vector2f(151, 91));
		heliShadowTexture[i].loadFromFile("Resources/images/heli" + to_string(i) + ".png");
		heliShadow[i].shape.setTexture(heliShadowTexture[i]);

		heliShadow[i].shape.setPosition(1280, 720);
		heliShadow[i].movementSpeed = Vector2f(0, 0);

		planeStarting[i] = false;
		heliStarting[i] = false;

		planeStarted[i] = false;
		heliStarted[i] = false;

		planeLanded[i] = false;
		heliLanded[i] = false;

		planeLanding[i] = false;
		heliLanding[i] = false;

		planeCheck[i] = false;
		heliCheck[i] = false;

		planeOnRunway[i] = false;

		planeCurLandingTime[i] = 0;
		planeCurStartingTime[i] = 0;

		heliCurLandingTime[i] = 0;
		heliCurStartingTime[i] = 0;
	}


	runwayCoords[1] = Vector2f(60, 540);
	runwayCoords[2] = Vector2f(50, 330);
	runwayCoords[3] = Vector2f(100, 440);
	runwayCoords[4] = Vector2f(110, 210);

	landingCoords[1] = Vector2f(1070, 540);
	landingCoords[2] = Vector2f(800, 540);
	landingCoords[3] = Vector2f(1030, 320);
	landingCoords[4] = Vector2f(760, 320);

	planeLandingTime = 1;
	heliLandingTime = 1;

	planeStartingTime = 1;
	heliStartingTime = 1;

	planeCheckTime = 1;
	heliCheckTime = 1;

	helisInHangar = 0;
	planesInHangar = 0;

	day = 1;
	bank = 1500;

	noMoneyTime = 0;
	noMoney = false;

	tooMuchTime = 0;
	tooMuch = false;
	filesystem::path p = "gamedata.txt";
	ifstream ifs(p);
	if (ifs && load)
	{
		ifs >> name;

		ifs >> bank;
		ifs >> day;

		ifs >> sc.runway;
		ifs >> sc.maxRunway;

		ifs >> sc.landing;
		ifs >> sc.maxLanding;

		ifs >> sc.hangar;
		ifs >> sc.maxHangar;

		ifs >> planesInHangar;
		ifs >> helisInHangar;
	}
	ifs.close();
}

void GameState::initBackground()
{
	this->background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));

	if (!this->backgroundTexture.loadFromFile("Resources/images/Backgrounds/"+to_string(sc.landing)+"-"+to_string(sc.runway)+".png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}



void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/CW_BITMP.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE DOWN"] = this->supportedKeys->at("S");
	this->keybinds["MOVE RIGHT"] = this->supportedKeys->at("D");
}

void GameState::initButtons()
{
	this->buttons["RUNWAY"] = new Button(80, 180, 200, 80, &this->font, "New runway",
		Color(130, 130, 130, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
		Color(0,0,0,200), Color(200,200,200,200));
	this->buttons["HANGAR"] = new Button(490, 180, 300, 80, &this->font, "Enlarge the Hangar",
		Color(130, 130, 130, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
		Color(0, 0, 0, 200), Color(200, 200, 200, 200));
	this->buttons["HANGAR_STATS"] = new Button(505, 228, 200, 80, &this->font, "",
		Color(130, 130, 130, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(0, 0, 0, 200), Color(0, 0, 0, 200));
	this->buttons["NO_MONEY"] = new Button(505, 328, 200, 80, &this->font, "NOT ENOUGH MONEY",
		Color(130, 130, 130, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(180,0,0,255), Color(180,0,0,255));
	this->buttons["EXIT_STATE"] = new Button(550, 590, 200, 80, &this->font, "Quit",
		Color(130, 130, 130, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
		Color(0, 0, 0, 200), Color(200, 200, 200, 200));
	this->buttons["LANDING"] = new Button(1020, 180, 200, 80, &this->font, "New landing",
		Color(130, 130, 130, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
		Color(0, 0, 0, 200), Color(200, 200, 200, 200));
	this->buttons["NAME"] = new Button(100, 78, 200, 80, &this->font, name,
		Color(130, 130, 130, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(0, 0, 0, 200), Color(0, 0, 0, 200));
	this->buttons["BANK"] = new Button(720, 78, 200, 80, &this->font, "$1500",
		Color(130, 130, 130, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(0, 0, 0, 200), Color(0, 0, 0, 200));
	this->buttons["DAY"] = new Button(1040, 78, 200, 80, &this->font, ("Day: 1"),
		Color(130, 130, 130, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(0, 0, 0, 200), Color(0, 0, 0, 200));
	this->buttons["TOO_MUCH"] = new Button(505, 428, 200, 80, &this->font, "YOU HAVE REACHED THE LIMIT",
		Color(130, 130, 130, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(180, 0, 0, 255), Color(180, 0, 0, 255));

	this->buttons["NO_MONEY"]->idleTextColor2 = Color(180, 0, 0, 255);
	this->buttons["NO_MONEY"]->hoverTextColor2 = Color(180, 0, 0, 255);
	this->buttons["NO_MONEY"]->vanish();

	this->buttons["TOO_MUCH"]->idleTextColor2 = Color(180, 0, 0, 255);
	this->buttons["TOO_MUCH"]->hoverTextColor2 = Color(180, 0, 0, 255);
	this->buttons["TOO_MUCH"]->vanish();
}

void GameState::initEvents()
{
	srand((unsigned)time(0));
	this->timeToNextEvent = 3 + (rand() % 3);
	totalTime = 0;
}
GameState::GameState(RenderWindow* window, map<string, int>* supportedKeys,
	stack<State*>* states, string name, bool load)
	: State(window, supportedKeys, states)
{
	this->name = name;

	this->initVariables(load);
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initEvents();




	
}

GameState::~GameState()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}
}


void GameState::endState()
{

}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void GameState::updateButtons()
{


	if (this->buttons["RUNWAY"]->isPressed())
	{
		if (sc.maxRunway == sc.limitRunway)
		{
			tooMuch = true;
			this->buttons["TOO_MUCH"]->show();
		}
		if (bank < 1000)
		{
			noMoney = true;
			this->buttons["NO_MONEY"]->show();
		}
		if (bank >= 1000 && sc.maxRunway < sc.limitRunway)
		{
			bank -= 1000;
			sc.runway++;
			sc.maxRunway++;
			this->backgroundTexture.loadFromFile("Resources/images/Backgrounds/" + to_string(sc.maxLanding) + "-" + to_string(sc.maxRunway) + ".png");
		}

	}
	if (this->buttons["LANDING"]->isPressed())
	{
		if (sc.maxLanding == sc.limitLanding)
		{
			tooMuch = true;
			this->buttons["TOO_MUCH"]->show();
		}
		if (bank < 1000)
		{
			noMoney = true;
			this->buttons["NO_MONEY"]->show();
		}
		if (bank >= 1000 && sc.maxLanding < sc.limitLanding)
		{
			bank -= 1000;
			sc.landing++;
			sc.maxLanding++;
			this->backgroundTexture.loadFromFile("Resources/images/Backgrounds/" + to_string(sc.maxLanding) + "-" + to_string(sc.maxRunway) + ".png");
		}

	}
	if (this->buttons["HANGAR"]->isPressed())
	{
		if (sc.maxHangar == sc.limitHangar)
		{
			tooMuch = true;
			this->buttons["TOO_MUCH"]->show();
		}

		if (bank < 500)
		{
			noMoney = true;
			this->buttons["NO_MONEY"]->show();
		}
		if (bank >= 500 && sc.maxHangar < sc.limitHangar)
		{
			bank -= 500;
			sc.maxHangar++;
		}

	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		filesystem::path p = "gamedata.txt";
		ofstream ofs(p);
		if (ofs)
		{
			ofs << name << "\n";

			ofs << bank << "\n";
			ofs << day << "\n";

			ofs << sc.runway << "\n";
			ofs << sc.maxRunway << "\n";

			ofs << sc.landing << "\n";
			ofs << sc.maxLanding << "\n";

			ofs << sc.hangar << "\n";
			ofs << sc.maxHangar << "\n";

			ofs << planesInHangar << "\n";
			ofs << helisInHangar << "\n";

		}
		ofs.close();
		this->quit = true;


	}
}

void GameState::updateShadows(const float& dt)
{

	for (int i = 1; i <= 4; i++)
	{
		if (planeStarting[i]) //PLANE FLEW AWAY AFTER STARTING
		{
			if (planeShadow[i].shape.getPosition().x > 1280 || planeShadow[i].shape.getPosition().y > 720)
			{
				planeStarting[i] = false;
				planeMoving[i] = false;
				planeLanding[i] = false;
				planeLanded[i] = false;

				planeShadow[i].shape.setPosition(-200, 720);
				planeShadow[i].movementSpeed = Vector2f(0, 0);
			}
		}
		if (heliStarting[i]) //HELI FLEW AWAY AFTER STARTING
		{
			if (heliShadow[i].shape.getPosition().x > 1400 || heliShadow[i].shape.getPosition().y < -160)
			{
				heliStarting[i] = false;
				heliMoving[i] = false;
				heliLanding[i] = false;
				heliLanded[i] = false;


				heliShadow[i].shape.setPosition(1280, 720);
				heliShadow[i].movementSpeed = Vector2f(0, 0);
			}
		}

		if (planeMoving[i])
		{
			//PLANE NOT CATCHED
			if (planeShadow[i].shape.getPosition().x > 1280 || planeShadow[i].shape.getPosition().y > 720)
			{
				planeStarting[i] = false;
				planeMoving[i] = false;
				planeLanded[i] = false;
				planeLanding[i] = false;

				planeShadow[i].shape.setPosition(-200, 720);
				planeShadow[i].movementSpeed = Vector2f(0, 0);
			}

			//PLANE MOVEMENT
			planeShadow[i].shape.setPosition(planeShadow[i].shape.getPosition().x + planeShadow[i].movementSpeed.x * dt,
				planeShadow[i].shape.getPosition().y + planeShadow[i].movementSpeed.y * dt);
			planeShadow[i].update(dt, mousePosView);

			if (planeOnRunway[i])
			{
				planeShadow[i].movementSpeed.x += 0.5;
			}


			//PLANE LANDS
			if (planeShadow[i].shape.getPosition().x >= runwayCoords[i].x - 3 && planeShadow[i].shape.getPosition().x <= runwayCoords[i].x + 3 &&
				planeShadow[i].shape.getPosition().y <= runwayCoords[i].y + 3 && planeShadow[i].shape.getPosition().y >= runwayCoords[i].y - 3 &&
				!planeStarting[i])
			{

				planeLanded[i] = true;
				planeMoving[i] = false;
				planeShadow[i].movementSpeed = Vector2f(0, 0);
			}
			//PLANE TAKES OFF
			if (planeShadow[i].shape.getPosition().x >= runwayCoords[i].x+250 - 10 && planeShadow[i].shape.getPosition().x <= runwayCoords[i].x + 260 &&
				planeShadow[i].shape.getPosition().y <= runwayCoords[i].y + 10 && planeShadow[i].shape.getPosition().y >= runwayCoords[i].y - 10 &&
				planeStarting[i])
			{
				planeStarting[i] = true;
				planeLanding[i] = false;
				planeLanded[i] = false;
				planeMoving[i] = true;
				planeCheck[i] = false;
				planeOnRunway[i] = false;
				planeShadow[i].movementSpeed = Vector2f(150, -150);
			}
		}
		if (heliMoving[i])
		{
			//HELI NOT CATCHED
			if (heliShadow[i].shape.getPosition().x < 0 || heliShadow[i].shape.getPosition().y > 720)
			{
				heliStarting[i] = false;
				heliMoving[i] = false;
				heliLanded[i] = false;
				heliLanding[i] = false;

				heliShadow[i].shape.setPosition(1280, 720);
				heliShadow[i].movementSpeed = Vector2f(0, 0);
			}

			//HELI MOVEMENT
			heliShadow[i].shape.setPosition(heliShadow[i].shape.getPosition().x + heliShadow[i].movementSpeed.x * dt,
				heliShadow[i].shape.getPosition().y + heliShadow[i].movementSpeed.y * dt);
			heliShadow[i].update(dt, mousePosView);


			if (heliOnRunway[i])
			{
				heliShadow[i].movementSpeed.y -= 1;
			}
			if(heliShadow[i].movementSpeed.y == -100.f)
			heliOnRunway[i] = false;

			//HELI LANDS
			if (heliShadow[i].shape.getPosition().x >= landingCoords[i].x - 3 && heliShadow[i].shape.getPosition().x <= landingCoords[i].x + 3 &&
				heliShadow[i].shape.getPosition().y <= landingCoords[i].y + 3 && heliShadow[i].shape.getPosition().y >= landingCoords[i].y - 3 &&
				!heliStarting[i])
			{

				heliLanded[i] = true;
				heliMoving[i] = false;
				heliShadow[i].movementSpeed = Vector2f(0, 0);
			}
		}

		//PLAYER CATCHES PLANE
		if (planeShadow[i].isPressed() && !planeStarting[i] && !planeCheck[i] && !planeLanded[i])
		{
			planeLand(i);
		}
		//PLAYER CATCHES HELI
		if (heliShadow[i].isPressed() && !heliStarting[i] && !heliCheck[i] && !heliLanded[i])
		{
			heliLand(i);
		}
	}
}


void GameState::update(const float& dt)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
		if (it.first == "BANK")
			it.second->setText("$" + to_string(bank));
		if (it.first == "DAY")
			it.second->setText("Day: " + to_string(day));
	}
	this->buttons["HANGAR_STATS"]->setText(to_string(this->sc.hangar) + "/" + to_string(this->sc.maxHangar));



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
		this->updateShadows(dt);

		totalTime += dt;

		if (totalTime >= timeToNextEvent)
		{
			manageEvent();
		}


		for (int i = 1; i <= 4; i++)
		{
			if (planeLanded[i]) //PLANE GOES TO HANGAR AFTER LANDING
			{
				planeCurLandingTime[i] += dt;
				if (planeCurLandingTime[i] >= planeLandingTime) //PLANE LANDED, GOES TO HANGAR
				{
					planeCurLandingTime[i] = 0;

					planeShadow[i].shape.setPosition(-200, 720);
					planeShadow[i].movementSpeed = Vector2f(0, 0);

					planeStarting[i] = false;
					planeMoving[i] = false;
					planeLanded[i] = false;
					planeLanding[i] = false;

					planesInHangar++;
					sc.hangar++;

					bank += 250;
				}
			}
			if (planeCheck[i]) //PLANE CHECK-OUT
			{
				planeCurCheckTime[i] += dt;
				if (planeCurCheckTime[i] >= planeCheckTime)
				{
					planeCurCheckTime[i] = 0;

					planeOnRunway[i] = true;

					planeStarting[i] = true;
					planeMoving[i] = true;
					planeLanded[i] = false;
					planeLanding[i] = false;
					planeCheck[i] = false;

					bank += 250;
				}
			}


			if (heliLanded[i]) //HELI GOES TO HANGAR AFTER LANDING
			{
				heliCurLandingTime[i] += dt;
				if (heliCurLandingTime[i] >= heliLandingTime) //HELI GOES TO HANGAR
				{
					heliCurLandingTime[i] = 0;

					heliShadow[i].shape.setPosition(1280, 720);
					heliShadow[i].movementSpeed = Vector2f(0, 0);

					heliStarting[i] = false;
					heliMoving[i] = false;
					heliLanded[i] = false;
					heliLanding[i] = false;

					helisInHangar++;
					sc.hangar++;

					bank += 250;
				}
			}
			if (heliCheck[i]) //HELI CHECK-OUT
			{
				heliCurCheckTime[i] += dt;
				if (heliCurCheckTime[i] >= heliCheckTime)
				{
					heliCurCheckTime[i] = 0;

					heliOnRunway[i] = true;

					heliStarting[i] = true;
					heliMoving[i] = true;
					heliLanded[i] = false;
					heliLanding[i] = false;
					heliCheck[i] = false;

					bank += 250;
				}
			}
		}




		updateShadows(dt);

		if (noMoney)
		{
			noMoneyTime += dt;
			if (noMoneyTime >= 1.5)
			{
				noMoneyTime = 0;
				noMoney = false;
				this->buttons["NO_MONEY"]->vanish();
			}
		}
		if (tooMuch)
		{
			tooMuchTime += dt;
			if (tooMuchTime >= 1.5)
			{
				tooMuchTime = 0;
				tooMuch = false;
				this->buttons["TOO_MUCH"]->vanish();
			}
		}
}

void GameState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	

	target->draw(this->background);

	this->renderButtons(target);
	for (int i = 1; i <= 4; i++)
	{
	planeShadow[i].render(target);
	heliShadow[i].render(target);
	}

}

bool GameState::runwayToStart(int n)
{
	if(n> sc.runway)
	return false;
	if (planeLanded[n])
		return false;
	if (planeLanding[n])
		return false;
	if (planeStarting[n])
		return false;
	return true;
}

bool GameState::runwayToLand(int n)
{
	if (sc.hangar == sc.maxHangar)
		return false;
	if (n > sc.runway)
		return false;
	if (planeLanded[n])
		return false;
	if (planeLanding[n])
		return false;
	if (planeStarting[n])
		return false;
	return true;
}\

bool GameState::landingToLand(int n)
{
	if (sc.hangar == sc.maxHangar)
		return false;
	if (n > sc.landing)
		return false;
	if (heliLanded[n])
		return false;
	if (heliLanding[n])
		return false;
	if (heliStarting[n])
		return false;
	return true;
}

bool GameState::landingToStart(int n)
{
	if (n > sc.landing)
		return false;
	if (heliLanded[n])
		return false;
	if (heliLanding[n])
		return false;
	if (heliStarting[n])
		return false;
	return true;
}

void GameState::heliLand(int n)
{
	heliLanding[n] = true;

	float ux = landingCoords[n].x - heliShadow[n].shape.getPosition().x;
	float uy = landingCoords[n].y - heliShadow[n].shape.getPosition().y;
	if (uy > 0)
		heliShadow[n].movementSpeed.y = sqrt(20000.0 / (((ux * ux) / (uy * uy)) + 1));
	else
		heliShadow[n].movementSpeed.y = -sqrt(20000.0 / (((ux * ux) / (uy * uy)) + 1));
	heliShadow[n].movementSpeed.x = heliShadow[n].movementSpeed.y * (ux / uy);
}

void GameState::planeLand(int n)
{
	planeLanding[n] = true;

	float ux = runwayCoords[n].x - planeShadow[n].shape.getPosition().x;
	float uy = runwayCoords[n].y - planeShadow[n].shape.getPosition().y;
	if (uy > 0)
		planeShadow[n].movementSpeed.y = sqrt(20000.0 / (((ux * ux) / (uy * uy)) + 1));
	else
		planeShadow[n].movementSpeed.y = -sqrt(20000.0 / (((ux * ux) / (uy * uy)) + 1));
	planeShadow[n].movementSpeed.x = planeShadow[n].movementSpeed.y * (ux / uy);



}
void GameState::manageEvent()
{
	helisToLand.clear();
	helisToStart.clear();
	planesToLand.clear();
	planesToStart.clear();

	for (int i = 1; i <= 4; i++)
	{
		if (runwayToLand(i))
			planesToLand.push_back(i);
		if (runwayToStart(i) && planesInHangar > 0)
			planesToStart.push_back(i);
		if (landingToLand(i))
			helisToLand.push_back(i);
		if (landingToStart(i) && helisInHangar > 0)
			helisToStart.push_back(i);
	}
	int action = 1 + rand() % 4;

	if (action == 1 && planesInHangar==0)
	{
		manageEvent();
		return;
	}
	if (action == 3 && helisInHangar == 0)
	{
		manageEvent();
		return;
	}


	int choice;


	switch (action)
	{
	case 1:
	{
		if (ranges::distance(planesToStart) > 0)
		{
			choice = 1 + rand() % (ranges::distance(planesToStart));
			planeShadow[choice].movementSpeed.x = 0;
			planeShadow[choice].movementSpeed.y = 0;
			planeShadow[choice].shape.setPosition(runwayCoords[choice]);
			planeCheck[choice] = true;
			planesInHangar--;
			sc.hangar--;
		}
	}//plane starts
		break;
	case 2:
	{
		if (ranges::distance(planesToLand) > 0 && sc.hangar < sc.maxHangar)
		{
			choice = 1 + rand()%(ranges::distance(planesToLand));

			planeShadow[choice].movementSpeed.x = 100.f;
			planeShadow[choice].movementSpeed.y = -100.f;
			planeMoving[choice] = true;
		}
	}//plane lands
		break;
	case 3:
	{
		if (ranges::distance(helisToStart) > 0)
		{
			choice = 1 + rand()%(ranges::distance(helisToStart));
			heliShadow[choice].movementSpeed.x = 0;
			heliShadow[choice].movementSpeed.y = 0;
			heliShadow[choice].shape.setPosition(Vector2f(landingCoords[choice]));
			heliCheck[choice] = true;
			helisInHangar--;
			sc.hangar--;
		}
	}//heli starts
		break;
	case 4:
	{
		if (ranges::distance(helisToLand) > 0 && sc.hangar < sc.maxHangar)
		{
			choice = 1 + rand() % (ranges::distance(helisToLand));
			heliShadow[choice].movementSpeed.x = -100;
			heliShadow[choice].movementSpeed.y = -100;
			heliMoving[choice] = true;
		}
	}//heli lands
		break;

	}
	
	totalTime = 0;
	timeToNextEvent = 4 - 0.20 * sc.runway - 0.20 * sc.landing;
	day++;
}
