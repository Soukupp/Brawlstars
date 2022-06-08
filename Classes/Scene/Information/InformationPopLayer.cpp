//���� ����Ԫ��
//���� : 2022-6-2

#include "InformationPopLayer.h"


/****************************
* Name ��InformationPopLayer::InformationPopLayer
* Summary �����캯����ʼ��
* return ��
****************************/
InformationPopLayer::InformationPopLayer()
	:
	_pMenu(NULL)
	, _contentPadding(0)
	, _contentPaddingTop(0)
	, _callbackListener(NULL)
	, _callback(NULL)
	, _sfBackGround(NULL)
	, _ltContentText(NULL)
	, _ltTitle(NULL)
{

}


/****************************
* Name ��InformationPopLayer::~InformationPopLayer
* Summary ������������ȫ�ͷ�
* return ��
****************************/
InformationPopLayer::~InformationPopLayer()
{
	CC_SAFE_RELEASE(_pMenu);
	CC_SAFE_RELEASE(_sfBackGround);
	CC_SAFE_RELEASE(_ltContentText);
	CC_SAFE_RELEASE(_ltTitle);
}


/****************************
* Name ��InformationPopLayer::init
* Summary ����ʼ��
* return ���Ƿ��ʼ���ɹ�
****************************/
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

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;

}


/****************************
* Name ��InformationPopLayer::onTouchBegan
* Summary ���ж�����touch
* return �����޴���
****************************/
bool InformationPopLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}


/****************************
* Name ��InformationPopLayer::create
* Summary �����쵯������
* return ��InformationPopLayer*
****************************/
InformationPopLayer* InformationPopLayer::create(const char* backgoundImage, Size dialogSize, int opacity)
{
	InformationPopLayer* layer = InformationPopLayer::create();  //���������Ի���ָ������ͼ�����С
	auto InformationBackground = Sprite::create(backgoundImage);
	InformationBackground->setOpacity(opacity);
	layer->setSpriteBackGround(InformationBackground);
	layer->_dialogContentSize = dialogSize;

	return layer;
}


/****************************
* Name ��InformationPopLayer::setTitle
* Summary �����õ�������
* return ����
****************************/
void InformationPopLayer::setTitle(const char* title, const char* fontstyle, int font)
{
	LabelTTF* TitleLabel = LabelTTF::create(title, fontstyle, font);
	TitleLabel->setColor(Color3B::WHITE); // Ĭ�ϰ�ɫ
	this->setLabelTitle(TitleLabel);
}


/****************************
* Name ��InformationPopLayer::setContentText
* Summary �����õ�������
* return ����
****************************/
void InformationPopLayer::setContentText(const char* text, const char* fontstyle, int font, int padding, int paddingTop)
{
	LabelTTF* ContentTextLabel = LabelTTF::create(text, fontstyle, font);
	ContentTextLabel->setColor(Color3B::BLUE);  // Ĭ����ɫ
	this->setLabelContentText(ContentTextLabel);

	_contentPadding = padding;
	_contentPaddingTop = paddingTop;
	// ����һ���ı��������������õ�
}


/****************************
* Name ��InformationPopLayer::setCallBackFunc
* Summary ������ص�״̬
* return ����
****************************/
void InformationPopLayer::setCallBackFunc(Ref* target, SEL_CallFuncN callfun)
{
	_callbackListener = target;
	_callback = callfun;

}


/****************************
* Name ��InformationPopLayer::createButton
* Summary �����Ӱ�ť
* return ����
****************************/
bool InformationPopLayer::createButton(const char* Image, const char* ImageSelected)
{

	Size winSize = Director::getInstance()->getWinSize();
	Vec2 center_point = Vec2(winSize.width / 2, winSize.height / 2);

	auto menuImage = MenuItemImage::create(Image, ImageSelected,
		CC_CALLBACK_1(InformationPopLayer::buttonCallBack, this));
	menuImage->setPosition(center_point);

	Size menuSize = menuImage->getContentSize();

	getMenuButton()->addChild(menuImage);

	return true;
}


/****************************
* Name ��InformationPopLayer::buttonCallBack
* Summary ����ť�ص�
* return ����
****************************/
void InformationPopLayer::buttonCallBack(Ref* pSender) {

	Node* node = dynamic_cast<Node*>(pSender);

	if (_callback && _callbackListener)
	{
		(_callbackListener->*_callback)(node);
	}

	this->removeFromParentAndCleanup(true);
}


/****************************
* Name ��InformationPopLayer::onEnter
* Summary ��������������
* return ����
****************************/
void InformationPopLayer::onEnter() {

	log("InformationPopLayer onEnter");

	LayerColor::onEnter();

	Size winSize = Director::getInstance()->getWinSize();
	Point center = Point(winSize.width / 2, winSize.height / 2);

	Sprite* ButtonBackground = getSpriteBackGround();

	ButtonBackground->setContentSize(_dialogContentSize);//ָ���Ի����С
	ButtonBackground->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(ButtonBackground, 0);

	Action* popupActions = Sequence::create(
		ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.1f, 0.8f),
		ScaleTo::create(0.1f, 1.2f), ScaleTo::create(0.1f, 1.1f),
		CallFunc::create(CC_CALLBACK_0(InformationPopLayer::backgroundFinish, this))
		, NULL);   // ����Ч��
	ButtonBackground->runAction(popupActions);

}

/****************************
* Name ��InformationPopLayer::backgroundFinish
* Summary ����������
* return ����
****************************/
void InformationPopLayer::backgroundFinish() {

	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	getMenuButton()->setPosition(winSize.width / 3, winSize.height / 2);
	this->addChild(getMenuButton());

	float btnWidth = _dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);
	Vector<Node*> vector = getMenuButton()->getChildren();
	Ref* pObj = NULL;
	int i = 0;

	for (Node* pObj : vector)
	{
		Node* node = dynamic_cast<Node*>(pObj);
		node->setPosition(Point(winSize.width / 2 - _dialogContentSize.width / 2
			+ btnWidth * (i + 1), winSize.height / 2 - _dialogContentSize.height / 3));
		i++;
	}

	if (getLabelTitle())
	{
		// Titleλ��
		getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, _dialogContentSize.height / 2 - 35.0f)));
		this->addChild(getLabelTitle());
	}

	if (getLabelContentText())
	{
		CCLabelTTF* ContentTextLabel = getLabelContentText();  // ContentTextλ��
		ContentTextLabel->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		ContentTextLabel->setDimensions(CCSizeMake(_dialogContentSize.width - _contentPadding * 2, _dialogContentSize.height - _contentPaddingTop));
		ContentTextLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		this->addChild(ContentTextLabel);
	}

}


/****************************
* Name ��InformationPopLayer::onExit
* Summary ���˳�
* return ����
****************************/
void InformationPopLayer::onExit() {

	log("InformationPopLayer onExit");
	LayerColor::onExit();
}