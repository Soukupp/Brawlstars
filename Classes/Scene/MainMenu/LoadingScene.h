#ifndef __LOADING_SCENE_H__
#define __LODING_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"

#define LOADING_BACKGROUND_POSITION origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2
#define LOADING_BSLOGO_POSITION origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2
#define LOADING_TJLOGO_POSITION origin.x + visibleSize.width - Tongji->getContentSize().width, visibleSize.height - 1.2 * Tongji->getContentSize().height / 2
#define LOADING_TIP1_POSITION origin.x + visibleSize.width / 2, visibleSize.height - 3 * tip1->getContentSize().height
#define LOADING_TIP2_POSITION origin.x + visibleSize.width / 2, 3 * tip2->getContentSize().height
#define LOADING_TIP3_POSITION origin.x + visibleSize.width / 2, 5 * tip3->getContentSize().height


class LoadingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void changeScene(float dt);

    CREATE_FUNC(LoadingScene);
};

#endif // __LOADING_SCENE_H__
