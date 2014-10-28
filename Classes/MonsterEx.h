#ifndef _MONSTER_EX_H_
#define _MONSTER_EX_H_

#include "Aware.h"

class MonsterEx : public Aware
{
protected:
	bool startTag;	//��һ�ο�ʼ��ʶ
	int jumpCount;
	int countGun;
	float fireTimeCount;	//���𵹼�ʱ
	float fireTime;			//���𵹼�ʱ
	/*�˶�״̬ moveState*/
	CC_SYNTHESIZE(MOVE, moveState, MoveState);
	/*������ spring*/
	CC_SYNTHESIZE(int, spring, Spring);
	/*�ٶ� speed*/
	CC_SYNTHESIZE(int, speed, Speed);
public:
	/*��ʼ��Ӣ�� ֻΪ�˷����̬*/
	virtual void initParam();

	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(MonsterEx, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(MonsterEx, float, float, b2Vec2*, int);

	virtual void dead() override;
	virtual void ended() override;

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

	virtual void update(float ft) override;

	virtual void BeginContact(GameObject* other, b2Contact* contact);
};

#endif