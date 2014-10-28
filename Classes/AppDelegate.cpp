#include "AppDelegate.h"
#include "HelloWorldScene.h"
//����ͳ��ͷ
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MobClickCpp.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
		glview->setFrameSize(960, 640);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
	//��Ļ����
	glview->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
    // run
    director->runWithScene(scene);
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // ����ͳ�Ƴ�ʼ��
    MOBCLICKCPP_START_WITH_APPKEY("542752bcfd98c578990126ac");	
#endif
    //��������ͳ�Ƶ���
    //umeng::MobClickCpp::setLogEnabled(true);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // ����ͳ����Ҫ
    umeng::MobClickCpp::applicationDidEnterBackground();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // ����ͳ����Ҫ
    umeng::MobClickCpp::applicationWillEnterForeground();
#endif
}
