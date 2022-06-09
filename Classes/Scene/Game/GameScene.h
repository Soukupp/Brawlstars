//作者 : 李元特
//日期 : 2022-5-18

//修改 : 王鹏
//日期 : 2022-5-20
//增加了Player头文件 Weapon头文件
//将人物从Sprite类替换为Player类 

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "MapLayer.h"
#include "SkillButton.h"
#include "Scene/Settings/GameSettingsScene.h"
#include "Scene/MainMenu/MainMenuScene.h"


#define GAME_BACK_TO_MENU_POSITION_X origin.x + visibleSize.width - 2.5 * BackToMenuItem->getContentSize().width / 2
#define GAME_BACK_TO_MENU_POSITION_Y origin.y + 1.2 * BackToMenuItem->getContentSize().height / 2

#define GAME_SETTING_POSITION_X origin.x + visibleSize.width - 2.5 * SettingsItem->getContentSize().width / 2
#define GAME_SETTING_POSITION_Y visibleSize.height - 1.2 * SettingsItem->getContentSize().height / 2

#define GAME_SKILL_BUTTON_POSITION_X origin.x + 1.5 * 40
#define GAME_SKILL_BUTTON_POSITION_Y origin.y + 1.5 * 40


class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    //cocos2d::Sprite* _SafeArea;

    //void updateForSafeArea(float delta);


    void menuCallback(cocos2d::Ref* pSender);
    void GameSettingsCallBack(cocos2d::Ref* pSender);

    int getUserInt(const char* name);
    void setUserInt(const char* name, int num);

    //void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // 必须要加作用域！！！

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
