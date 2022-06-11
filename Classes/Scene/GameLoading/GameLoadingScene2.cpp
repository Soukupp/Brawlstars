//作者 : 李元特
//日期 : 2022-6-10

#include "GameLoadingScene2.h"

USING_NS_CC;

/****************************
* Name ：GameLoadingScene2::createScene
* Summary ：创建场景
* return ：场景类指针
****************************/
Scene* GameLoadingScene2::createScene()
{
    return GameLoadingScene2::create();
}

/****************************
* Name ：problemLoading
* Summary ：错误打印
* return ：
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

/****************************
* Name ：GameLoadingScene2::init
* Summary ：主菜单初始化
* return ：初始化成功与否
****************************/
bool GameLoadingScene2::init() {
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("background/GameLoadingBackground2.png");
    if (background == nullptr)
    {
        problemLoading("'background/GameLoadingBackground2.png'");
    }
    else
    {
        //将背景图放在中央
        background->setPosition(Vec2(MAINMENU_BACKGROUND_POSITION_X,
            MAINMENU_BACKGROUND_POSITION_Y));

        this->addChild(background, 10);
    }

    this->scheduleOnce(schedule_selector(GameLoadingScene2::changeScene), 3.5f); // 开启计时器！

    return true;
}

/****************************
* Name ：GameLoadingScene2::changeScene
* Summary ：进入菜单界面
* return ：无
****************************/
void GameLoadingScene2::changeScene(float dt)
{
    auto GS = GameScene::createScene();   // 转入GameScene
    Director::getInstance()->replaceScene(TransitionFade::create(1, GS));//GSL2已被释放
}
