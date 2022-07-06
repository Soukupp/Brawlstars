//作者：李元特
//日期：2022-6-6
//实现：loading界面完工


#ifndef __LOADING_SCENE_H__
#define __LODING_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"

#define LOADING_BACKGROUND_POSITION static_cast<float>(origin.x + visibleSize.width / 2), static_cast<float>(origin.y + visibleSize.height / 2)

#define LOADING_BSLOGO_POSITION static_cast<float>(origin.x + visibleSize.width / 2), static_cast<float>(origin.y + visibleSize.height / 2)
#define LOADING_TJLOGO_POSITION static_cast<float>(origin.x + visibleSize.width - 0.8 * Tongji->getContentSize().width), static_cast<float>(visibleSize.height - 1.2 * Tongji->getContentSize().height / 2)

#define LOADING_TIP1_POSITION static_cast<float>(origin.x + visibleSize.width / 2), static_cast<float>(visibleSize.height - 3 * tip1->getContentSize().height)
#define LOADING_TIP2_POSITION static_cast<float>(origin.x + visibleSize.width / 2), static_cast<float>(3 * tip2->getContentSize().height)
#define LOADING_TIP3_POSITION static_cast<float>(origin.x + visibleSize.width / 2), static_cast<float>(5 * tip3->getContentSize().height)

#define LOADING_TIP1_SHADOW Size(5.0f, -5.0f), 150, 10, true
#define LOADING_TIP2_SHADOW Size(5.0f, -5.0f), 150, 10, true
#define LOADING_TIP3_SHADOW Size(5.0f, -5.0f), 150, 10, true

class LoadingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void changeScene(float dt);

    CREATE_FUNC(LoadingScene);
};
#endif // __LOADING_SCENE_H__
