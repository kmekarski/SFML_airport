#pragma once
#include "GameState.h"

class AnimationState :
    public State
{
private:
    bool load;
    Vector2u imageCount;
    Vector2u currentImage;

    float totalTime;
    float switchTime;
    string name;
    //Variables
    Texture backgroundTexture;
    RectangleShape background;
    Font font;

    map<string, Button*> buttons;
    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    AnimationState(RenderWindow* window, map<string, int>* supportedKeys,
        stack<State*>* states, Vector2u imageCount, float switchTime, string name, bool load);
    AnimationState(RenderWindow* window, map<string, int>* supportedKeys,
        stack<State*>* states, Vector2u imageCount, float switchTime, bool load);
    virtual ~AnimationState();

    //Functions

    void endState();

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(RenderTarget* target = nullptr);
    void render(RenderTarget* target = nullptr);

    IntRect uvRect;
};

