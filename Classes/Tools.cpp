//作者：王鹏
//日期：2022-6-25
//实现：工具集

#include "Tools.h"

/****************************
* Name ：problemLoading
* Summary ：错误打印
* return ：
****************************/
void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

void Tools::getDirtFromKey(std::map<cocos2d::EventKeyboard::KeyCode, bool>& keyMap, int& direction)
{
    if ((keyMap[EventKeyboard::KeyCode::KEY_D] || keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
        && (keyMap[EventKeyboard::KeyCode::KEY_W] || keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW]))
    {
        direction = eRU;
    }
    else if ((keyMap[EventKeyboard::KeyCode::KEY_D] || keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
        && (keyMap[EventKeyboard::KeyCode::KEY_S] || keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW]))
    {
        direction = eRD;
    }
    else if ((keyMap[EventKeyboard::KeyCode::KEY_A] || keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
        && (keyMap[EventKeyboard::KeyCode::KEY_W] || keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW]))
    {
        direction = eLU;
    }
    else if ((keyMap[EventKeyboard::KeyCode::KEY_A] || keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
        && (keyMap[EventKeyboard::KeyCode::KEY_S] || keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW]))
    {
        direction = eLD;
    }
    else if (keyMap[EventKeyboard::KeyCode::KEY_D] || keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
    {
        direction = eR;
    }
    else if (keyMap[EventKeyboard::KeyCode::KEY_A] || keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
    {
        direction = eL;
    }
    else if (keyMap[EventKeyboard::KeyCode::KEY_W] || keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW])
    {
        direction = eU;
    }
    else if (keyMap[EventKeyboard::KeyCode::KEY_S] || keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW])
    {
        direction = eD;
    }
    else {
        direction = eST;
    }
}

void Tools::getDirtForAI(Character& character, const cocos2d::Sprite* _SafeArea)
{
    if (!_SafeArea->boundingBox().containsPoint(Vec2(character._player->getPosition())))//不在安全区
    {
        ++character._searchTimes;
        if (character._searchTimes <= 100)//寻路少于一定数量则进行逃离方向选择逻辑
        {
            if (!character._backDirectChanged)//且没有掉头
            {//那么掉头
                if (character._direct <= 1)//左右
                {
                    character._direct = 1 - character._direct;
                }
                else//上下
                {
                    character._direct = 5 - character._direct;
                }
                character._backDirectChanged = true;
            }
            //否则维持原方向
        }
        else//达到寻路上限还没逃离则开始随机选方向逃出
        {
            character._backDirectChanged = false;//参数重置
            int tempDirect = rand() % 60;
            if (tempDirect <= 7)//除去原本的方向，每一帧有3/60的几率转向
            {//这样是为了保证ai基本可以走一段路 而不是原地不停转向
                character._direct = tempDirect;//每一帧小概率获取新方向或者大概率维持原方向
            }
        }
    }
    else//在安全区
    {//正常选方向
        character._searchTimes = 0;//参数重置
        character._backDirectChanged = false;//参数重置
        int tempDirect = rand() % 120;
        if (tempDirect <= 7)//除去原本的方向，每一帧有3/60的几率转向
        {//这样是为了保证ai基本可以走一段路 而不是原地不停转向
            character._direct = tempDirect;//每一帧小概率获取新方向或者大概率维持原方向
        }
    }
}

void Tools::getNextPosByDirt(Vec2& playerPos, Character& character)
{
    switch (character._direct)
    {
        case eR:
            playerPos.x += 4;
            character._player->_panel.setPlayerState(MOVING);
            character._player->runFlipxWithWeapon(false, character._weapon);
            break;
        case eL:
            playerPos.x -= 4;
            character._player->_panel.setPlayerState(MOVING);
            character._player->runFlipxWithWeapon(true, character._weapon);
            break;
        case eU:
            playerPos.y += 4;
            character._player->_panel.setPlayerState(MOVING);
            break;
        case eD:
            playerPos.y -= 4;
            character._player->_panel.setPlayerState(MOVING);
            break;
        case eRU:
            playerPos.x += 2.828f;
            playerPos.y += 2.828f;
            character._player->_panel.setPlayerState(MOVING);
            character._player->runFlipxWithWeapon(false, character._weapon);
            break;
        case eRD:
            playerPos.x += 2.828f;
            playerPos.y -= 2.828f;
            character._player->_panel.setPlayerState(MOVING);
            character._player->runFlipxWithWeapon(false, character._weapon);
            break;
        case eLU:
            playerPos.x -= 2.828f;
            playerPos.y += 2.828f;
            character._player->_panel.setPlayerState(MOVING);
            character._player->runFlipxWithWeapon(true, character._weapon);
            break;
        case eLD:
            playerPos.x -= 2.828f;
            playerPos.y -= 2.828f;
            character._player->_panel.setPlayerState(MOVING);
            character._player->runFlipxWithWeapon(true, character._weapon);
            break;
        default:
            break;
    }
}

void Tools::initUserInt(CCH* key, const int num)
{
    if (!Tools::getUserInt(key))
        Tools::setUserInt(key, num);
}
void Tools::initUserBool(CCH* key, const bool num)
{
    if (!Tools::getUserBool(key))
        Tools::setUserBool(key, num);
}

/****************************
* Name ：Tools::getUserInt
* Summary ：获取用户int型数据
* return ：用户int型数据
****************************/
int Tools::getUserInt(CCH* key)
{
	return UserDefault::getInstance()->getIntegerForKey(key);
}

/****************************
* Name ：Tools::setUserInt
* Summary ：设置用户int型数据
* return ：无
****************************/
void Tools::setUserInt(CCH* key, const int num)
{
    UserDefault::getInstance()->setIntegerForKey(key, num);
}

/****************************
* Name ：Tools::getUserBool
* Summary ：获取用户bool型数据
* return ：用户bool型数据
****************************/
int Tools::getUserBool(CCH* key)
{
    return UserDefault::getInstance()->getBoolForKey(key);
}

/****************************
* Name ：Tools::setUserBool
* Summary ：设置用户bool型数据
* return ：无
****************************/
void Tools::setUserBool(CCH* key, const int num)
{
    UserDefault::getInstance()->setBoolForKey(key, num);
}

std::string Tools::GBKToUTF8(CSTR& strGBK)
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

const char* Tools::cbyid(Dictionary* pDict, CSTR& key)
{
    const char* charById = ((String*)pDict->objectForKey(key))->getCString();
    if (charById == nullptr)
    {
        printf("cbyid error when load key : %s\n", key.c_str());
    }
    return charById;
}

const char* Tools::cbyid(CSTR& key)
{
    auto pDict = Tools::initDict();
    return ((String*)pDict->objectForKey(key))->getCString();
}

std::string Tools::strbyid(Dictionary* pDict, CSTR& key)
{
    auto b = ((String*)pDict->objectForKey(key))->getCString();
    std::string a = b;
    return a;
}

Dictionary* Tools::initDict()
{
    Dictionary* pDict = NULL;
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

void Tools::emptyCallback(cocos2d::Ref* pSender)
{

}

void Tools::gameoverDataSave()
{
    if (Tools::getUserInt("_numOfPlayer") == 1)
    {
        Tools::setUserInt("_winTimes", 1 + Tools::getUserInt("_winTimes"));
    }
    Tools::setUserInt("_gameTimes", 1 + Tools::getUserInt("_gameTimes"));
    Tools::setUserInt("_killNums", Tools::getUserInt("_hitNum") + Tools::getUserInt("_killNums"));
    if (Tools::getUserInt("_numOfPlayer") <= 5)
    {
        Tools::setUserInt("_cupNums", 6 + Tools::getUserInt("_numOfPlayer") + Tools::getUserInt("_cupNums"));
    }
}

void Tools::playEffect(CCH* filePath, bool loop, float pitch, float pan, float gain)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(filePath, loop, pitch, pan, gain);
}

void Tools::setEffectsVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
}

void Tools::setEffectsVolume(CCH* volumeKey)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(
        static_cast<float>(Tools::getUserInt(volumeKey)) / 100);
}

void Tools::playBackgroundMusic(CCH* filePath, bool loop)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath, loop);
}

void Tools::setBackgroundMusicVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

void Tools::setBackgroundMusicVolume(CCH* volumeKey)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(
        static_cast<float>(Tools::getUserInt(volumeKey)) / 100);
}

void Tools::preloadEffect(CCH* filePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(filePath);
}
void Tools::preloadBackgroundMusic(CCH* filePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(filePath);
}

bool Tools::isBackgroundMusicPlaying()
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}

void Tools::pauseBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void Tools::resumeBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}