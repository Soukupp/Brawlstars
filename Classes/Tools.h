//���ߣ�����
//���ڣ�2022-6-25
//ʵ�֣����߼�

#ifndef __TOOLS__
#define __TOOLS__

#include "cocos2d.h"

using namespace cocos2d;

enum enumLanguage {               //����״̬��ö��
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
	static std::string GBKToUTF8(const std::string& strGBK);
	static const char* strid(CCDictionary* pDict, const std::string& key);
	static Dictionary* initDict();
};
#endif