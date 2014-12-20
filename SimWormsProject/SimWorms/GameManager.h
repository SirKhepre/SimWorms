#pragma once
#include "Singleton.h"
#include <sstream>
#include <time.h>

#include "OOSDL/OOSDL.h"

#include "AssetsManager.h"
#include "GameOptionsManager.h"
#include "Player.h"
#include "EventManager.h"
#include "Gui/GuiTextBox.h"
#include "Gui/GuiMainMenu.h"
#include "Grenade.h"
#include "HealPack.h"
#include "Mine.h"
#include "Rocket.h"
#include "Melee.h"
#include "Gui/GuiWeaponMenu.h"
#include "GUI/GuiPauseMenu.h"

#include "Camera.h"

#include "MapManager.h"


class GameManager : public Singleton<GameManager> {
private:
	int tour;
	int numberPlayerOnGround;
	int numberPlayer;
	sdl::Clock tourClock;
	int useObject;
	bool menuPause;
	sdl::StaticText fpsText;
	int useItem;
public:
	GameManager();

	void startGame(int numberTeam);

	void update(sdl::Window& renderWindow, Camera* cam, Map* actualMap, float frametime);

	int getTour();

	void setTour(int tour);

	int getNumberPlayer();

	void setNumberPlayer(int numberPlayer);

	int getUseObject();

	void setUseObject(int useObject);

	bool getMenuPause();
};