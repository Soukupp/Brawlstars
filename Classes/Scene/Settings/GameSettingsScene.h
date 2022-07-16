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

#define GAMESETTINGS_BACK_ITEM_POSITION_X static_cast<float>(origin.x + settingsBackItem->getContentSize().width / 2)
#define GAMESETTINGS_BACK_ITEM_POSITION_Y static_cast<float>(origin.y + settingsBackItem->getContentSize().height / 2)

#define GAMESETTINGS_BACK_TO_MENU_POSITION_X static_cast<float>(origin.x + visibleSize.width - backToMenuItem->getContentSize().width / 2 * 1.5)
#define GAMESETTINGS_BACK_TO_MENU_POSITION_Y static_cast<float>(origin.y + backToMenuItem->getContentSize().height / 2 * 1.5)

#define GAMESETTINGS_NAME_LABEL_POSITION_X static_cast<float>(origin.x + visibleSize.width / 2)
#define GAMESETTINGS_NAME_LABEL_POSITION_Y static_cast<float>(origin.y + visibleSize.height - settingsNameLabel->getContentSize().height)

#define GAMESETTINGS_BACKGROUND_POSITION_X static_cast<float>(visibleSize.width / 2 + origin.x)
#define GAMESETTINGS_BACKGROUND_POSITION_Y static_cast<float>(visibleSize.height / 2 + origin.y)

#define GAMESETTINGS_SETTINGSMENU_POSITION_X static_cast<float>(visibleSize.width / 2 + origin.x)
#define GAMESETTINGS_SETTINGSMENU_POSITION_Y static_cast<float>(visibleSize.height / 2 * 1.25 + origin.y)

#define GAMESETTINGS_SETTINGSMUSICLABEL_POSITION_X static_cast<float>(visibleSize.width / 2 * 0.5 + origin.x)
#define GAMESETTINGS_SETTINGSMUSICLABEL_POSITION_Y static_cast<float>(visibleSize.height / 2 * 1.4 + origin.y)

#define GAMESETTINGS_SETTINGMUSICSTATES_POSITION_X static_cast<float>(visibleSize.width / 4 + origin.x)
#define GAMESETTINGS_SETTINGMUSICSTATES_POSITION_Y static_cast<float>(visibleSize.height / 2  + origin.y)

#define GAMESETTINGS_SETTINGFPSSTATES_POSITION_X static_cast<float>(visibleSize.width / 7 -130)
#define GAMESETTINGS_SETTINGFPSSTATES_POSITION_Y static_cast<float>(visibleSize.height /15-150)

#define GAMESETTINGS_SETTINGSFPSLABEL_POSITION_X static_cast<float>(visibleSize.width / 4 + origin.x)
#define GAMESETTINGS_SETTINGSFPSLABEL_POSITION_Y static_cast<float>(visibleSize.height / 3 + origin.y+20)

#define GAMESETTINGS_TEXT_RGB_COLOR 0, 0, 0

#define GAMESETTINGS_NAME_LABEL_SIZE 64


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

    virtual bool init();  // 返回游戏界面回调函数
    
    void settingsBackToGameCallback(cocos2d::Ref* pSender);  // 按钮回调函数
    void settingsPlayCallBack(cocos2d::Ref* pSender);
    void menuCallback(Ref* pSender);

    void sliderEvent(Ref* pSender, Slider::EventType type);   // 滑动事件监听

    void settingsFPSCallBack(cocos2d::Ref* pSender);

    CREATE_FUNC(GameSettingsScene);

private:
    Text* _displayedPercentage;          //显示音量百分比
    //Text* _displayedMusicStates = Text::create("MUSIC ON", "fonts/PixeloidSans.ttf", 27);    //显示音乐开关
    //Text* _displayedFPSStates = Text::create("FPS DISPLAY", "fonts/PixeloidSans.ttf", 27);   //显示FPS显示或隐藏
    Label* _displayedMusicStates = Label::create("MUSIC ON", "Maiandra GD", 35);
    Label* _displayedFPSStates = Label::create("FPS DISPLAY", "Maiandra GD", 35);
};

#endif  //__GAMESETTINGS_SCENE_H__
