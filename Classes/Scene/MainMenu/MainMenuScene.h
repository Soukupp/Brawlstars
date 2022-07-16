//作者 : 王鹏
//日期 : 2022-5-14

#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#define MAINMENU_CLOSE_ITEM_POSITION_X origin.x + visibleSize.width - mainMenuCloseItem->getContentSize().width / 2
#define MAINMENU_CLOSE_ITEM_POSITION_Y origin.y + mainMenuCloseItem->getContentSize().height / 2

#define MAINMENU_INFO_ITEM_POSITION_X origin.x + visibleSize.width - mainMenuInfoItem->getContentSize().width
#define MAINMENU_INFO_ITEM_POSITION_Y origin.y + visibleSize.height - mainMenuInfoItem->getContentSize().height

#define MAINMENU_GAMENAME_LABEL_POSITION_X origin.x + visibleSize.width / 2
#define MAINMENU_GAMENAME_LABEL_POSITION_Y origin.y + visibleSize.height - gameNameLabel->getContentSize().height

#define MAINMENU_BACKGROUND_POSITION_X visibleSize.width / 2 + origin.x
#define MAINMENU_BACKGROUND_POSITION_Y visibleSize.height / 2 + origin.y

#define MAINMENU_MAINMENU_POSITION_X visibleSize.width / 2 + origin.x
#define MAINMENU_MAINMENU_POSITION_Y origin.y + mainMenu->getContentSize().height / 2

#define MAINMENU_PLAYERMASSAGE_POSITION_X origin.x + playerMassageItem->getContentSize().width
#define MAINMENU_PLAYERMASSAGE_POSITION_Y origin.y + visibleSize.height - playerMassageItem->getContentSize().width

#define MAINMENU_TEXT_RGB_COLOR 105, 105, 105
#define MAINMENU_TITLE_RGB_COLOR 238, 201, 0

#define MAINMENU_GAMENAME_LABEL_SIZE 96

#define MAINMENU_INFORMATION_POSITION_X visibleSize.width / 2 + origin.x
#define MAINMENU_INFORMATION_POSITION_Y visibleSize.height / 2 + origin.y

#define MAINMENU_INFORMATION_CONTENT_TEXT_PADDING 32
#define MAINMENU_INFORMATION_CONTENT_TEXT_PADDINGTOP 75

#include "cocos2d.h"
#include "Scene/Game/GameScene.h"
#include "Scene/Options/StoreScene.h"
#include "Scene/Options/HeroScene.h"
#include "Scene/Settings/SettingsScene.h"
#include "Scene/Information/InformationPopLayer.h"
#include "Scene/GameLoading/GameLoadingScene1.h"
#include "windows.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void onEnterTransitionDidFinish();

    //关闭主界面
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuInfoCallback(cocos2d::Ref* pSender);

    //菜单项回调函数
    void menuStartCallback(cocos2d::Ref* pSender);
    void menuMapCallback(cocos2d::Ref* pSender);
    void menuHerosCallback(cocos2d::Ref* pSender);
    void menuSettingsCallback(cocos2d::Ref* pSender);

    void playerMassageCallback(cocos2d::Ref* pSender);

    //创建
    CREATE_FUNC(MainMenuScene);
};

#endif
