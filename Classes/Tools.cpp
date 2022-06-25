//作者：王鹏
//日期：2022-6-25
//实现：工具集

#include "Tools.h"

/****************************
* Name ：problemLoading
* Summary ：错误打印
* return ：
****************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

/****************************
* Name ：Tools::getUserInt
* Summary ：获取用户int型数据
* return ：用户int型数据
****************************/
int Tools::getUserInt(CCH* name)
{
	return UserDefault::getInstance()->getIntegerForKey(name);
}

/****************************
* Name ：Tools::setUserInt
* Summary ：设置用户int型数据
* return ：无
****************************/
void Tools::setUserInt(CCH* name, int num)
{
	UserDefault::getInstance()->setIntegerForKey(name, num);
}

std::string Tools::GBKToUTF8(const std::string& strGBK)
{
    std::string strOutUTF8 = "";
    WCHAR* str1;
    int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    str1 = new WCHAR[n];
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char* str2 = new char[n];
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    strOutUTF8 = str2;
    delete[]str1;
    str1 = NULL;
    delete[]str2;
    str2 = NULL;
    return strOutUTF8;
}

const char* Tools::strid(CCDictionary* pDict, const std::string& key)
{
    return ((String*)pDict->objectForKey(key))->getCString();
}

Dictionary* Tools::initDict()
{
    Dictionary* pDict;
    switch (Tools::getUserInt("language"))
    {
        case enumEnglish:
            pDict = Dictionary::createWithContentsOfFile("language/English.xml");
            log("English xml loaded");
            break;
        case enumChinese:
            pDict = Dictionary::createWithContentsOfFile("language/Chinese.xml");
            log("Chinese xml loaded");
            break;
        default:
            log("no language xml loaded");
            break;
    }
    if (pDict == NULL)
    {
        log("nullptr language xml loaded");
    }
    return pDict;
}