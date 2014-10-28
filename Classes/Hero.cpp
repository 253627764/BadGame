#include "Hero.h"
#include "Grenade.h"
#include "StaticData.h"
#include "HudLayer.h"
#include "FinishScene.h"

USING_NS_CC;

void Hero::initParam()
{
	startTag = true;
	jumpCount = 0;
	setCoin(0);//��� todo
	unbeatable = false; //�޵б�ʶ
	unbeatableTime = 0;	//�޵�ʱ��
	
	speed = SD_FLOAT("hero_float_speed");	//�����ٶ�
	spring = SD_FLOAT("hero_float_spring");	//������
	moveState = MOVE_STOP;
	//���ó���
	this->setDir(DIR_RIGHT);
	//����Ѫ��
	this->setHp(SD_INT("hero_int_hp"));

	this->getBody()->SetFixedRotation(true);

	b2MassData mass;
	mass.mass = SD_FLOAT("hero_float_mass");
	mass.I = SD_FLOAT("hero_float_i");
	mass.center = this->getBody()->GetLocalCenter();
	this->getBody()->SetMassData(&mass);

	//���������
	this->setType(TYPE_HERO);
	//�����Щ���巽ʽ��ײ
	this->setMask(
		TYPE_BRICK |
		TYPE_COIN |
		TYPE_MONSTER |
		TYPE_PRIZE |
		TYPE_ARTICLE |
		TYPE_WEAPON);
	//����ֹͣ����
	moveStop();
}

bool Hero::init(float x, float y, float width, float height)
{
	if(!Aware::init(x, y, width, height))
	{
		return false;
	}
	initParam();

	return true;
}

bool Hero::init(float x, float y, b2Vec2* points, int count)
{
	if(!Aware::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;
}

void Hero::dead()
{
	Aware::dead();
	//����������ײ
	setMask(TYPE_BRICK);
	//����ʱֹͣ
	this->moveStop();
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_dead"), SD_FLOAT("hero_float_dead_speed"));
	Action* action = Sequence::createWithTwoActions(animate, CallFunc::create(CC_CALLBACK_0(Hero::ended, this)));
	this->stopAllActions();
	this->runAction(action);
}

void Hero::ended()
{
	Aware::ended();
	//��ת����������
	auto finish = FinishScene::createScene(coin);
	Director::getInstance()->replaceScene(finish);
}

void Hero::moveStop()
{
	//������ǵ�һ��stop  ��δ�ƶ� ��ô������ֹͣ����
	if(!startTag && moveState == MOVE_STOP)
	{
		return;
	}
	startTag = false;	//��һ�α�ʶ����false
	moveState = MOVE_STOP;
	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.x = 0;
	this->getBody()->SetLinearVelocity(vec);

	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_stop"), SD_FLOAT("hero_float_stop_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void Hero::moveLeft()
{
	if(moveState == MOVE_LEFT)
		return;
	if(isDie() || isOver())
		return;

	this->setDir(DIR_LEFT);
	moveState = MOVE_LEFT;
	//���Ŷ���
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_walk_left"), SD_FLOAT("hero_float_walk_left_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void Hero::moveRight()
{
	if(moveState == MOVE_RIGHT)
		return;
	if(isDie() || isOver())
		return;

	this->setDir(DIR_RIGHT);
	moveState = MOVE_RIGHT;
	//���Ŷ���
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_walk_right"), SD_FLOAT("hero_float_walk_right_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void Hero::jump()
{
	if(jumpCount >= 2)
		return;
	if(isDie() || isOver())
		return;
	
	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.y = spring;
	this->getBody()->SetLinearVelocity(vec);
	
	jumpCount++; //�ۼ� ��������
}

void Hero::update(float ft)
{
	Aware::update(ft);
	/*�����ƶ�*/
	if(moveState == MOVE_LEFT)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = -speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	/*�����ƶ�*/
	else if(moveState == MOVE_RIGHT)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	/*�޸��޵�ʱ��*/
	unbeatableTime = unbeatableTime - ft;
	if (unbeatableTime <= 0)
		unbeatable = false;
}

void Hero::BeginContact(GameObject* other, b2Contact* contact)
{
	if(other->getType() == TYPE_BRICK )
	{//�ȵ��ذ��������ʱ��
		//��ȡ��ײ������ĺ�������
		float y = contact->GetManifold()->localNormal.y;
		if (y > 0)
		{ //�ȵ��ذ�
			jumpCount = 0;	//��Ծ����
		}
	}
	else if (other->getType() == TYPE_ARTICLE)
	{
		jumpCount = 0;
	}
}

void Hero::fire()
{
	if (isDie() || isOver())
		return;
// 	Weapon* w = Weapon::create(this);
// 	GameManager::getInstance()->heroLayer->addChild(w, 50);

	Grenade* g = Grenade::create(this);
	GameManager::getInstance()->heroLayer->addChild(g, 51);
}

void Hero::setCoin(int coin)
{
	this->coin = coin;
	//���»���Ǯ������
	GameManager::getInstance()->hudLayer->replaceCoinHud();
}

int Hero::getCoin()
{
	return coin;
}

void Hero::setUnbeatable(float unbeatableTime)
{
	if(!unbeatable)
		this->unbeatableTime = unbeatableTime;
	unbeatable = true;
}

bool Hero::isUnbeatable()
{
	return unbeatable;
}

void Hero::setHp(int var)
{
	if (isUnbeatable()) //����޵� �Ͳ�����Ѫ����
		return;
	Aware::setHp(var);
	//����HUD
	GameManager::getInstance()->hudLayer->replaceHpHud();
}
