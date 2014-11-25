#pragma once
#include "OOSDL/OOSDL.h"

class ScreenState{
public:
	virtual void update(float frametime) = 0;
	virtual void draw(sdl::Window &target) = 0;
};