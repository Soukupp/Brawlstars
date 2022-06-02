//作者 ：李元特
//日期 : 2022-6-2

#include "InformationPopLayer.h"

InformationPopLayer::InformationPopLayer()
	:
	m__pMenu(NULL)
	, m_contentPadding(0)
	, m_contentPaddingTop(0)
	, m_callbackListener(NULL)
	, m_callback(NULL)
	, m__sfBackGround(NULL)
	, m__s9BackGround(NULL)
	, m__ltContentText(NULL)
	, m__ltTitle(NULL)
{

}

InformationPopLayer::~InformationPopLayer() 
{
	CC_SAFE_RELEASE(m__pMenu);
	CC_SAFE_RELEASE(m__sfBackGround);
	CC_SAFE_RELEASE(m__s9BackGround);
	CC_SAFE_RELEASE(m__ltContentText);
	CC_SAFE_RELEASE(m__ltTitle);
}

bool InformationPopLayer::init() 
{
	if (!LayerColor::init()) {
		return false;
	}

	Menu* menu = Menu::create();

	menu->setPosition(CCPointZero);

	setMenuButton(menu);

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(InformationPopLayer::onTouchBegan, this);

	listener->onTouchMoved = CC_CALLBACK_2(InformationPopLayer::onTouchMoved, this);

	listener->onTouchEnded = CC_CALLBACK_2(InformationPopLayer::onTouchEnded, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	setColor(Color3B::GRAY);   //设置弹出层的颜色

	setOpacity(128);  //设置弹出层的透明度

	return true;

}

bool InformationPopLayer::onTouchBegan(Touch* touch, Event* event) 
{
	return true;
}

void InformationPopLayer::onTouchMoved(Touch* touch, Event* event) 
{

}

void InformationPopLayer::onTouchEnded(Touch* touch, Event* event) 
{

}

InformationPopLayer* InformationPopLayer::create(const char* backgoundImage, Size dialogSize) 
{
	InformationPopLayer* layer = InformationPopLayer::create();  //创建弹出对话框，指定背景图和其大小

	//layer->setSpriteBackGround(Sprite::create(backgoundImage));

	layer->setSprite9BackGround(Scale9Sprite::create(backgoundImage));

	layer->m_dialogContentSize = dialogSize;

	return layer;

}

void InformationPopLayer::setTitle(const char* title, int fontsize /*=20*/) 
{
	LabelTTF* label = LabelTTF::create(title, "", fontsize);

	label->setColor(Color3B::RED);

	setLabelTitle(label);

}

void InformationPopLayer::setContentText(const char* text, int fontsize, int padding, int paddingTop) 
{
	LabelTTF* ltf = LabelTTF::create(text, "", fontsize);

	ltf->setColor(Color3B::BLUE);

	setLabelContentText(ltf);

	m_contentPadding = padding;

	m_contentPaddingTop = paddingTop;

}

void InformationPopLayer::setCallBackFunc(Ref* target, SEL_CallFuncN callfun) 
{
	m_callbackListener = target;

	m_callback = callfun;

}

bool InformationPopLayer::addButton(const char* normalImage, const char* selectedImage, const char* title, int tag) 
{

	Size winSize = Director::getInstance()->getWinSize();

	Point center_point = Point(winSize.width / 2, winSize.height / 2);

	auto menuImage = MenuItemImage::create(

		normalImage,

		selectedImage,

		CC_CALLBACK_1(InformationPopLayer::buttonCallBack, this));

	menuImage->setTag(tag);

	menuImage->setPosition(center_point);

	Size menuSize = menuImage->getContentSize();

	Label* labelttf = Label::createWithTTF(title, "fonts/arial.ttf", 15);

	labelttf->setColor(Color3B(Color3B::BLACK));

	labelttf->setPosition(Point(menuSize.width / 2, menuSize.height / 2));

	menuImage->addChild(labelttf);

	getMenuButton()->addChild(menuImage);

	return true;

}

void InformationPopLayer::buttonCallBack(Ref* pSender) {

	Node* node = dynamic_cast<Node*>(pSender);

	//log("[========PopAlertDialog:buttonCallBack=======]touch tag:%d",node->getTag());

	if (m_callback && m_callbackListener) {

		(m_callbackListener->*m_callback)(node);

	}

	this->removeFromParentAndCleanup(true);

}

void InformationPopLayer::onEnter() {

	log("InformationPopLayer onEnter");

	LayerColor::onEnter();

	Size winSize = Director::getInstance()->getWinSize();

	Point center = Point(winSize.width / 2, winSize.height / 2);

	//Sprite* background=getSpriteBackGround();

	Scale9Sprite* background = getSprite9BackGround();

	background->setContentSize(m_dialogContentSize);//指定对话框大小

	background->setPosition(Point(winSize.width / 2, winSize.height / 2));

	this->addChild(background, 0, 0);

	Action* popupActions = Sequence::create(ScaleTo::create(0.0, 0.0),

		ScaleTo::create(0.06, 1.05),

		ScaleTo::create(0.08, 0.95),

		ScaleTo::create(0.08, 1.0),

		CallFunc::create(CC_CALLBACK_0(InformationPopLayer::backgroundFinish, this))

		, NULL);

	background->runAction(popupActions);

}

void InformationPopLayer::backgroundFinish() {

	Size winSize = Director::getInstance()->getWinSize();

	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	this->addChild(getMenuButton());

	float btnWidth = m_dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);

	Vector<Node*> vector = getMenuButton()->getChildren();

	Ref* pObj = NULL;

	int i = 0;

	for (Node* pObj : vector) {

		Node* node = dynamic_cast<Node*>(pObj);

		node->setPosition(Point(winSize.width / 2 - m_dialogContentSize.width / 2 + btnWidth * (i + 1), winSize.height / 2 - m_dialogContentSize.height / 3));

		i++;

	}

	if (getLabelTitle()) {

		getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, m_dialogContentSize.height / 2 - 35.0f)));

		this->addChild(getLabelTitle());

	}

	if (getLabelContentText()) {

		CCLabelTTF* ltf = getLabelContentText();

		ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));

		ltf->setDimensions(CCSizeMake(m_dialogContentSize.width - m_contentPadding * 2, m_dialogContentSize.height - m_contentPaddingTop));

		ltf->setHorizontalAlignment(kCCTextAlignmentLeft);

		this->addChild(ltf);

	}

}

void InformationPopLayer::onExit() {

	log("PInformationPopLayer onExit");

	LayerColor::onExit();

}

////调用：
//
//MenuItemSprite* item1 = MenuItemSprite::create(btn_normal_sprite, btn_select_sprite, nullptr, CC_CALLBACK_1(InformationPopLayer::select_learn, this));
//
//
////select_learn方法：
//
//void InformationPopLayer::select_learn(Object* pSender) {
//
//	log("you had select this button");
//
//	InformationPopLayer* popup = InformationPopLayer::create("background01.png", Size(800, 250));
//
//	popup->setTitle("Message");
//
//	popup->setContentText("This is a test message!", 20, 50, 150);
//
//	popup->setCallBackFunc(this, callfuncN_selector(InformationPopLayer::popButtonCallback));
//
//	popup->addButton("btnreturn.png", "btnreturn.png", "OK", 0);
//
//	popup->addButton("btnreturn.png", "btnreturn.png", "Cancel", 1);
//
//	this->addChild(popup);
//
//}
//
//void  InformationPopLayer::popButtonCallback(Node* pNode) {
//
//	log("[==========]button call back.tag %d", pNode->getTag());
//
//	if (pNode->getTag() == 0) {
//
//		Director::getInstance()->end();
//
//	}
//
//	if (pNode->getTag() == 1) {
//
//		//pNode->getParent()->removeFromParent();
//
//		pNode->removeFromParent();
//
//	}
//
//}