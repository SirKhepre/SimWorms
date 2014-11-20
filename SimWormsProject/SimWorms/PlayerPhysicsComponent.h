#pragma once
#include "PhysicsComponent.h"
class Player;
class PlayerPhysicsComponent : public PhysicsComponent
{
public:
	void update(Player &player, Terrain &terrain, float frametime);
	void checkCollision(Player &player, Terrain &terrain, float frametime);
	bool isInMidAir(Player &player);
	bool isUpperBoundBlocked;
	bool isUpperBoundBlockedFromLeft;
	bool isUpperBoundBlockedFromRight;
	void stopMovingX(Player &player);
	void stopMovingY(Player &player);
};

