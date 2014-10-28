#ifndef _LIFE_BOJECT_H_
#define _LIFE_BOJECT_H_

#include "GameObject.h"

class LifeObject : public GameObject{
protected:
	bool die;
	bool over;
public:
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(LifeObject, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(LifeObject, float, float, b2Vec2*, int);

	//Ѫ��
	CC_SYNTHESIZE(int, hp, Hp);	
	//������
	CC_SYNTHESIZE(int, atk, Atk);	

	/*��������״̬*/
	virtual void setDie(bool die);
	/*�жϵ�ǰ�������Ƿ�����*/
	virtual bool isDie() const;
	/*���ý���״̬*/
	virtual void setOver(bool over);
	/*���������Ƿ����*/
	virtual bool isOver() const;

	/*��֡�ص�����*/
	virtual void update(float ft);
	
	/* �Զ����� ����ʱ�Ļص����� �����������д�ú������� �ú�������hp����0ʱ�Զ�����һ��*/
	virtual void dead();
	/* ע��ע�⣬�����������Զ�����~ �Ƽ���������д�붯���ٵ�������
	 * ��������ͨ���ӳٶ�������ʬ�嵽һ��ʱ��
	 * ���ô˷�����ֱ��ɾ��������,������over=true
	 * ������˷�����Ӧ�ó����ڱ����У��Ժ���ع���Ӧ���޸Ĵ�����
	 */
	virtual void ended();
};

#endif