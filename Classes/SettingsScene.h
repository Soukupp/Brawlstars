#pragma once
//作者 : 王鹏
//日期 : 2022-5-17
#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#define SETTINGS_BACK_ITEM_POSITION_X origin.x + settingsBackItem->getContentSize().width / 2
#define SETTINGS_BACK_ITEM_POSITION_Y origin.y + settingsBackItem->getContentSize().height / 2


#define SETTINGS_NAME_LABEL_POSITION_X origin.x + visibleSize.width / 2
#define SETTINGS_NAME_LABEL_POSITION_Y origin.y + visibleSize.height - settingsNameLabel->getContentSize().height

#define SETTINGS_BACKGROUND_POSITION_X visibleSize.width / 2 + origin.x
#define SETTINGS_BACKGROUND_POSITION_Y visibleSize.height / 2 + origin.y

#define SETTINGS_SETTINGSMENU_POSITION_X visibleSize.width / 2 + origin.x
#define SETTINGS_SETTINGSMENU_POSITION_Y origin.y + settingsMenu->getContentSize().height / 2

#define SETTINGS_TEXT_RGB_COLOR 31, 91, 116


#define SETTINGS_NAME_LABEL_SIZE 64


#include "cocos2d.h"
#include "MainMenuScene.h"

class SettingsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //返回主菜单回调函数
    void settingsBackCallback(cocos2d::Ref* pSender);
    //按钮回调函数
    
    //创建
    CREATE_FUNC(SettingsScene);
};

#endif  //__SETTINGS_SCENE_H__
