#pragma once
//作者：束赫
//创建日期：2022-5-17
 
#include "cocos2d.h"

class PlayerScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void player1_Callback(cocos2d::Ref* pSender);
    void player2_Callback(cocos2d::Ref* pSender);
    void player3_Callback(cocos2d::Ref* pSender);
    void player4_Callback(cocos2d::Ref* pSender);

    void playerSceneCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(PlayerScene);
};
