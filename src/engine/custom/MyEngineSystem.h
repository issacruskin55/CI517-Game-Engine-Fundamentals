#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../GraphicsEngine.h"
#include "../AudioEngine.h"

class MyEngineSystem {
	friend class XCube2Engine;
public:

	std::shared_ptr<GraphicsEngine> gfx;
	std::shared_ptr<AudioEngine> sfx;

	class Button {
	public:
		struct buttonData {
			int ID = -1;
			std::string text = "";
			Rect box{ 0,0,0,0 };
			SDL_Color textColor = SDL_COLOR_BLACK;
			bool isDropDownButton = false;
			SDL_Texture* texture{};
		};
		buttonData data;
		std::shared_ptr<GraphicsEngine> gfx;

		bool onClicked();
		void onClicked(int dropID);

	}; // --------------------

	class Slider {
	public:
		struct sliderData {
			int ID = -1;
			int Margin = 0;
			bool held = false;
			SDL_Color unfilledColor = SDL_COLOR_BLACK;
			SDL_Color filledColor = SDL_COLOR_BLACK;
			SDL_Color dotColor = SDL_COLOR_BLACK;
			Rect box{ 1,1,1,1 };
			Rect dot { box.x,box.y - 5,box.h - 4,box.h + 10 };
			float progress = ((float(dot.x  - box.x) / box.w) * 100);
			Rect filled{ box.x,box.y,int(box.w * progress / 100),box.h };
			Rect unfilled{ (box.x + box.w) - int(box.w * (float(100 - progress) / 100)),
				box.y,int(box.w * (float(100 - progress) / 100)),box.h };
		};
		sliderData data;
		std::shared_ptr<GraphicsEngine> gfx;
		std::shared_ptr<AudioEngine> sfx;

		void sliding(sliderData* data, Point2 mousePos);
	}; // ------------------------------

	class dropDown {
	public:
		struct dropDownData {
			int ID = -1;
			std::string boxText = "";
			Rect box{ 0,0,0,0 };
			SDL_Color textColor = SDL_COLOR_BLACK;
			std::vector<std::string> optionsText;
			bool selected = false;
			SDL_Texture* mainTexture;
			SDL_Texture* subTexture;
			std::vector<Button*> buttonsVector;
		};
		dropDownData data;
		std::shared_ptr<GraphicsEngine> gfx;

		void selected(dropDownData* data, MyEngineSystem::Button* button);
	}; // -------------------------------------

	MyEngineSystem() {};
	MyEngineSystem(std::shared_ptr<GraphicsEngine> graphicsRef, std::shared_ptr<AudioEngine> sfx);

	Button* createButton(Button::buttonData data);
	Slider* createSlider(Slider::sliderData data);
	dropDown* createDropDown(dropDown::dropDownData data);

};


#endif
