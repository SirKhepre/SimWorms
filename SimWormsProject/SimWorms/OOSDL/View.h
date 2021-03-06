#pragma once
#include "Vector2.h"
#include "Rect.h"

namespace sdl{
	class View
	{
	public:
		View();
		View(const sdl::RectFloat &rect);
		View(sdl::Vector2Float& center, sdl::Vector2Float& size);
		
		void setCenter(float x, float y);
		void setCenter(sdl::Vector2Float &center);
		
		void setSize(float w, float h);
		void setSize(sdl::Vector2Float &size);

		void setRotation(float angle);

		void setViewport(const sdl::RectFloat &viewport);

		void reset(const sdl::RectFloat &rect);

		sdl::Vector2Float& getCenter();

		sdl::Vector2Float& getSize();

		sdl::Vector2Float getOriginalSize(){ return originalSize; }

		float getRotation();

		sdl::RectFloat& getViewport();

		void move(float x, float y);
		void move(sdl::Vector2Float& vect);

		void rotate(float angle);

		void zoom(float factor);
	private:
		sdl::Vector2Float center;
		sdl::Vector2Float size;
		sdl::Vector2Float originalSize;
		sdl::RectFloat viewport;
		float orientation;
		float zoomFactor;
	};
}