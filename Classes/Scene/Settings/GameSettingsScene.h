#pragma once
//作者 : 王鹏
//日期 : 2022-5-17
//实现 ：框架搭建
// 
//作者 ：束赫
//日期 : 2022-5-19
//实现 ：具体功能实现
// 
//作者 ：李元特
//日期 : 2022-5-21
//实现 ：对接游戏界面

#ifndef __GAMESETTINGS_SCENE_H__
#define __GAMESETTINGS_SCENE_H__

#define SETTINGS_BACK_ITEM_POSITION_X origin.x + settingsBackItem->getContentSize().width / 2
#define SETTINGS_BACK_ITEM_POSITION_Y origin.y + settingsBackItem->getContentSize().height / 2


#define SETTINGS_NAME_LABEL_POSITION_X origin.x + visibleSize.width / 2
#define SETTINGS_NAME_LABEL_POSITION_Y origin.y + visibleSize.height - settingsNameLabel->getContentSize().height

#define SETTINGS_BACKGROUND_POSITION_X visibleSize.width / 2 + origin.x
#define SETTINGS_BACKGROUND_POSITION_Y visibleSize.height / 2 + origin.y

#define SETTINGS_SETTINGSMENU_POSITION_X visibleSize.width / 2 + origin.x
#define SETTINGS_SETTINGSMENU_POSITION_Y visibleSize.height / 2 * 1.25 + origin.y

#define SETTINGS_SETTINGSMUSICLABEL_POSITION_X visibleSize.width / 2 * 0.5 + origin.x
#define SETTINGS_SETTINGSMUSICLABEL_POSITION_Y visibleSize.height / 2 * 1.4 + origin.y

#define SETTINGS_SETTINGMUSICSTATES_POSITION_X visibleSize.width / 4 + origin.x
#define SETTINGS_SETTINGMUSICSTATES_POSITION_Y visibleSize.height / 2  + origin.y

#define SETTINGS_SETTINGFPSSTATES_POSITION_X visibleSize.width / 7 -130
#define SETTINGS_SETTINGFPSSTATES_POSITION_Y visibleSize.height /15-150

#define SETTINGS_SETTINGSFPSLABEL_POSITION_X visibleSize.width / 4 + origin.x
#define SETTINGS_SETTINGSFPSLABEL_POSITION_Y visibleSize.height / 3 + origin.y+20

//#define SETTINGS_TEXT_RGB_COLOR 255, 140, 15


#define SETTINGS_NAME_LABEL_SIZE 64


#include "cocos2d.h"
#include "Scene/MainMenu/MainMenuScene.h"
#include "Scene/Game/GameScene.h"
#include "../ui/UISlider.h"
#include <cocos/ui/UIText.h>

using namespace cocos2d::ui;


class GameSettingsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //返回游戏界面回调函数
    void settingsBackToGameCallback(cocos2d::Ref* pSender);
    //按钮回调函数
    void settingsPlayCallBack(cocos2d::Ref* pSender);

    void sliderEvent(Ref* pSender, Slider::EventType type);   //滑动事件监听

    void settingsFPSCallBack(cocos2d::Ref* pSender);

    CREATE_FUNC(GameSettingsScene);

private:
    Text* _displayedPercentage;          //显示音量百分比
    Text* _displayedMusicStates = Text::create("MUSIC ON", "fonts/PixeloidSans.ttf", 27);    //显示音乐开关
    float musicVolume;                   //储存的音量
    Text* _displayedFPSStates = Text::create("FPS DISPLAY", "fonts/PixeloidSans.ttf", 27);   //显示FPS显示或隐藏

};

#endif  //__GAMESETTINGS_SCENE_H__
