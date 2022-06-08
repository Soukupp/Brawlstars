//作者 ：李元特
//日期 : 2022-6-2


#ifndef _INFORMATION_POP_LAYER_H_
#define _INFORMATION_POP_LAYER_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;


class InformationPopLayer : public cocos2d::LayerColor
{
public:
	InformationPopLayer::InformationPopLayer();

	InformationPopLayer::~InformationPopLayer();

	virtual bool init();

	CREATE_FUNC(InformationPopLayer);

	static InformationPopLayer* create(const char* backgroudImage, Size dialogSize, int opacity);

	bool onTouchBegan(Touch* touch, Event* event);

	void setTitle(const char* title, const char* fontstyle, int font);
	// 设置标题

	void setContentText(const char* text, const char* fontstyle, int font, int padding, int paddingTop);
	// 弹窗内容

	void setCallBackFunc(Ref* target, SEL_CallFuncN callfun);

	bool createButton(const char* normalImage, const char* selectedImage);
	// 添加按钮

	virtual void onEnter();

	virtual void onExit();

	void backgroundFinish();

private:

	void buttonCallBack(Ref* pSender);
	// 按钮回调函数

	int _contentPadding;
	int _contentPaddingTop;

	Size _dialogContentSize; //对话框大小

	Ref* _callbackListener;

	SEL_CallFuncN _callback;

	// 安全释放
	CC_SYNTHESIZE_RETAIN(Menu*, _pMenu, MenuButton);

	CC_SYNTHESIZE_RETAIN(Sprite*, _sfBackGround, SpriteBackGround);

	CC_SYNTHESIZE_RETAIN(LabelTTF*, _ltTitle, LabelTitle);

	CC_SYNTHESIZE_RETAIN(LabelTTF*, _ltContentText, LabelContentText);

};


#endif