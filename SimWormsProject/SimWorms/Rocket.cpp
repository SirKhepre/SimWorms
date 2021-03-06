#include "Rocket.h"
#include "GameManager.h"
#include "RadToDeg.h"

Rocket::Rocket(sdl::Vector2Float &startingPosition, sdl::Vector2Float &orientation, float force) {
	sprite.setTexture(&AssetsManager::getInstance().getTexture("data/textures/doom_rocket.png"));
	sprite.setPosition(sdl::Vector2Float(startingPosition.x, startingPosition.y));
	velocity = (orientation * force);
	sprite.setOrigin(0, (0 + (sprite.getBounds().h / 2)));
	std::cout << sprite.getPosition().x << sprite.getPosition().y << std::endl;
	dead = false;
	isLaunched = false;
	this->physics = new ProjectilePhysicsComponents;
}

void Rocket::draw(sdl::Window &target) {
	if (physics->getResultingVector().x > 0)
		sprite.setRotation(180 + radToDeg(atan(physics->getResultingVector().y / physics->getResultingVector().x)));
	if (physics->getResultingVector().x < 0)
		sprite.setRotation(radToDeg(atan(physics->getResultingVector().y / physics->getResultingVector().x)));
	target.draw(&sprite);
}

void Rocket::explode(float frametime, Terrain &terrain){
	EntityManager::getInstance().addEntity(new Explosion(sprite.getPosition(), terrain, 50, frametime));
	dead = true;
}
