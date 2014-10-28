#include "MonsterEx.h"
#include "Weapon.h"
#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"

USING_NS_CC;

void MonsterEx::initParam()
{
	startTag = true;
	jumpCount = 0;
	countGun = 0;

	fireTime = SD_FLOAT("monster_float_fireTime");	//���𵹼�ʱ
	fireTimeCount = fireTime;	

	speed = SD_FLOAT("monster_float_speed");
	spring = SD_FLOAT("monster_float_spring");
	moveState = MOVE_STOP;
	//���ó���
	this->setDir(DIR_RIGHT);
	//����Ѫ��
	this->setHp(SD_INT("monster_int_hp"));

	this->getBody()->SetFixedRotation(true);//�̶���ת
	//�������� Ťת��
	b2MassData mass;
	mass.mass = SD_FLOAT("monster_float_mass");
	mass.I = SD_FLOAT("monster_float_i");
	mass.center = this->getBody()->GetLocalCenter();
	this->getBody()->SetMassData(&mass);

	//���������
	this->setType(TYPE_MONSTER);
	//�����Щ���巽ʽ��ײ
	this->setMask(
		TYPE_BRICK |
		TYPE_COIN |
		TYPE_HERO |
		TYPE_PRIZE |
		TYPE_ARTICLE |
		TYPE_WEAPON);
	//����ֹͣ����
	moveStop();
}

bool MonsterEx::init(float x, float y, float width, float height)
{
	if (!Aware::init(x, y, width, height))
	{
		return false;
	}
	initParam();

	return true;
}

bool MonsterEx::init(float x, float y, b2Vec2* points, int count)
{
	if (!Aware::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;
}

void MonsterEx::dead()
{
	Aware::dead();

	//����������ײ
	setMask(TYPE_BRICK);
	//����ʱֹͣ
	this->moveStop();
	//todo �˴�Ӧ���޸�
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("monster_animate_dead"), SD_FLOAT("monster_float_dead_speed"));
	Action* action = Sequence::createWithTwoActions(animate, CallFunc::create(CC_CALLBACK_0(MonsterEx::ended, this)));
	this->stopAllActions();
	this->runAction(action);
}

void MonsterEx::ended()
{
	Aware::ended();
	this->autoRemovePhysicsSprite();
}

void MonsterEx::moveStop()
{
	//������ǵ�һ��stop  ��δ�ƶ� ��ô������ֹͣ����
	if (!startTag && moveState == MOVE_STOP)
	{
		return;
	}
	startTag = false;	//��һ�α�ʶ����false
	moveState = MOVE_STOP;
	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.x = 0;
	this->getBody()->SetLinearVelocity(vec);
	//todo �˴�Ӧ���޸�
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("monster_animate_stop"), SD_FLOAT("monster_float_stop_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void MonsterEx::moveLeft()
{
	if (moveState == MOVE_LEFT)
		return;
	if (isDie() || isOver())
		return;

	this->setDir(DIR_LEFT);
	moveState = MOVE_LEFT;
}

void MonsterEx::moveRight()
{
	if (moveState == MOVE_RIGHT)
		return;
	if (isDie() || isOver())
		return;

	this->setDir(DIR_RIGHT);
	moveState = MOVE_RIGHT;
}

void MonsterEx::jump()
{
	if (jumpCount >= 1)
		return;
	if (isDie() || isOver())
		return;

	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.y = spring;
	this->getBody()->SetLinearVelocity(vec);

	jumpCount++;
}

void MonsterEx::update(float ft)
{
	Aware::update(ft);

	/*�����ƶ�*/
	if (moveState == MOVE_LEFT)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = -speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	/*�����ƶ�*/
	else if (moveState == MOVE_RIGHT)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	//todo///////////AI///////////////////
	Hero* hero = GameManager::getInstance()->hero;

	fireTimeCount = fireTimeCount - ft;
	//ʲôʱ����һ���ӵ�
	if (fireTimeCount <= 0)
	{
		fireTimeCount = fireTime;
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

void MonsterEx::BeginContact(GameObject* other, b2Contact* contact)
{
	if (other->getType() == TYPE_BRICK || other->getType() == TYPE_ARTICLE)
	{//�ȵ��ذ��������ʱ��
		//��ȡ��ײ������ĺ�������
		float y = contact->GetManifold()->localNormal.y;
		if (y > 0)
		{ //�ȵ��ذ�
			jumpCount = 0;	//��Ծ����
		}
	}
}

void MonsterEx::fire()
{
	if (isDie() || isOver())
		return;
	Weapon* w = Weapon::create(this);
	//��ӵ�herolayer��
	GameManager::getInstance()->heroLayer->addChild(w, 50);
}
