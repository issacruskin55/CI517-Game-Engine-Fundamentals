#include "MyEngineSystem.h"

MyEngineSystem::MyEngineSystem(std::shared_ptr<GraphicsEngine> graphicsRef, std::shared_ptr<AudioEngine> audioRef) {
	gfx = graphicsRef;
	sfx = audioRef;
	}

MyEngineSystem::Button* MyEngineSystem::createButton(Button::buttonData data ) {
	Button* button = new Button;
	button->gfx = gfx;
	button->data = Button::buttonData{
	data.ID,
	data.text,
	data.box,
	data.textColor,
	data.isDropDownButton,
	data.texture
	};
	SDL_Rect boxSDL = { button->data.box.x, button->data.box.y, button->data.box.w, button->data.box.h};
	gfx->drawTexture(button->data.texture, &boxSDL, SDL_FLIP_NONE);
	gfx->setDrawColor(button->data.textColor);
	gfx->drawText(button->data.text, button->data.box.x + (button->data.box.w/20), button->data.box.y + (button->data.box.h / 5));
	return button;
}
bool MyEngineSystem::Button::onClicked() { 
	if (this->data.ID == 0) { return true;} // settings button pressed so game will pause
	if (this->data.ID == 1) { return false;} // play button pressed so game will unpause

}
void MyEngineSystem::Button::onClicked(int dropID) {
	if (dropID == 0)
	{
		if (this->data.ID == 1)
		{
			gfx->setFullscreen(false);
			gfx->setWindowSize(720, 480);
		}
		else if (this->data.ID == 2)
		{
			gfx->setFullscreen(false);
			gfx->setWindowSize(1280, 720);
		}
		else if (this->data.ID == 3)
		{
			gfx->setFullscreen(false);
			gfx->setWindowSize(1920, 1080);
		}
	}
}

MyEngineSystem::Slider* MyEngineSystem::createSlider(Slider::sliderData data) {
	Slider* slider = new Slider;
	slider->gfx = gfx;
	slider->sfx = sfx;
	slider->data = Slider::sliderData{
		data.ID,
		data.Margin,
		data.held,
		data.unfilledColor,
		data.filledColor,
		data.dotColor,
		data.box,
		data.dot
	};
	gfx->setDrawColor(slider->data.unfilledColor);
	gfx->fillRect(slider->data.unfilled.x, slider->data.unfilled.y, slider->data.unfilled.w, slider->data.unfilled.h);
	gfx->setDrawColor(slider->data.filledColor);
	gfx->fillRect(slider->data.filled.x, slider->data.filled.y, slider->data.filled.w, slider->data.filled.h);
	gfx->setDrawColor(slider->data.dotColor);
	gfx->fillRect(slider->data.dot.x, slider->data.dot.y, slider->data.dot.w, slider->data.dot.h);
	return slider;
}

void MyEngineSystem::Slider::sliding(sliderData* data, Point2 mousePos) {
	if (data->ID == 0){ // Music slider
		data->dot.x = mousePos.x;
		if (data->dot.x > data->box.x + data->box.w)
			data->dot.x = data->box.x + data->box.w;
		if (data->dot.x < data->box.x)
			data->dot.x = data->box.x;
		Mix_VolumeMusic(this->data.progress);
	}
	if (data->ID == 1){ // Sound effect slider
		data->dot.x = mousePos.x;
		if (data->dot.x > data->box.x + data->box.w)
			data->dot.x = data->box.x + data->box.w;
		if (data->dot.x < data->box.x)
			data->dot.x = data->box.x;
		sfx->setSoundVolume(this->data.progress);
	}
}

MyEngineSystem::dropDown* MyEngineSystem::createDropDown(dropDown::dropDownData data) {
	dropDown* drop = new dropDown;
	drop->gfx = gfx;
	drop->data = dropDown::dropDownData{
		data.ID,
		data.boxText,
		data.box,
		data.textColor,
		data.optionsText,
		data.selected,
		data.mainTexture,
		data.subTexture
	};
	drop->data.buttonsVector.push_back(createButton({ drop->data.ID, drop->data.boxText, drop->data.box, 
		drop->data.textColor,true, drop->data.mainTexture }));
	if (drop->data.selected) {
		for (int i = 1; i < drop->data.optionsText.size(); i++)
		{
			MyEngineSystem::Button::buttonData button;
			button = {
				drop->data.ID + i,
				drop->data.optionsText[i],
				{drop->data.box.x, drop->data.box.y + (drop->data.box.h*i), drop->data.box.w, drop->data.box.h},
				drop->data.textColor,
				true,
				drop->data.subTexture
			};
			drop->data.buttonsVector.push_back(createButton(button));
		}
	}
	return drop;
}

void MyEngineSystem::dropDown::selected(dropDownData* data, MyEngineSystem::Button* button) {
	if (data->ID == 0)
	{
		button->onClicked(this->data.ID);
		data->boxText = button->data.text;
		data->selected = false;
		this->data.selected = false;
	}
}
