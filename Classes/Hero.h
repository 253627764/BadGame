#ifndef _HERO_H_
#define _HERO_H_

#include "GameManager.h"
#include "Aware.h"
#include "Weapon.h"

class Hero : public Aware
{
protected:
	bool startTag;	//��һ�ο�ʼ��ʶ
	int jumpCount;
	int coin;	//���
	//�޵б�ʶ
	bool unbeatable;
	//�޵�ʱ��
	float unbeatableTime;

	/*�˶�״̬ moveState*/
	CC_SYNTHESIZE(MOVE, moveState, MoveState);
	/*������ spring*/
	CC_SYNTHESIZE(float , spring, Spring);
	/*�ٶ� speed*/
	CC_SYNTHESIZE(float , speed, Speed);
public:
	/*��ʼ��Ӣ�� ֻΪ�˷����̬*/
	virtual void initParam();

	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Hero, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(Hero, float, float, b2Vec2*, int);

	virtual void dead() override;
	virtual void ended() override;

	/*���*/
	void setCoin(int coin);
	int getCoin();

	/*ֹͣ�ƶ�*/
	virtual void moveStop();
	/*�����ƶ�*/
	virtual void moveLeft();
	/*�����ƶ�*/
	virtual void moveRight();
	/*��Ծ*/
	virtual void jump();
	/*����*/
	virtual void fire();
	/*�޵� �������޵�ʱ��*/
	virtual void setUnbeatable(float unbeatableTime);
	virtual bool isUnbeatable();

	virtual void update(float ft) override;

	virtual void BeginContact(GameObject* other, b2Contact* contact);

	virtual void setHp(int var);

};

#endif