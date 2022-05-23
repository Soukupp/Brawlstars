//作者 : 李元特
//日期 : 2022-5-18

#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "Scene/MainMenu/MainMenuScene.h"

class GameOverScene : public cocos2d::Layer
{
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _collidable;
    cocos2d::Sprite* _player;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
  
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};

#endif // __GAMEOVER_SCENE_H__
