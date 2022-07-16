//作者：王鹏
//日期：2022-6-25
//实现：工具集

#ifndef __TOOLS__
#define __TOOLS__

#include "cocos2d.h"
#include "Entity/Character.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum enumLanguage {               //人物状态的枚举
    enumEnglish,
	enumChinese
};

enum enumDirection {
	eR,
	eL,
	eU,
	eD,
	eRU,
	eRD,
	eLU,
	eLD,
	eST
};

void problemLoading(const char* filename);

typedef const std::string CSTR;
typedef const char CCH;
typedef const cocos2d::ccMenuCallback CCOCCMCB;
typedef cocos2d::MenuItemImage COMII;

class Tools
{
public:
	static void getDirtFromKey(std::map<cocos2d::EventKeyboard::KeyCode, bool>& keyMap, int& direction);
	static void getDirtForAI(Character& character, const cocos2d::Sprite* _SafeArea);
	static void getNextPosByDirt(Vec2& playerPos, Character& character);

	static void initUserInt(CCH* key, const int num = 0);
	static void initUserBool(CCH* key, const bool num = false);

	static int getUserInt(CCH* key);
	static void setUserInt(CCH* key, const int num);
	static int getUserBool(CCH* key);
	static void setUserBool(CCH* key, const int num);

	static std::string GBKToUTF8(CSTR& strGBK);
	static const char* cbyid(Dictionary* pDict, CSTR& key);
	static const char* cbyid(CSTR& key);
	static std::string strbyid(Dictionary* pDict, CSTR& key);
	static Dictionary* initDict();
	static void emptyCallback(cocos2d::Ref* pSender);
	static void gameoverDataSave();

	static void playEffect(CCH* filePath, bool loop = false, float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);
	static void setEffectsVolume(float volume);
	static void setEffectsVolume(CCH* volumeKey);

	static void playBackgroundMusic(CCH* filePath, bool loop = false);
	static void setBackgroundMusicVolume(float volume);
	static void setBackgroundMusicVolume(CCH* volumeKey);

	static void preloadEffect(CCH* filePath);
	static void preloadBackgroundMusic(CCH* filePath);

	static bool isBackgroundMusicPlaying();

	static void pauseBackgroundMusic();
	static void resumeBackgroundMusic();
};
#endif