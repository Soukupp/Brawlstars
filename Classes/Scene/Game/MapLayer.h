//���� : ��Ԫ��
//���� : 2022-5-20

#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Entity/Player/Player.h"


class MapLayer : public cocos2d::Layer
{
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _collidable;
    cocos2d::TMXLayer* _watermonster;
    Player* _player;
   /* Player _try1;
    Player* _try1 = &_try1;*/
    
   
    Weapon* _weapon;//Weaponͷ�ļ��Ѿ�������Playerͷ�ļ�����
// cocos2d:: Sprite* _groundmonster;
public:

    virtual bool init();

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // ����Ҫ�������򣡣���
  

    void setPlayerPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);

    // implement the "static create()" method manually
    CREATE_FUNC(MapLayer);
};

#endif // __GAME_SCENE_H__
