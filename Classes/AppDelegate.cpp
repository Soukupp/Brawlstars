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
        glview = GLViewImpl::createWithRect("Brawlstars", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Brawlstars");
#endif

        //获取屏幕分辨率
        int screenWidth, screenHeight;
        screenWidth = GetSystemMetrics(SM_CXSCREEN);
        screenHeight = GetSystemMetrics(SM_CYSCREEN);

        glview->setFrameSize(screenWidth, screenHeight);
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
    /**
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
    /**/

    std::string str = UserDefault::getInstance()->getXMLFilePath();
    if (UserDefault::getInstance()->isXMLFileExist()) //是否存在
    {
        std::string path = UserDefault::getInstance()->getXMLFilePath();
        CCLOG("XML file is exist!");
        CCLOG("XML file path : %s", path.c_str());
    }
    else
    {
        CCLOG("XML file is not exist!");
    }

    do {
        if (!UserDefault::getInstance()->getIntegerForKey("_winTimes"))
            UserDefault::getInstance()->setIntegerForKey("_winTimes", 0);
        if (!UserDefault::getInstance()->getIntegerForKey("_gameTimes"))
            UserDefault::getInstance()->setIntegerForKey("_gameTimes", 0);
        if (!UserDefault::getInstance()->getIntegerForKey("_killNums"))
            UserDefault::getInstance()->setIntegerForKey("_killNums", 0);
        if (!UserDefault::getInstance()->getIntegerForKey("_cupNums"))
            UserDefault::getInstance()->setIntegerForKey("_cupNums", 0);
        if (!UserDefault::getInstance()->getIntegerForKey("selectedHero"))
            UserDefault::getInstance()->setIntegerForKey("selectedHero", 1);
        if (!UserDefault::getInstance()->getIntegerForKey("invincibleMode"))
            UserDefault::getInstance()->setIntegerForKey("invincibleMode", 0);
        UserDefault::getInstance()->setIntegerForKey("invincibleMode", 0);
        if (!UserDefault::getInstance()->getIntegerForKey("selectedMap"))
            UserDefault::getInstance()->setIntegerForKey("selectedMap", 0);
        if (!UserDefault::getInstance()->getIntegerForKey("selectedAINUmber"))
            UserDefault::getInstance()->setIntegerForKey("selectedAINUmber", 9);
        if (!UserDefault::getInstance()->getIntegerForKey("PlayerRank"))
            UserDefault::getInstance()->setIntegerForKey("PlayerRank", 10);
        if (!UserDefault::getInstance()->getIntegerForKey("HitNum"))
            UserDefault::getInstance()->setIntegerForKey("HitNum", 0);
        if (!UserDefault::getInstance()->getIntegerForKey("musicVolume"))
            UserDefault::getInstance()->setIntegerForKey("musicVolume", 50);
        if (!UserDefault::getInstance()->getBoolForKey("ifPlayMusic"))
            UserDefault::getInstance()->setBoolForKey("ifPlayMusic", true);
        if (!UserDefault::getInstance()->getBoolForKey("ifShowFPS"))
            UserDefault::getInstance()->setBoolForKey("ifShowFPS", false);
    } while (0);

    // turn on display FPS
    director->setDisplayStats(UserDefault::getInstance()->getBoolForKey("ifShowFPS"));

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 144);

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
