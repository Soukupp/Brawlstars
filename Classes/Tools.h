//作者：王鹏
//日期：2022-6-25
//实现：工具集

#ifndef __TOOLS__
#define __TOOLS__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum enumLanguage {               //人物状态的枚举
    enumEnglish,
	enumChinese
};

typedef const std::string CSTR;
typedef const char CCH;
typedef const cocos2d::ccMenuCallback CCOCCMCB;
typedef cocos2d::MenuItemImage COMII;

class Tools
{
public:
	static int getUserInt(CCH* name);
	static void setUserInt(CCH* name, int num);
	static std::string GBKToUTF8(CSTR& strGBK);
	static const char* cbyid(Dictionary* pDict, CSTR& key);
	static const char* cbyid(const std::string& key);
	static std::string strbyid(Dictionary* pDict, CSTR& key);
	static Dictionary* initDict();
	static void emptyCallback(cocos2d::Ref* pSender);
	static void gameoverDataSave();
	static void playEffect(CCH* filePath, bool loop = false, float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);
	static void setEffectsVolume(float volume);
	static void setEffectsVolume(CCH* volume);
};
#endif