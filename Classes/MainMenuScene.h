#pragma once
//作者 : 王鹏
//日期 : 2022-5-14
#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#define MAINMENU_CLOSE_ITEM_POSITION_X origin.x + visibleSize.width - mainMenuCloseItem->getContentSize().width / 2
#define MAINMENU_CLOSE_ITEM_POSITION_Y origin.y + mainMenuCloseItem->getContentSize().height / 2

#define MAINMENU_GAMENAME_LABEL_POSITION_X origin.x + visibleSize.width / 2
#define MAINMENU_GAMENAME_LABEL_POSITION_Y origin.y + visibleSize.height - gameNameLabel->getContentSize().height

#define MAINMENU_BACKGROUND_POSITION_X visibleSize.width / 2 + origin.x
#define MAINMENU_BACKGROUND_POSITION_Y visibleSize.height / 2 + origin.y

#define MAINMENU_MAINMENU_POSITION_X visibleSize.width / 2 + origin.x
#define MAINMENU_MAINMENU_POSITION_Y origin.y + mainMenu->getContentSize().height / 2

#define MAINMENU_TEXT_RGB_COLOR 31, 91, 116

#define MAINMENU_GAMENAME_LABEL_SIZE 96

#include "cocos2d.h"
//#include "GameScene.h"
//#include "StoreScene.h"
#include "PlayerScene.h"
#include "SettingScene.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //关闭主界面
    void menuCloseCallback(cocos2d::Ref* pSender);
    //菜单项回调函数
    void menuStartCallback(cocos2d::Ref* pSender);
    void menuStoreCallback(cocos2d::Ref* pSender);
    void menuHerosCallback(cocos2d::Ref* pSender);
    void menuSettingsCallback(cocos2d::Ref* pSender);
    //创建
    CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__
