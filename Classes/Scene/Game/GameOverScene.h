//作者 : 李元特
//日期 : 2022-5-18

#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "string"
#include "Scene/MainMenu/MainMenuScene.h"
#include "Scene/Information/InformationPopLayer.h"


#define GAMEOVER_HERO_ANIMATON_POSITION 200, 250

#define GAMEOVER_BACKGROUND_POSITION origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2
#define GAMEOVER_TITLE_LABLE_POSITION_X origin.x + visibleSize.width / 2
#define GAMEOVER_TITLE_LABLE_POSITION_Y origin.y + visibleSize.height - 1.3 * label->getContentSize().height



#define GAMEOVER_BACK_ITEM_POSITION_X origin.x + visibleSize.width - 2 * settingsBackItem->getContentSize().width / 2
#define GAMEOVER_BACK_ITEM_POSITION_Y origin.y + settingsBackItem->getContentSize().height / 2

class GameOverScene : public cocos2d::Layer
{
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _collidable;
    cocos2d::Sprite* _player;

public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void hero1();
    void hero2();
    void hero3();
    void hero4();
  
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};

#endif // __GAMEOVER_SCENE_H__
