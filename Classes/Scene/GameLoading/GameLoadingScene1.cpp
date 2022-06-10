//���� : ��Ԫ��
//���� : 2022-6-10

#include "GameLoadingScene1.h"

USING_NS_CC;


/****************************
* Name ��GameLoadingScene1::createScene
* Summary ����������
* return ��������ָ��
****************************/
Scene* GameLoadingScene1::createScene() 
{
    return GameLoadingScene1::create();
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
* Name ��GameLoadingScene1::init
* Summary �����˵���ʼ��
* return ����ʼ���ɹ����
****************************/
bool GameLoadingScene1::init() {
    if (!Scene::init()) 
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("background/GameLoadingBackground1.png");
    if (background == nullptr)
    {
        problemLoading("'background/GameLoadingBackground1.png'");
    }
    else
    {
        //������ͼ��������
        background->setPosition(Vec2(MAINMENU_BACKGROUND_POSITION_X,
            MAINMENU_BACKGROUND_POSITION_Y));

        this->addChild(background, 10);
    }

    this->scheduleOnce(schedule_selector(GameLoadingScene1::changeScene), 3.5f); // ������ʱ����

    return true;
}


/****************************
* Name ��GameLoadingScene1::changeScene
* Summary ������˵�����
* return ����
****************************/
void GameLoadingScene1::changeScene(float dt)
{
    auto GLS2 = GameLoadingScene2::createScene();   // ת��GameLoadingScene2
    Director::getInstance()->replaceScene(TransitionFade::create(1, GLS2));//GSL1�ѱ��ͷ�
}
