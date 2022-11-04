#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Game.h"
#include "MainMenuState.h"
#include "Button.h"

import myFile;


class GameState :
    public State
{
private:
    string name;

    Vector2f runwayCoords[5];
    Vector2f landingCoords[5];

    Entity planeShadow[5];
    Texture planeShadowTexture[5];
    Entity heliShadow[5];
    Texture heliShadowTexture[5];
    Event sfEvent;

    int helisInHangar;
    int planesInHangar;


    AirportStats sc;

    //int runway, maxRunway, limitRunway;
    //int landing, maxLanding, limitLanding;
    //int hangar, maxHangar, limitHangar;

    int bank, day;


    float timeToNextEvent;
    float totalTime;

    float noMoneyTime;
    bool noMoney;
    float tooMuchTime;
    bool tooMuch;

    Texture backgroundTexture;
    RectangleShape background;
    Font font;

    bool heliStarting[5], planeStarting[5];
    bool heliStarted[5], planeStarted[5];
    bool heliLanding[5], planeLanding[5];
    bool heliLanded[5], planeLanded[5];
    bool heliMoving[5], planeMoving[5];
    bool heliCheck[5], planeCheck[5];




    float planeStartingTime;
    float planeCurStartingTime[5];
    float heliStartingTime;
    float heliCurStartingTime[5];
    float planeLandingTime, heliLandingTime;
    float planeCurLandingTime[5], heliCurLandingTime[5];
    float planeCheckTime, heliCheckTime;
    float planeCurCheckTime[5], heliCurCheckTime[5];
    float planeOnRunway[5], heliOnRunway[5];

    vector <int> helisToLand;
    vector <int> planesToLand;
    vector <int> helisToStart;
    vector <int> planesToStart;


    map<string, Button*> buttons;
    //Functions
    void initVariables(bool load);
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initEvents();


public:
    GameState(RenderWindow* window, map<string, int>* supportedKeys,
        stack<State*>* states, string name, bool load);
    virtual ~GameState();

    //Functions

    void endState();

    void updateInput(const float& dt);
    void updateButtons();
    void updateShadows(const float& dt);
    void update(const float& dt);
    void renderButtons(RenderTarget* target = nullptr);
    void render(RenderTarget* target = nullptr);

    bool landingToStart(int n);
    bool landingToLand(int n);
    bool runwayToStart(int n);
    bool runwayToLand(int n);

    void heliStart(int n);
    void planeStart(int n);
    void heliLand(int n);
    void planeLand(int n);

    void manageEvent();
};

#endif