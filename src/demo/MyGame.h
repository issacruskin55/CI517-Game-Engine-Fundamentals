#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"

struct GameKey {
	Point2 defaultPos;
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;

		Vector2i velocity;
		int speedScale = 1;
		bool scaled = false;
		int fontSize = 32;

		/* LOADING TEXTURES */
		/* https://kenney.nl/assets/ui-pack */

		SDL_Texture* settingsButtonTexture = ResourceManager::loadTexture("../res/UI_Elements/button_rectangle_border.png", SDL_COLOR_BLUE);
		SDL_Texture* playButtonTexture = ResourceManager::loadTexture("../res/UI_Elements/button_rectangle_border.png", SDL_COLOR_BLUE);
		SDL_Texture* dropDownMain = ResourceManager::loadTexture("../res/UI_Elements/button_rectangle_border.png", SDL_COLOR_BLUE);
		SDL_Texture* dropDownSub = ResourceManager::loadTexture("../res/UI_Elements/button_rectangle_line.png", SDL_COLOR_BLUE);

		MyEngineSystem::Button::buttonData settingsButton = { 0, "Settings", { 520,  1  ,  200  ,  100   }, SDL_COLOR_BLACK, false, settingsButtonTexture };
		MyEngineSystem::Button::buttonData playButton = { 1, "Play", { 350  , 460  ,  200  ,  100  }, SDL_COLOR_BLACK , false, playButtonTexture };
		MyEngineSystem::Slider::sliderData musicSlider = { 0, 2, false, SDL_COLOR_AQUA, SDL_COLOR_GREEN, SDL_COLOR_BLACK, {60,150,300,20} ,{ 90,145,15,30 } };
		MyEngineSystem::Slider::sliderData soundEffectSlider = { 1, 2, false, SDL_COLOR_AQUA, SDL_COLOR_GREEN, SDL_COLOR_BLACK, { 60,200,300,20 }  ,{ 90,195,15,30 } };
		MyEngineSystem::dropDown::dropDownData resolution = { 0, "720x480", { 500  ,  160  , 100  , 30  }, SDL_COLOR_BLACK, 
			{"null","720x480", "1280x720", "1920x1080"}, false, dropDownMain, dropDownSub };

		SDL_Rect settingsRect;
		SDL_Rect settingsText;
		SDL_Rect musicText;
		SDL_Rect soundEffectText;

		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;


		void handleKeyEvents();
		void update();
		void updateUI();
		void render();
		void renderUI();
	public:
        MyGame();
		~MyGame();
};

#endif