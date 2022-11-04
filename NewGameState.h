#ifndef NEWGAMESTATE_H
#define NEWGAMESTATE_H

#include "State.h"
#include "AnimationState.h"
#include "MainMenuState.h"
#include "Button.h"

#include <regex>

class NewGameState :
    public State
{
private:
    //Variables
    Texture backgroundTexture;
    RectangleShape background;
    Font font; 
    string name;

    map<string, Button*> buttons;
    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    NewGameState(RenderWindow* window, map<string, int>* supportedKeys,
        stack<State*>* states);
    virtual ~NewGameState();

    //Functions

    void endState();

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(RenderTarget* target = nullptr);
    void render(RenderTarget* target = nullptr);
};

#endif