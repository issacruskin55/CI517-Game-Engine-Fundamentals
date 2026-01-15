#include "AbstractGame.h"

AbstractGame::AbstractGame() : running(true), paused(0), gameTime(0.0) {
	std::shared_ptr<XCube2Engine> engine = XCube2Engine::getInstance();

	// engine ready, get subsystems
	gfx = engine->getGraphicsEngine();
	sfx = engine->getAudioEngine();
	eventSystem = engine->getEventEngine();
	physics = engine->getPhysicsEngine();
    mySystem = engine->getMyEngineSystem();

	Mix_Music* music = ResourceManager::loadMP3("../res/audio/backgroundMusic.MP3");
	pickUp = ResourceManager::loadSound("../res/audio/coinPickUp.MP3");
	Mix_VolumeMusic(10);
	sfx->playMP3(music, -1);
}

AbstractGame::~AbstractGame() {
#ifdef __DEBUG
	debug("AbstractGame::~AbstractGame() started");
#endif

	// kill Game class' instance pointers
	// so that engine is isolated from the outside world
	// before shutting down
	gfx.reset();
	eventSystem.reset();

	// kill engine
	XCube2Engine::quit();

#ifdef __DEBUG
	debug("AbstractGame::~AbstractGame() finished");
	debug("The game finished and cleaned up successfully. Press Enter to exit");
	getchar();
#endif
}

int AbstractGame::runMainLoop() {
#ifdef __DEBUG
	debug("Entered Main Loop");
#endif
	paused = false;
	while (running) {
		gfx->setFrameStart();
		eventSystem->pollEvents();

		if (eventSystem->isPressed(Key::ESC) || eventSystem->isPressed(Key::QUIT))
			running = false;

		handleKeyEvents();
		handleMouseEvents();

		if (!paused) {
			update();
			updatePhysics();

			gameTime += 0.016;	// 60 times a sec
		}
		gfx->clearScreen();
		render();
		updateUI();
		renderUI();
		gfx->showScreen();

		gfx->adjustFPSDelay(16);	// atm hardcoded to ~60 FPS
	}

#ifdef __DEBUG
	debug("Exited Main Loop");
#endif

	return 0;
}

void AbstractGame::handleMouseEvents() {
	if (eventSystem->isPressed(Mouse::BTN_LEFT)) onLeftMouseButton();
	if (eventSystem->isPressed(Mouse::BTN_RIGHT)) onRightMouseButton();
}

void AbstractGame::updatePhysics() {
	physics->update();
}

void AbstractGame::onLeftMouseButton() 
{
	// get mouse pos
	Point2 mousePos = eventSystem->getMousePos();
	
	// detect if mouse press is on button
	for (MyEngineSystem::Button* button : buttons)
	{
		if (!button->data.isDropDownButton && (mousePos.x > button->data.box.x   && mousePos.x < (button->data.box.x + button->data.box.w)  
		&& mousePos.y > button->data.box.y   && mousePos.y < (button->data.box.y + button->data.box.h)  )) {
			paused = button->onClicked();
		}
	}

	for (MyEngineSystem::Slider* slider : sliders)
	{
		if (eventSystem->isPressed(Mouse::BTN_LEFT) && (mousePos.x > slider->data.dot.x-15 && mousePos.x < (slider->data.dot.x + slider->data.dot.w)
		&& mousePos.y > slider->data.dot.y && mousePos.y < (slider->data.dot.y + slider->data.dot.h)))
		{
			for (MyEngineSystem::Slider::sliderData* data : sliderData)
				if (slider->data.ID == data->ID)
				{
					slider->sliding(data, mousePos);
				}
		}
	}

	for (MyEngineSystem::dropDown* drop : dropDowns)
	{
		if (!drop->data.selected && mousePos.x > drop->data.box.x && mousePos.x < (drop->data.box.x + drop->data.box.w) && 
		mousePos.y > drop->data.box.y && mousePos.y < (drop->data.box.y + drop->data.box.h))
		{
			dropDown = drop->data.ID;
			for (MyEngineSystem::dropDown::dropDownData* data : dropDownData)
				if (data->ID == drop->data.ID)
					data->selected = true;
		}
		for (MyEngineSystem::Button* button : drop->data.buttonsVector)
		{
			if (button->data.ID != 0 && drop->data.selected && mousePos.x > button->data.box.x &&
				mousePos.x < (button->data.box.x + button->data.box.w) && mousePos.y > button->data.box.y && 
				mousePos.y < (button->data.box.y + button->data.box.h))
			{
				for (MyEngineSystem::dropDown::dropDownData* data : dropDownData)
					if (drop->data.ID == data->ID)
					{
						drop->selected(data, button);
					}
			}
		}
	}
}

void AbstractGame::onRightMouseButton() {}
void AbstractGame::renderUI() {}
