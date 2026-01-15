#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("../res/fonts/Kenney_Future_Narrow.ttf", 32);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
		k->defaultPos = Point2(getRandom(0, 720), getRandom(0, 480));
		k->pos = k->defaultPos;
		if (k->pos.x > settingsButton.box.x) k->pos.x = settingsButton.box.x - 50;
		if (k->pos.y > settingsButton.box.y + settingsButton.box.h) k->pos.x = settingsButton.box.y + 50;
		gameKeys.push_back(k);
	}
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed*speedScale;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed * speedScale;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed * speedScale;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed * speedScale;
	}
}

void MyGame::update() {
	Dimension2i windowSize = gfx->getCurrentWindowSize();
	box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 200;
			key->isAlive = false;
			numKeys--;
			sfx->playSound(pickUp);
		}
		if (windowSize.w == 720) key->pos = key->defaultPos;
		if (windowSize.w == 1280) key->pos = Point2(int(key->defaultPos.x * 1.7777778), int(key->defaultPos.y * 1.5));
		if (windowSize.w == 1920) key->pos = Point2(int(key->defaultPos.x * 2.6666667), int(key->defaultPos.y * 2.25));
		if (gfx->getFullscreen()) {
			Dimension2i maxScreen = gfx->getMaximumWindowSize();
			key->pos = Point2(int(key->defaultPos.x * (maxScreen.w / 720)), int(key->defaultPos.y * (maxScreen.w / 480)));
		}
		
	}
	velocity.x = 0;
	velocity.y = 0;

	if (numKeys == 0) {
		gameWon = true;
	}
}
void MyGame::updateUI()
{

	Dimension2i windowSize = gfx->getCurrentWindowSize();
	if (windowSize.w == 720)
	{
		scaled = false;
		buttons.clear();
		sliders.clear();
		dropDowns.clear();
		settingsButton.box = { 520,1,200,100 };
		settingsText.x = 60; settingsText.y = 60;
		musicText.x = 60; musicText.y = 200;
		soundEffectText.x = 60; soundEffectText.y = 300;
		playButton.box = { 480,340,200,100 };
		settingsRect = { 40, 40, 640, 400 };
		if (!scaled)
		{
			for (MyEngineSystem::Slider::sliderData* data : sliderData)
			{
				if (data->dot.y == 355 || data->dot.y == 480)
				{
					data->dot.x -= 100 + int(((data->dot.x - data->box.x) / data->box.w) * data->box.w);
					data->dot.w = 15; data->dot.h = 30;
				}
				else if (data->dot.y == 545 || data->dot.y == 745)
				{
					data->dot.x -= 240 + int(((data->dot.x - data->box.x) / data->box.w) * data->box.w);
					data->dot.w = 15; data->dot.h = 30;
				}
			}
			box.x /= speedScale;
			box.y /= speedScale;
			speedScale = 1;
			scaled = true;
		}
		musicSlider.box = { 60,250,300,20 };
		soundEffectSlider.box = { 60,350,300,20 };
		musicSlider.dot.y = 245;
		musicSlider.dot.w = 15;
		musicSlider.dot.h = 30;
		soundEffectSlider.dot.y = 345;
		soundEffectSlider.dot.w = 15;
		soundEffectSlider.dot.h = 30;
		resolution.box = { 450, 100, 180, 40 };
		fontSize = 32;
	}// ------------


	if (windowSize.w == 1280)
	{
		scaled = false;
		buttons.clear();
		sliders.clear();
		dropDowns.clear();
		settingsButton.box = { 1040,1,240,100 };
		settingsText.x = 160; settingsText.y = 160;
		musicText.x = 160; musicText.y = 300;
		soundEffectText.x = 160; soundEffectText.y = 420;
		playButton.box = { 960,350,200,100 };
		settingsRect = { 120, 120, 1040, 480 };
		if (!scaled)
		{
			for (MyEngineSystem::Slider::sliderData* data : sliderData)
			{
				if (data->dot.y == 245 || data->dot.y == 345)
				{
					data->dot.x += 100 + int(((data->dot.x - data->box.x) / data->box.w) * data->box.w);
					data->dot.w = 15; data->dot.h = 30;
				}
				else if (data->dot.y == 545 || data->dot.y == 745)
				{
					data->dot.x -= 140 + int(((data->dot.x - data->box.x) / data->box.w) * data->box.w);
					data->dot.w = 15; data->dot.h = 30;
				}
			}
			if (speedScale == 1)
			{
				speedScale = 1.5;
				box.x *= speedScale;
				box.y *= speedScale;
			}
			if (speedScale == 2)
			{
				box.x /= speedScale;
				box.y /= speedScale;
				speedScale = 1.5;
				box.x *= speedScale;
				box.y *= speedScale;
			}
		}
		//musicSlider.box.x = 160; musicSlider.box.w = 300;
		//soundEffectSlider.box.x = 160; soundEffectSlider.box.w = 300;
		musicSlider.box = {160, 360, 300, 20};
		soundEffectSlider.box = { 160,485,300,20 };
		soundEffectSlider.dot.y = 480;
		musicSlider.dot.y = 355;
		scaled = true;
		resolution.box = { 650, 300, 210, 60 };
		fontSize = 38;
	}// -------------


	if (windowSize.w == 1920)
	{
		scaled = false;
		buttons.clear();
		sliders.clear();
		dropDowns.clear();
		settingsButton.box = { 1520,1,400,200 };
		settingsText.x = 300; settingsText.y = 280;
		musicText.x = 300; musicText.y = 460;
		soundEffectText.x = 300; soundEffectText.y = 660;
		playButton.box = { 1280,600,400,200 };
		settingsRect = { 240, 200, 1440, 680 };
		if (!scaled)
		{
			for (MyEngineSystem::Slider::sliderData* data : sliderData)
			{
				if (data->dot.y == 245 || data->dot.y == 345)
				{
					data->dot.x += 240 + int(((data->dot.x - data->box.x) / data->box.w) * data->box.w);
					data->dot.w = 25; data->dot.h = 40;
				}
				else if (data->dot.y == 355 || data->dot.y == 480)
				{
					data->dot.x += 140 + int(((data->dot.x - data->box.x) / data->box.w) * data->box.w);
					data->dot.w = 25; data->dot.h = 40;
				}
			}
			if (speedScale == 1)
			{
				speedScale = 2;
				box.x *= speedScale;
				box.y *= speedScale;
			}
			if (speedScale == 1.5)
			{
				box.x /= speedScale;
				box.y /= speedScale;
				speedScale = 2;
				box.x *= speedScale;
				box.y *= speedScale;
			}
			scaled = true;
		}
		musicSlider.box = { 300,550,500,30 };
		musicSlider.dot.y = 545;
		soundEffectSlider.box = { 300,750,500,30 };
		soundEffectSlider.dot.y = 745;
		resolution.box = { 900, 400, 350, 75 };
		fontSize = 50;
	}// ----------------

} // ===================

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : gameKeys)
        if (key->isAlive)
		    gfx->drawCircle(key->pos, 5);
}

void MyGame::renderUI()
{
	Dimension2i windowSize = gfx->getCurrentWindowSize();
	if (paused)
	{
		gfx->useFont(ResourceManager::loadFont("../res/fonts/Kenney_Future_Narrow.ttf", fontSize));

		gfx->setDrawColor(SDL_COLOR_GRAY);
		gfx->fillRect(settingsRect.x, settingsRect.y, settingsRect.w, settingsRect.h);

		buttons.push_back(mySystem->createButton(playButton));
		gfx->setDrawColor(SDL_COLOR_BLACK);

		gfx->drawText("Settings", settingsText.x, settingsText.y);
		gfx->drawText("Music", musicText.x, musicText.y);
		gfx->drawText("Sound Effects", soundEffectText.x, soundEffectText.y);

		gfx->useFont(ResourceManager::loadFont("../res/fonts/arial.ttf", fontSize));

		if (dropDown == -1)
			dropDowns.push_back(mySystem->createDropDown(resolution));
		if (dropDown == resolution.ID)
			dropDowns.push_back(mySystem->createDropDown(resolution));

		sliders.push_back(mySystem->createSlider(musicSlider));
		sliders.push_back(mySystem->createSlider(soundEffectSlider));

		buttonData.clear();
		dropDownData.clear();
		sliderData.clear();

		buttonData.push_back(&settingsButton);
		buttonData.push_back(&playButton);
		dropDownData.push_back(&resolution);
		sliderData.push_back(&musicSlider);
		sliderData.push_back(&soundEffectSlider);
	}
	if (!paused)
	{
		gfx->useFont(ResourceManager::loadFont("../res/fonts/Kenney_Future_Narrow.ttf", fontSize));
		buttons.push_back(mySystem->createButton(settingsButton));
		gfx->setDrawColor(SDL_COLOR_AQUA);
		std::string scoreStr = std::to_string(score);
		gfx->drawText(scoreStr, (windowSize.w / 2) - (scoreStr.length() * 25), 25);
	}
}
