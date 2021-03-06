#include "Map.h"


Map::Map(const std::string& name, const std::string& description, int landMinesCount, int maxWindForce, int gravityForce, const std::string& terrainPath, const std::string& bgPath, const std::string& thumbnailPath){
	this->name = name;
	this->description = description;
	this->landMinesCount = landMinesCount;
	this->maxWindForce = maxWindForce;
	this->gravityForce = gravityForce;
	this->terrain.loadTerrainFromFile(terrainPath);
	this->bg.setTexture(&AssetsManager::getInstance().getTexture(bgPath));
	thumbnail.setTexture(&AssetsManager::getInstance().getTexture(thumbnailPath));
	updateWindForce();
	/*std::default_random_engine engine(time(0));
	std::uniform_int_distribution<int> dist(50, terrain.getSize().x - 50);
	for (int i = 0; i < landMinesCount; i++)
		landMinesPositions.push_back(sdl::Vector2Float(dist(engine), dist(engine)));*/
}

void Map::updateWindForce(){
	std::default_random_engine engine(time(0));
	std::uniform_int_distribution<int> distX(-maxWindForce, maxWindForce);
	std::uniform_int_distribution<int> distY(0, maxWindForce);
	windForce.x = distX(engine);
	windForce.y = distY(engine);
}

sdl::RectFloat Map::getBounds(){
	return sdl::RectFloat(0, 0, terrain.getSize().x, terrain.getSize().y);
}

void Map::update(){

}

void Map::draw(sdl::Window &target){
	target.draw(&bg);
	terrain.draw(target);
}