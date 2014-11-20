#include "PlayerPhysicsComponent.h"
#include "Player.h"

void PlayerPhysicsComponent::update(Player &player, Terrain &terrain, float frametime){
	addConstraint(sdl::Vector2Float(0, 10) * frametime);
	checkCollision(player, terrain, frametime);
	isUpperBoundBlocked = false;
	isUpperBoundBlockedFromLeft = false;
	isUpperBoundBlockedFromRight = false;
}

void PlayerPhysicsComponent::checkCollision(Player &player, Terrain &terrain, float frametime){
	sdl::Vector2Float playerVelocity = player.getVelocity() + resultingVector;
	sdl::Vector2Float finalPos = player.getPosition() + resultingVector;
	// is upper bound blocked...
	for (float y = finalPos.y; y <= finalPos.y + (player.getBounds().h / 2); y++){
		for (float x = finalPos.x; x <= finalPos.x + player.getBounds().w; x++){
			if (player.isPixelSolid(sdl::Vector2Float(x, y) - finalPos) && terrain.isPixelSolid(sdl::Vector2Float(x, y))){
				isUpperBoundBlockedFromLeft = resultingVector.x < 0;
				isUpperBoundBlockedFromRight = resultingVector.x > 0;
				isUpperBoundBlocked = true;
				stopMovingY(player);
				stopMovingX(player);
				while (terrain.isPixelSolid(player.getPosition())){
					player.setPosition(player.getPosition() + sdl::Vector2Float(0, 1));
				}
				return;
			}
		}
	}
	isUpperBoundBlockedFromLeft = false;
	isUpperBoundBlockedFromRight = false;
	isUpperBoundBlocked = false;
	// is not moving in x...
	if (playerVelocity.x == 0){
		for (float y = finalPos.y + player.getBounds().h; y >= finalPos.y + (player.getBounds().h / 2); y--){
			for (float x = finalPos.x; x <= finalPos.x + player.getBounds().w; x++){
				if (player.isPixelSolid(sdl::Vector2Float(x, y) - finalPos) && terrain.isPixelSolid(sdl::Vector2Float(x, y))){
					stopMovingY(player);
					while (terrain.isPixelSolid(sdl::Vector2Float(x, y-- - 1))){
						player.setPosition(player.getPosition() - sdl::Vector2Float(0, 1));
					}
					if (!isSliding(player, terrain, x, y, frametime))
						player.setVelocity(resultingVector + player.getVelocity());
					player.setPosition(player.getPosition() + player.getVelocity());
					return;
				}
			}
		}
	}
	// is going left...
	else if (playerVelocity.x < 0 && !isUpperBoundBlockedFromLeft){
		for (float x = finalPos.x; x <= finalPos.x + (player.getBounds().w / 2); x++){
			for (float y = finalPos.y + player.getBounds().h; y >= finalPos.y; y--){
				if (player.isPixelSolid(sdl::Vector2Float(x, y) - finalPos) && terrain.isPixelSolid(sdl::Vector2Float(x, y))){
					while (terrain.isPixelSolid(sdl::Vector2Float(x, y--))){
						player.setPosition(player.getPosition() - sdl::Vector2Float(0, 1));
					}
					if (!isSliding(player, terrain, x, y, frametime))
						player.setVelocity(resultingVector + playerVelocity);
					player.setPosition(player.getPosition() + player.getVelocity());
					return;
				}
			}
		}
	}
	// is going right...
	else if (playerVelocity.x > 0 && !isUpperBoundBlockedFromRight){
		for (float x = finalPos.x + player.getBounds().w; x >= finalPos.x + (player.getBounds().w / 2); x--){
			for (float y = finalPos.y + player.getBounds().h; y >= finalPos.y; y--){
				if (player.isPixelSolid(sdl::Vector2Float(x, y) - finalPos) && terrain.isPixelSolid(sdl::Vector2Float(x, y))){
					while (terrain.isPixelSolid(sdl::Vector2Float(x, y--))){
						player.setPosition(player.getPosition() - sdl::Vector2Float(0, 1));
					}
					if (!isSliding(player, terrain, x, y, frametime))
						player.setVelocity(resultingVector + playerVelocity);
					player.setPosition(player.getPosition() + player.getVelocity());
					return;
				}
			}
		}
	}
	player.setVelocity(resultingVector + player.getVelocity());
	player.setPosition(player.getPosition() + player.getVelocity());
}
bool PlayerPhysicsComponent::isSliding(Player &player, Terrain &terrain, float x, float y, float frametime){
	float terrainNormalX = terrain.getNormal(sdl::Vector2Float(x, y)).x;
	if (terrainNormalX > 0.9 || terrainNormalX < -0.9){
		//stopMovingX(player);
		addConstraint(sdl::Vector2Float(25 * terrainNormalX, resultingVector.y) * frametime);
		player.setVelocity(resultingVector + player.getVelocity());
		cannotMove = true;
		return true;
	}
	cannotMove = false;
	return false;
}
void PlayerPhysicsComponent::stopMovingX(Player &player){
	resultingVector = sdl::Vector2Float(0, resultingVector.y);
	player.setVelocity(resultingVector);
}
void PlayerPhysicsComponent::stopMovingY(Player &player){
	resultingVector = sdl::Vector2Float(resultingVector.x, 0);
	player.setVelocity(resultingVector);
}
bool PlayerPhysicsComponent::canMove(Player &player){
	return (player.getVelocity().y != 0 || cannotMove);
}