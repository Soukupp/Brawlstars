//作者 : 李元特
//日期 : 2022-6-10

#ifndef __GAMELOADING1_SCENE_H__
#define __GAMELOADING1_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Scene/MainMenu/MainMenuScene.h"
#include "GameLoadingScene2.h"

using namespace CocosDenshion;

class GameLoadingScene1 : public cocos2d::Scene
{

public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void changeScene(float dt);

    CREATE_FUNC(GameLoadingScene1);
};

#endif //__GAMELOADING1_SCENE_H__

