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



class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    void menuCloseCallback(cocos2d::Ref* pSender);
    void GameSettingsCallBack(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
