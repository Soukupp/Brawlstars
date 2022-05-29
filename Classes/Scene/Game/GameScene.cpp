//���� : ��Ԫ��
//���� : 2022-5-18

//�޸� : ����
//���� : 2022-5-20
//�������Sprite���滻ΪPlayer�� 

#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/****************************
* Name ��GameScene::createScene
* Summary ������������ʵ��layer
* return ��������ָ��
****************************/
Scene* GameScene::createScene()
{
	auto GameScene = Scene::create();
	auto MapLayer = GameScene::create();
	GameScene->addChild(MapLayer);
	return GameScene;
}

/****************************
* Name ��problemLoading
* Summary �������ӡ
* return ��
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
* Name ��GameScene::init
* Summary ����Ϸ������ʼ��
* return ����ʼ���ɹ����
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

	/*=====================�����رհ�ť��ʼ======================*/
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
	}  // �رղ˵���Ҫ��Ϊ�̶�λ�ã��Ҵ˴��رղ˵���ʾ�����������棩

	/*=====================�������ð�ť��ʼ======================*/
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
    /*=====================�������ð�ť����====================*/

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

	//static bool SkillIsReady = true;    //�þ�̬��������ֹûCD��ʹ�ü���
	//if (SkillIsReady == false)
	//	return true;
	//{
	//	// �ͷż���
	//}
	//SkillIsReady = false;


	////��Mask����һ��˳ʱ�붯������Ȼ��������ԭʼ��
	//ProgressTimer* mypro = ProgressTimer::create(Sprite::createWithTexture(texture2));
	//mypro->setAnchorPoint(Point(0, 0));
	//mypro->setType(ProgressTimer::Type::RADIAL);
	//_Mask->addChild(mypro);

	////����������ֱ���Ƴ����ֲ�,���°ѵ�ͼ���ɫ
	//CallFunc* action_callback = CallFuncN::create([_Mask, node](Node* ent) {
	//	node->removeChild(_Mask, true);//�Ƴ�����
	//	SwitchGray(node, false);//�ָ���ͼԭʼɫ��
	//	SkillIsReady = true;//��λ��ʾCD���˿������ô˼���
	//	});

	//ActionInterval* action_progress_to = Sequence::create(
	//	ProgressTo::create(5, 100),//��3sʱ�������ȴ
	//	action_callback,
	//	NULL);
	////����
	//mypro->runAction(action_progress_to);




	





	GameSettingLayer->addChild(menu);
	
	this->addChild(GameSettingLayer, 1);


	auto MapLayer1 = MapLayer::create();
	this->addChild(MapLayer1, 0);

	return true;
}


/****************************
* Name ��GameScene::menuCloseCallback
* Summary ������GameOverScene
* return ����
****************************/
void GameScene::menuCloseCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	auto GOS = GameOverScene::createScene();
	Director::getInstance()->replaceScene(GOS);
}


/****************************
* Name ��GameScene::GameSettingsCallBack
* Summary ������GameSettingsScene
* return ����
****************************/
void GameScene::GameSettingsCallBack(cocos2d::Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/if_click_buttom_on_menu.mp3");
	auto GSS = GameSettingsScene::createScene();
	Director::getInstance()->pushScene(GSS);  // �˴���push�ķ�ʽ��������Ϸ����
}
