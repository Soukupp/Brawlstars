#ifndef __LOADING_SCENE_H__
#define __LODING_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"





class LoadingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void changeScene(float dt);

    CREATE_FUNC(LoadingScene);
};

#endif // __LOADING_SCENE_H__
