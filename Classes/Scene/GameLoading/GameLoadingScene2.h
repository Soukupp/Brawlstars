//作者 : 李元特
//日期 : 2022-6-10

#ifndef __GAMELOADING2_SCENE_H__
#define __GAMELOADING2_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Scene/Game/GameScene.h"

using namespace CocosDenshion;

class GameLoadingScene2 : public cocos2d::Scene
{

public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void changeScene(float dt);

    CREATE_FUNC(GameLoadingScene2);
};

#endif //__GAMELOADING2_SCENE_H__

