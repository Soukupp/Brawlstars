//作者 : 李元特
//日期 : 2022-5-18

//修改 : 王鹏
//日期 : 2022-5-20
//将人物从Sprite类替换为Player类 

#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/****************************
* Name ：GameScene::createScene
* Summary ：创建场景，实质layer
* return ：场景类指针
****************************/
Scene* GameScene::createScene()
{
	auto GameScene = Scene::create();
	auto MapLayer = GameScene::create();
	GameScene->addChild(MapLayer);
	return GameScene;
}

/****************************
* Name ：problemLoading
* Summary ：错误打印
* return ：
****************************/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//static void SwitchGray(Sprite* sp, bool isGray)
//{
//	GLchar* grayvsh =
//		"attribute vec4 a_position; \n \
//		attribute vec2 a_texCoord; \n \
//		attribute vec4 a_color; \n \
//		varying vec4 v_fragmentColor;\n \
//		varying vec2 v_texCoord;\n \
//		void main(void) \n \
//		{ \n \
//			gl_Position = CC_PMatrix * a_position;\n \
//			v_fragmentColor = a_color;\n \
//			v_texCoord = a_texCoord;\n \
//		}";
//	if (isGray)
//	{
//		GLchar* grayfsh =
//			"varying vec4 v_fragmentColor;\n \
//				varying vec2 v_texCoord;\n \
//				void main()\n \
//				{\n \
//				vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);\n \
//				float gray = dot(v_orColor.rgb, vec3(0.299, 0.587, 0.114));\n \
//				gl_FragColor = vec4(gray, gray, gray, v_orColor.a);\n \
//				}";
//		GLProgram* pProgram = new GLProgram();
//		pProgram->initWithVertexShaderByteArray(grayvsh, grayfsh);
//		sp->setShaderProgram(pProgram);
//		pProgram->release();
//		CHECK_GL_ERROR_DEBUG();
//	}
//	else {
//		GLProgram* pProgram = new GLProgram();
//		//pProgram->initWithFilenames("gray.vsh", "color.fsh");
//		pProgram->initWithVertexShaderByteArray(grayvsh, ccPositionTextureColor_frag);
//		sp->setShaderProgram(pProgram);
//		pProgram->release();
//		CHECK_GL_ERROR_DEBUG();
//	}
//	sp->getShaderProgram()->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, kCCVertexAttribFlag_Position);
//	sp->getShaderProgram()->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, kCCVertexAttrib_Position);
//	sp->getShaderProgram()->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, kCCVertexAttrib_Color);
//	sp->getShaderProgram()->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, kCCVertexAttrib_TexCoords);
//	CHECK_GL_ERROR_DEBUG();
//	sp->getShaderProgram()->link();
//	CHECK_GL_ERROR_DEBUG();
//	sp->getShaderProgram()->updateUniforms();
//	CHECK_GL_ERROR_DEBUG();
//}

/****************************
* Name ：GameScene::init
* Summary ：游戏场景初始化
* return ：初始化成功与否
****************************/
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto GameSettingLayer = LayerColor::create();
	GameSettingLayer->changeWidthAndHeight(960, 720);

	/*=====================创建关闭按钮开始======================*/
	auto closeItem = MenuItemImage::create(
		"ui/CloseNormal.png",
		"ui/CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'ui/CloseNormal.png' and 'ui/CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}  // 关闭菜单需要改为固定位置（且此处关闭菜单表示跳到结束界面）

	/*=====================创建设置按钮开始======================*/
	auto SettingsItem = MenuItemImage::create(
		"ui/GameSettingsButton.png", "ui/GameSettingsButton.png",
		CC_CALLBACK_1(GameScene::GameSettingsCallBack, this));

	if (SettingsItem == nullptr ||
		SettingsItem->getContentSize().width <= 0 ||
		SettingsItem->getContentSize().height <= 0)
	{
		problemLoading("'ui/GameSettingsButton.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - 3 * SettingsItem->getContentSize().width / 2;
		float y = visibleSize.height - SettingsItem->getContentSize().height / 2;
		SettingsItem->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(closeItem, SettingsItem, NULL);
	menu->setPosition(Vec2::ZERO);
    /*=====================创建设置按钮结束====================*/

	auto SkillButton = SkillButton::create("ui/buttonForSkill.png", "ui/buttonShadow.png", 30);
	float x = origin.x + 1.5 * 40;
	float y = origin.y + 1.5 * 40;
	SkillButton->setPosition(Vec2(x, y));
	this->addChild(SkillButton, 100);

	//

	//auto Skill = Sprite::create("ui/buttonForSkill.png");
	//float x = origin.x + 1.5 * Skill->getContentSize().width / 2;
	//float y = origin.y + 1.5 * Skill->getContentSize().height / 2;
	//Skill->setPosition(Vec2(x, y));
	//this->addChild(Skill, 100);

	//static bool SkillIsReady = true;    //用静态变量，防止没CD就使用技能
	//if (SkillIsReady == false)
	//	return true;
	//{
	//	// 释放技能
	//}
	//SkillIsReady = false;


	////在Mask上造一个顺时针动画，当然纹理还是用原始的
	//ProgressTimer* mypro = ProgressTimer::create(Sprite::createWithTexture(texture2));
	//mypro->setAnchorPoint(Point(0, 0));
	//mypro->setType(ProgressTimer::Type::RADIAL);
	//_Mask->addChild(mypro);

	////动画结束后直接移除遮罩层,重新把地图变彩色
	//CallFunc* action_callback = CallFuncN::create([_Mask, node](Node* ent) {
	//	node->removeChild(_Mask, true);//移除遮罩
	//	SwitchGray(node, false);//恢复底图原始色调
	//	SkillIsReady = true;//置位表示CD好了可以再用此技能
	//	});

	//ActionInterval* action_progress_to = Sequence::create(
	//	ProgressTo::create(5, 100),//用3s时间完成冷却
	//	action_callback,
	//	NULL);
	////动画
	//mypro->runAction(action_progress_to);




	





	GameSettingLayer->addChild(menu);
	
	this->addChild(GameSettingLayer, 1);


	auto MapLayer1 = MapLayer::create();
	this->addChild(MapLayer1, 0);

	return true;
}


/****************************
* Name ：GameScene::menuCloseCallback
* Summary ：跳到GameOverScene
* return ：无
****************************/
void GameScene::menuCloseCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	auto GOS = GameOverScene::createScene();
	Director::getInstance()->replaceScene(GOS);
}


/****************************
* Name ：GameScene::GameSettingsCallBack
* Summary ：跳到GameSettingsScene
* return ：无
****************************/
void GameScene::GameSettingsCallBack(cocos2d::Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	auto GSS = GameSettingsScene::createScene();
	Director::getInstance()->pushScene(GSS);  // 此处用push的方式，保留游戏进度
}
