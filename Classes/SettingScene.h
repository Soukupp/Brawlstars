#pragma once
//姓名：束赫
//创建日期：2022-5-18
#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__
#include "cocos2d.h"
#include <cocos/ui/UIText.h>
#include "../ui/UISlider.h"
using namespace cocos2d::ui;

#define SETTING_SCENE_MUSIC_TITLE_X visibleSize.width/4
#define SETTING_SCENE_MUSIC_TITLE_Y visibleSize.height/4*3
#define SETTING_SCENE_CLOSE_BUTTON_X visibleSize.width/4*3
#define SETTING_SCENE_CLOSE_BUTTON_Y visibleSize.height/4*3
#define SETTING_SCENE_SLIDER_X visibleSize.width/2
#define SETTING_SCENE_SLIDER_Y visibleSize.height/2
#define SETTING_SCENE_BG_X visibleSize.width/2
#define SETTING_SCENE_BG_Y visibleSize.height/2

#define MAINMENU_TEXT_RGB_COLOR 31, 91, 116

class SettingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void spriteSetting();
	void closeButtonSetting();
	void textSetting();
	void sliderSetting();
	void sliderEvent(Ref* pSender, Slider::EventType type);
	void settingSceneCloseCallback(Ref* pSender);

	CREATE_FUNC(SettingScene);

private:
	float musicVolume;
	Text* _displayedPrecentage;
};
#endif
