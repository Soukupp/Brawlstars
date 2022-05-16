#pragma once
//���� : ����
//���� : 2022-5-14
#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "StoreScene.h"
#include "PlayerScene.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //�ر�������
    void menuCloseCallback(cocos2d::Ref* pSender);

    //�˵���ص�����
    void menuStartCallback(cocos2d::Ref* pSender);
    void menuStoreCallback(cocos2d::Ref* pSender);
    void menuHerosCallback(cocos2d::Ref* pSender);
    void menuSettingsCallback(cocos2d::Ref* pSender);
    //����
    CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__
