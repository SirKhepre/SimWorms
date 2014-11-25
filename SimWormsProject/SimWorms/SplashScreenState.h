#pragma once
#include "ScreenState.h"
class SplashScreenState : public ScreenState
{
public:
	SplashScreenState();
	void update(float frametime);
	void draw(sdl::Window &target);
private:
	sdl::Sprite splashScreenSprite;
	sdl::Clock splashScreenClock;
};

