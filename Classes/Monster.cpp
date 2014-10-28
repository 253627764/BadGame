#include "Monster.h"
#include "Weapon.h"
/*
������
*/
USING_NS_CC;

void Monster::initParam()
{
	countGun = 0;
	jumpCount = 0;
	speed = 1;
	spring = 5;
	moveState = MOVE_STOP;
	//���ó���
	this->setDir(DIR_RIGHT);
	//���������
	this->setType(TYPE_MONSTER);
	//�����Щ���巽ʽ��ײ
	this->setMask(
		TYPE_BRICK		| 
		TYPE_COIN		| 
		TYPE_HERO		| 
		TYPE_PRIZE		| 
		TYPE_ARTICLE	|
		TYPE_WEAPON);
	//����ֹͣ����
	moveStop();
}

bool Monster::init(float x, float y, float width, float height)
{
	if(!Hero::init(x, y, width, height))
	{
		return false;
	}
	initParam();
	return true;
}

bool Monster::init(float x, float y, b2Vec2* points, int count)
{
	if(!Hero::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;
}

void Monster::fire()
{
	if(isDie() || isOver())
		return;
	Weapon* w = Weapon::create(this);
	GameManager::getInstance()->monsterLayer->addChild(w, 50);
}

void Monster::update(float ft)
{
	Hero::update(ft);
	Hero* hero = GameManager::getInstance()->hero;
	
	if(countGun >= 60*4)
	{
		countGun = 0;
		fire();
	}
	countGun++;

	if (this->getPositionX() < hero->getPositionX())
	{
		this->moveRight();
	}
	else
	{
		this->moveLeft();
	}
}

void Monster::ended()
{
	Hero::ended();
	this->autoRemovePhysicsSprite();
}