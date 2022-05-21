//���� : ��Ԫ��
//���� : 2022-5-18

//�޸� : ����
//���� : 2022-5-20
//������Playerͷ�ļ� Weaponͷ�ļ�
//�������Sprite���滻ΪPlayer�� 

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Entity/Player/Player.h"


class GameScene : public cocos2d::Layer
{
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer* _collidable;
    Player* _player;
    Weapon* _weapon;//Weaponͷ�ļ��Ѿ�������Playerͷ�ļ�����

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onEnterTransitionDidFinish();
    virtual void cleanup();

    void menuCloseCallback(cocos2d::Ref* pSender);

    void setPlayerPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
