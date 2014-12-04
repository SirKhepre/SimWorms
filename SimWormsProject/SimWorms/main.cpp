#include <sstream>
#include <time.h>

#include "OOSDL/OOSDL.h"

#include "Terrain.h"
#include "AssetsManager.h"
#include "GameOptionsManager.h"
#include "Player.h"
#include "EventManager.h"
#include "Gui/GuiTextBox.h"
#include "Gui/GuiMainMenu.h"
#include "Grenade.h"

int main(int argc, char** argv){
	srand(time(0));
	SDL_StartTextInput();
	sdl::Window renderWindow(sdl::VideoMode(1280, 1024), "SimWorms", false);
	GameOptionsManager::getInstance().update(renderWindow);
	Terrain terrain;
	terrain.loadTerrainFromFile("data/maps/country/map.png");
	sdl::StaticSprite bg;
	bg.setTexture(&AssetsManager::getInstance().getTexture("data/maps/country/background.jpg"));
	bg.setScale(terrain.getSize().x / bg.getBounds().w, terrain.getSize().y / bg.getBounds().h);
	sdl::View view;
	view = renderWindow.getDefaultView();
	//GuiMainMenu Game;
	//GuiTextBox Text;
	//Player player(sdl::Vector2Float(800,200));
	//view.setCenter(player.getPosition());

	sdl::StaticText fpsText;
	fpsText.setFont("data/fonts/Arial.ttf");
	fpsText.setPosition(10, 10);
	fpsText.setCharacterSize(16);
	fpsText.setColor(sdl::Color::Black);
	fpsText.setString("");

	sdl::Clock fpsClock;
	sdl::Clock fpsDisplayUpdateClock;

	EntityManager::getInstance().addEntity(new Player(sdl::Vector2Float(500, 500)));

	sdl::Clock runclock;
	while (renderWindow.isOpen()){
		float frametime = fpsClock.restart().asSeconds();
		int fps = (int)(1 / frametime);
		SDL_Event event;
		
		while (renderWindow.pollEvent(event)){
			EventManager::getInstance().launchEvent(event);
			if (event.type == SDL_WINDOWEVENT)
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				renderWindow.close();
			if (event.type == SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_ESCAPE)
				renderWindow.close();
			//if (event.key.keysym.sym == SDLK_q){

			//}
			//if (event.key.keysym.sym == SDLK_e){
			//	GameOptionsManager::getInstance().setVideoMode(sdl::VideoMode::getModes()[0]);
			//}/*
			//if (event.key.keysym.sym == SDLK_f){
			//	GameOptionsManager::getInstance().setFullScreen(true);
			//}
			//if (event.key.keysym.sym == SDLK_g){
			//	GameOptionsManager::getInstance().setFullScreen(false);
			//}
			//if (event.key.keysym.sym == SDLK_u){
			//	GameOptionsManager::getInstance().update(renderWindow);
			//}
			if (event.type == SDL_MOUSEWHEEL)
			{
				if (event.wheel.y < 0)
					view.zoom(1.10);
				if (event.wheel.y > 0)
					view.zoom(0.90);
			}

		}
		if (sdl::Mouse::isButtonPressed(SDL_BUTTON_LEFT)){
			/*if (sdl::Mouse::getPosition().x > 0 && sdl::Mouse::getPosition().x < terrain.getSize().x && sdl::Mouse::getPosition().y > 0 && sdl::Mouse::getPosition().y < terrain.getSize().y){
				ExplosionsManager::getInstance().addExplosion(sdl::Mouse::getPosition(view), terrain, rand() % 50 + 50);
				std::cout << sdl::Mouse::getPosition(view).x << ", " << sdl::Mouse::getPosition(view).y << std::endl;
				std::cout << sdl::Mouse::getPosition().x << ", " << sdl::Mouse::getPosition().y << std::endl;

			}*/
			EntityManager::getInstance().addEntity(new Grenade(sdl::Mouse::getPosition(view), sdl::Vector2Float(), 0, 4));
		}
		if (sdl::Mouse::isButtonPressed(SDL_BUTTON_RIGHT)){
			(*EntityManager::getInstance().getEntities().begin())->setPosition(sdl::Mouse::getPosition(view));
		}
		if (sdl::Keyboard::isKeyPressed(SDLK_w))
			view.move(0, -500 * frametime);
		if (sdl::Keyboard::isKeyPressed(SDLK_a))
			view.move(-500 * frametime, 0);
		if (sdl::Keyboard::isKeyPressed(SDLK_s))
			view.move(0, 500 * frametime);
		if (sdl::Keyboard::isKeyPressed(SDLK_d))
			view.move(500 * frametime, 0);
		if (sdl::Keyboard::isKeyPressed(SDLK_z))
			view.zoom(1.01);
		if (sdl::Keyboard::isKeyPressed(SDLK_x))
			view.zoom(0.99);
		renderWindow.clear(sdl::Color::White);
		renderWindow.setView(view);
		renderWindow.draw(&bg);
		terrain.draw(renderWindow);
		EntityManager::getInstance().update(frametime, terrain, renderWindow);

		if (fpsDisplayUpdateClock.getElapsedTime().asSeconds() > 0.2) {
			std::stringstream ss;
			ss << "SimWorms v0.0.1" << " @ " << fps << " fps";
			fpsText.setString(ss.str());
			fpsDisplayUpdateClock.restart();
		}
	//	Game.update(renderWindow);
		//Game.draw(renderWindow);
		/*Text.update(renderWindow);
		Text.draw(renderWindow);*/
		/*player.update(frametime, terrain);
		player.draw(renderWindow);*/

		renderWindow.draw(&fpsText);

		renderWindow.show();
	}
	SDL_StopTextInput();
	return 0;
}