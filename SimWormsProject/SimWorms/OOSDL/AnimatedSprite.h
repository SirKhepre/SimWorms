#pragma once

#include <SDL2/SDL_rect.h>

#include "Texture.h"
#include "Clock.h"
#include "Sprite.h"

namespace sdl {
	class AnimatedSprite : public sdl::Sprite
	{
	public:
		AnimatedSprite(sdl::Texture* texture, int numberOfFrames, int delay);

		void reset();

		void draw(SDL_Renderer* renderer, sdl::View &view);

		void nextFrame();
		void updateFrame();

		bool looping;
		int delay;
		bool active;
	private:
		sdl::RectFloat getRenderDestination(sdl::View& view);


		sdl::Clock clock;

		unsigned int currentFrame;
		unsigned int numberOfFrames;
	};
}