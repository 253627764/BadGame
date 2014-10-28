#include "HelloWorldScene.h"
#include "GameScene.h"
#include "ConfigData.h"
#include "AboutScene.h"
#include "LevelScene.h"
#include "JINTools.h"

// ������ص�ͷ�ļ�
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//����ͳ��ͷ
#include "MobClickCpp.h"
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
// ʹ����������ռ�
USING_NS_UM_SOCIAL;
#endif

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
/*
 * ����ص�, �ûص�����ĳ����ĳ�Ա������ ����һ����ͨ�ĺ���, ����ʹ�òο�HelloWorldScene������
* @param platform Ҫ������Ŀ��ƽ̨
 * @param stCode ������, 200�������ɹ�, 100����ʼ����
 * @param errorMsg ����ʧ��ʱ�Ĵ�����Ϣ,androidƽ̨û�д�����Ϣ
 */
void shareCallback(int platform, int stCode, string& errorMsg)
{
    if ( stCode == 100 ) 
    {
        CCLog("#### HelloWorld startshare");
    }
    else if ( stCode == 200 ) 
    {
        CCLog("#### HelloWorld finishshare");
    }
    else 
    {
        CCLog("#### HelloWorld erroshare");
    }

    CCLog("platform num is : %d.", platform);
}
#endif

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

	return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(0,255,255,255)) )
    {
        return false;
    }
	Size size = Size(960, 640);
	//����
	Sprite* background = Sprite::create("UI/START/background.png");
	background->setPosition(size.width/2, size.height/2);
	this->addChild(background);
	//������
	Sprite* left = Sprite::create("UI/START/START_UI_DOWN_0004_LeftFoot.png");
	left->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	left->setPosition(0, 0);
	this->addChild(left);

	float leftFootWeight = left->getContentSize().width;
	float leftFootHeight = left->getContentSize().height;
	//LOGO
	Sprite* logo = Sprite::create("UI/START/START_UI_UP_0005_BAD-GAME.png");
	logo->setPosition((size.width - leftFootWeight) / 2 + leftFootWeight, CD_FLOAT("start_scene_logo_y"));
	this->addChild(logo);
	//�汾��
	TTFConfig ttfConfig("fonts/font.ttf", 16);
	auto number = Label::createWithTTF(ttfConfig, CD_STRING("number"));
	number->setTextColor(Color4B(0, 0, 0, 150));
	number->setPosition(size.width - 460, 20);
	this->addChild(number);

	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	this->addChild(menu);
	//���ð�ť
	MenuItemImage* buttonSetting = MenuItemImage::create("UI/START/START_UI_UP_0000_setting.png", "UI/START/START_UI_DOWN_0000_setting.png", "UI/START_UI_DOWN_0000_setting.png", CC_CALLBACK_1(HelloWorld::settingCallBack, this));
	buttonSetting->setPosition(leftFootWeight / 2, CD_FLOAT("start_scene_setting_button_y"));
	menu->addChild(buttonSetting);
	//���ڰ�ť
	MenuItemImage* buttonAbout = MenuItemImage::create("UI/START/START_UI_UP_0003__.png", "UI/START/START_UI_DOWN_0003__.png", "UI/START_UI_UP_0003__.png", CC_CALLBACK_1(HelloWorld::aboutCallBack, this));
	buttonAbout->setPosition(leftFootWeight / 2, CD_FLOAT("start_scene_about_button_y"));
	menu->addChild(buttonAbout);
	//���ఴť
//	MenuItemImage* buttonMore = MenuItemImage::create("UI/START/START_UI_UP_0002_....png", "UI/START/START_UI_DOWN_0002_....png", "UI/START_UI_UP_0003__.png", CC_CALLBACK_1(HelloWorld::settingCallBack, this));
//	buttonMore->setPosition(leftFootWeight / 2, CD_FLOAT("start_scene_more_button_y"));
//	menu->addChild(buttonMore);
	//��ʼ��ť
	MenuItemImage* buttonStart = MenuItemImage::create("UI/START/START_UI_UP_0006_StartButton.png", "UI/START/START_UI_DOWN_0006_StartButton.png", "UI/START_UI_UP_0003__.png", CC_CALLBACK_1(HelloWorld::startCallBack, this));
	buttonStart->setPosition((size.width - leftFootWeight) / 2 + leftFootWeight, CD_FLOAT("start_scene_start_button_y"));
	menu->addChild(buttonStart);
	//�˳���ť
	MenuItemImage* exitStart = MenuItemImage::create("UI/START/exit1.png", "UI/START/exit2.png", "UI/exit2.png", CC_CALLBACK_1(HelloWorld::exitCallBack, this));
	exitStart->setPosition(CD_FLOAT("start_scene_exit_button_x"), CD_FLOAT("start_scene_exit_button_y"));
	menu->addChild(exitStart);
	//������ť
	MenuItemImage* buttonMsg = MenuItemImage::create("UI/START/msg1.png", "UI/START/msg2.png", "UI/msg2.png", CC_CALLBACK_1(HelloWorld::msgCallBack, this));
	buttonMsg->setPosition(CD_FLOAT("start_scene_msg_button_x"), CD_FLOAT("start_scene_msg_button_y"));
	menu->addChild(buttonMsg);
	//todo logo��̬����
	this->schedule(schedule_selector(HelloWorld::dyncLogo), 3.5f);
    
	//���Թ��� ��ʾFPS
	/*
	EventListenerTouchOneByOne* event = EventListenerTouchOneByOne::create();
	event->onTouchBegan = [=](Touch* touch, Event* event){
		if (logo->getBoundingBox().containsPoint(touch->getLocation()))
		{
			// �����LOGO����������ʱ�䣬��ô��ʾFPS
			Director::getInstance()->setDisplayStats(!Director::getInstance()->isDisplayStats());
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
	*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// ��������ť, ����1Ϊ��ť��������µ�ͼƬ, ����2Ϊ��ťѡ��ʱ��ͼƬ,����3Ϊ����appkey, ����4Ϊ����ص�
    UMShareButton *shareButton = UMShareButton::create("UI/START/share.png", "UI/START/share.png", "542752bcfd98c578990126ac", share_selector(shareCallback)) ;
	// ��ʾ�����˷�������ϵ�ƽ̨
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
//    platforms->push_back(RENREN) ;
    platforms->push_back(DOUBAN) ;
    platforms->push_back(WEIXIN_CIRCLE) ;
    platforms->push_back(WEIXIN);
    platforms->push_back(QZONE) ;
    platforms->push_back(QQ) ;
    // �������˷����������ʾ��ƽ̨
    shareButton->setPlatforms(platforms);
    // �����ı���������
    shareButton->setShareContent(CD_CHARS("share_content")) ;
    // ����Ҫ�����ͼƬ, ͼƬ֧�ֱ���ͼƬ��urlͼƬ, ����urlͼƬ������http://����https://��ͷ
    shareButton->setShareImage(CD_CHARS("share_picture")) ;
    // ���ð�ť��λ��
    shareButton->setPosition(leftFootWeight / 2, CD_FLOAT("start_scene_more_button_y"));
    // Ȼ�󿪷�����Ҫ���ð�ť��ӵ���Ϸ������
	menu->addChild(shareButton);
    // ********************** ����ƽ̨��Ϣ ***************************
    CCUMSocialSDK *sdk = shareButton->getSocialSDK();
    sdk->setWeiXinAppId("wx608e3343f4047772");
    // sdk->setQQAppIdAndAppKey("����QQ��app id", "appkey");
    sdk->setQQAppIdAndAppKey("1103269146", "hLU6S75uuvXx4gyD");
    // �����û����һ��ͼ�ķ���ʱ�û���ת����Ŀ��ҳ��, һ��Ϊapp��ҳ��������ҳ��
    sdk->setTargetUrl(CD_CHARS("share_websize"));
    //     // �򿪻��߹ر�log
    sdk->setLogEnable(false) ;
    // **********************   END ***************************
#endif

    return true;
}

void HelloWorld::aboutCallBack(cocos2d::Ref* ref)
{
	auto reScene = TransitionCrossFade::create(0.3f, AboutScene::createScene());
	Director::getInstance()->pushScene(reScene);
}

void HelloWorld::settingCallBack(cocos2d::Ref* ref)
{
	log("settingCallBack");
	MessageBox("The function to be realized.\nWill be updated in the next version.", "Sorry");
}

void HelloWorld::startCallBack(cocos2d::Ref* ref)
{	
	auto reScene = TransitionCrossFade::create(0.3f, LevelScene::createScene());
	Director::getInstance()->replaceScene(reScene);
}

void HelloWorld::exitCallBack(cocos2d::Ref* ref)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����ͳ���ͷ���Դ
	umeng::MobClickCpp::end();
#endif

	Director::getInstance()->end();
}

void HelloWorld::msgCallBack(cocos2d::Ref* ref)
{
	JINTools::openFeedback();
}

void HelloWorld::dyncLogo(float time)
{
	Size size(960, 640);
	float leftFootWeight = 194;
	Sprite* logo = Sprite::create("UI/START/START_UI_DOWN_0005_BAD-GAME.png");
	logo->setPosition((size.width - leftFootWeight) / 2 + leftFootWeight, CD_FLOAT("start_scene_logo_y"));
	this->addChild(logo);

	Sequence* action = Sequence::createWithTwoActions(cocos2d::DelayTime::create(0.3), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteNode, this)));
	logo->runAction(action);
}

void HelloWorld::deleteNode(cocos2d::Node* sender)
{
	sender->removeFromParent();
}



