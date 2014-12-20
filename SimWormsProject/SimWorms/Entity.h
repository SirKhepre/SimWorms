#pragma once
#include "OOSDL\AnimatedSprite.h"
#include "Terrain.h"
#include "AssetsManager.h"
#include "PlayerPhysicsComponent.h"

#define LEFT false;
#define RIGHT true;
class PhysicsComponent;
class Entity {
protected:
	sdl::Vector2Float position;
	sdl::Vector2Float velocity;
	sdl::Sprite sprite;
	PhysicsComponent *physics;
	bool direction; // true = droite et false = gauche
	int health;
public:
	virtual void update(float frametime, Terrain &terrain) = 0;

	virtual void draw(sdl::Window &target) = 0;

	virtual bool isDead() = 0;

	virtual void explode(float frametime, Terrain &terrain) = 0;
	sdl::Vector2Float& getPosition();
	sdl::Vector2Float& getVelocity();
	sdl::RectFloat& getBounds();
	void setPosition(sdl::Vector2Float& position);
	void setVelocity(sdl::Vector2Float& velocity);
	void addConstraint(sdl::Vector2Float &vector, float frametime);
	bool isPixelSolid(sdl::Vector2Float& position);
	void moveLeft(float frametime);
	void moveRight(float frametime);
	void jump(float frametime);
	void stop();
	int getHealth();
	void setHealth(int health);
	bool isOnGround;
	bool isTopBlocked;
	bool jetpack;
	void setOrigin(sdl::Vector2Float& origin){ this->sprite.setOrigin(origin); };
	void setDirection(bool direction) { this->direction = direction; }
	bool getDirection() { return direction; }
};