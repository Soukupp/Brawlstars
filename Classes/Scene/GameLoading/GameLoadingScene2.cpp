//���� : ��Ԫ��
//���� : 2022-6-10

#include "GameLoadingScene2.h"

USING_NS_CC;

/****************************
* Name ��GameLoadingScene2::createScene
* Summary ����������
* return ��������ָ��
****************************/
Scene* GameLoadingScene2::createScene()
{
    return GameLoadingScene2::create();
}

/****************************
* Name ��problemLoading
* Summary �������ӡ
* return ��
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

/****************************
* Name ��GameLoadingScene2::init
* Summary �����˵���ʼ��
* return ����ʼ���ɹ����
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
        //������ͼ��������
        background->setPosition(Vec2(MAINMENU_BACKGROUND_POSITION_X,
            MAINMENU_BACKGROUND_POSITION_Y));

        this->addChild(background, 10);
    }

    this->scheduleOnce(schedule_selector(GameLoadingScene2::changeScene), 3.5f); // ������ʱ����

    return true;
}

/****************************
* Name ��GameLoadingScene2::changeScene
* Summary ������˵�����
* return ����
****************************/
void GameLoadingScene2::changeScene(float dt)
{
    auto GS = GameScene::createScene();   // ת��GameScene
    Director::getInstance()->replaceScene(TransitionFade::create(1, GS));//GSL2�ѱ��ͷ�
}
