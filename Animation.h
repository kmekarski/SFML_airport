#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class Animation
{
public:
	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	~Animation();

	void update(int row, float dt);

public:
	IntRect uvRect;

private:
	Vector2u imageCount;
	Vector2u currentImage;
	float totalTime;
	float switchTime;

};

