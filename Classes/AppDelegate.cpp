 //修改 : 李元特
 //日期 : 2022-5-18

#include "AppDelegate.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(960, 720);
static cocos2d::Size smallResolutionSize = cocos2d::Size(960, 720);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1920, 1080);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Brawlstars", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height), 1.0f, true);
#else
        glview = GLViewImpl::create("Brawlstars");
#endif

        //获取屏幕分辨率
        int screenWidth, screenHeight;
        screenWidth = GetSystemMetrics(SM_CXSCREEN);
        screenHeight = GetSystemMetrics(SM_CYSCREEN);

        glview->setFrameSize(screenWidth * 0.8f, screenHeight * 0.8f);
        director->setOpenGLView(glview);

        //获取窗口大小
        int windowWidth, windowHeight;
        tagRECT rect;
        ::GetWindowRect(glview->getWin32Window(), &rect);
        windowWidth = rect.right - rect.left;
        windowHeight = rect.bottom - rect.top;

        //移动窗口并重绘
        ::MoveWindow(glview->getWin32Window(), (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2, windowWidth, windowHeight, TRUE);
    }

    // Set the design resolution
    //glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
    //glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);

    if (UserDefault::getInstance()->isXMLFileExist()) //是否存在
    {
        std::string path = UserDefault::getInstance()->getXMLFilePath();
        CCLOG("XML file is exist!");
        CCLOG("XML file path : %s", path.c_str());

        do {
            Tools::initUserInt("_winTimes", 0);
            Tools::initUserInt("_gameTimes", 0);
            Tools::initUserInt("_killNums", 0);
            Tools::initUserInt("_cupNums", 0);
            Tools::initUserInt("selectedHero", 1);
            Tools::initUserInt("invincibleMode", 0);
            Tools::setUserInt("invincibleMode", 0);
            Tools::initUserInt("selectedMap", 0);
            Tools::initUserInt("selectedAINUmber", 9);
            Tools::initUserInt("PlayerRank", 10);
            Tools::initUserInt("HitNum", 0);
            Tools::initUserInt("musicVolume", 50);
            Tools::initUserInt("language", enumEnglish);
            Tools::initUserBool("ifPlayMusic", true);
            Tools::initUserBool("ifShowFPS", false);
        } while (0);
    }
    else
    {
        CCLOG("XML file is not exist!");
        exit(0);
    }

    // turn on display FPS
    director->setDisplayStats(Tools::getUserBool("ifShowFPS"));

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 240);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto LS = LoadingScene::createScene();

    // run
    director->runWithScene(LS);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // 暂停音乐（SimpleAudioEngine）
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //attached


#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // 恢复音乐（SimpleAudioEngine）
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();//attached



#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
