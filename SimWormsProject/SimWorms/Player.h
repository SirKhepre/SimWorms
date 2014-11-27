#pragma once
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "AssetsManager.h"
#include "Entity.h"
class Player : public Entity
{
private:
	PlayerInputComponent input;
	int heal;
public:
	Player(sdl::Vector2Float &position);
	void draw(sdl::Window &target);
	void update(float frametime, Terrain& terrain);
	bool isDead();
	int getHeal(); // Ajout par Nathan
	bool getDirection(); // Ajout par Nathan
	void setHeal(int heal); // Ajout par Nathan
};

