//姓名：束赫
//创建日期：2022-5-18

#include "cocos2d.h"
#include "SettingScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;


static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SettingScene.cpp\n");
}


Scene* SettingScene::createScene()
{
	return SettingScene::create();
}

bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	textSetting();
	closeButtonSetting();
	spriteSetting();
	sliderSetting();

	return true;
}

void SettingScene::settingSceneCloseCallback(Ref* pSender)
{
	Director::getInstance()->popScene();          //返回MainMenuScene
}
/*name: spriteSetting
* function: 设置场景所需精灵*/
void SettingScene::spriteSetting()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* backgroundForSettingScene = Sprite::create("settingSceneBackground.png");

	if (backgroundForSettingScene == nullptr)
	{
		problemLoading("'mainmenuBackground.png'");
	}
	else
	{
		backgroundForSettingScene->setPosition(SETTING_SCENE_BG_X, SETTING_SCENE_BG_Y);
		addChild(backgroundForSettingScene, 0);
	}
}
/*name: closeButtonSetting
  function: 关闭按钮设置*/
void SettingScene::closeButtonSetting()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto closeButton = MenuItemImage::create("crossNormal.png", "crossSelected.png", CC_CALLBACK_1(SettingScene::settingSceneCloseCallback, this));
	if (closeButton == nullptr ||
		closeButton->getContentSize().width <= 0 ||
		closeButton->getContentSize().height <= 0)
	{
		log("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		log("'CloseNormal.png' and 'CloseSelected.png'");
		closeButton->setPosition(SETTING_SCENE_CLOSE_BUTTON_X, SETTING_SCENE_CLOSE_BUTTON_Y);
	}
	closeButton->setScale(0.5f);

	auto closeMenu = Menu::create(closeButton, NULL);

	closeMenu->setPosition(Vec2::ZERO);
	this->addChild(closeMenu, 1);
}
/*name: textSettinng
  function: 文本框设置*/
void SettingScene::textSetting()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto musicSettingTitle = Label::createWithTTF("Music Setting", "fonts/segoepr.ttf", 27);

	if (musicSettingTitle == nullptr)
	{
		problemLoading("fonts/segoepr.ttf");
	}
	else
	{
		musicSettingTitle->setPosition(SETTING_SCENE_MUSIC_TITLE_X, SETTING_SCENE_MUSIC_TITLE_Y);
		const Color4B gameNameLabelColor(MAINMENU_TEXT_RGB_COLOR, 255);

		musicSettingTitle->setTextColor(gameNameLabelColor);

		this->addChild(musicSettingTitle, 1);
	}

}
/*name: sliderSetting
  function: 设置滑块*/
void SettingScene::sliderSetting()
{   
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_displayedPrecentage = Text::create("0", "fonts/segoepr.ttf", 27);          //_displayedPrecentage 用于显示滑块拖动后所占比例
	_displayedPrecentage->setPosition(Vec2(SETTING_SCENE_SLIDER_X, SETTING_SCENE_SLIDER_Y * 0.5));
	auto musicSlider = Slider::create(); 

	 musicVolume = UserDefault::getInstance()->getFloatForKey("musicVolume");   //musicVolume 用于记录音量大小（百分制）
	musicVolume = 50.0f;                                                        //定义初始值为50
	_displayedPrecentage->setString(StringUtils::format("Percent %f", musicVolume));
	musicSlider->setPercent(musicVolume);

	musicSlider->loadBarTexture("progressFrame.png");
	musicSlider->loadSlidBallTextures("","","");
	musicSlider->loadProgressBarTexture("progressblock.png");
	musicSlider->setPosition(Vec2(SETTING_SCENE_SLIDER_X, SETTING_SCENE_SLIDER_Y));
	musicSlider->addEventListener(CC_CALLBACK_2(SettingScene::sliderEvent, this));
	musicSlider->setScale(0.5);


	this->addChild(_displayedPrecentage);
	this->addChild(musicSlider);  
}
/*name: sliderEvent
  function: 监控滑块动作并想要实现音量调节*/
void SettingScene::sliderEvent(Ref* pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int percentVolume = slider->getPercent();


		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percentVolume)/ 100); 
		                            //实在调不了音量，烂尾了，~~~~~~~~~~~~~~~~~~~~~~~~这个函数要自己实现，先烂尾了
		                            //需要用是sliderEvent中进行修改
		
		UserDefault::getInstance()->setFloatForKey("musicVolume", percentVolume);

		_displayedPrecentage->setString(StringUtils::format("Percent %d", percentVolume));   //显示所占百分比

	}
}

