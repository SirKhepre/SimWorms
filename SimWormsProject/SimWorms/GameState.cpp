#include "GameState.h"


GameState::GameState(sdl::Window &target)
{
	actualMap = new Map(MapManager::getInstance().getActualMap());
	cam = new Camera(target, actualMap);
}

void GameState::update(sdl::Window &target, float frametime) {
	GameManager::getInstance().update(target, cam, actualMap, frametime);
}

void GameState::draw(sdl::Window &target) {

}