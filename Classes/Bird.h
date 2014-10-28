#ifndef _BIRD_H_
#define _BIRD_H_

#include "Aware.h"

class Bird : public Aware
{
protected:
	bool fly;
	bool startTag;	//��һ�α�ʶ
	int sight;	//��Ұ
public:
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Bird, float, float, float, float);

	/*ֹͣ����-����*/
	virtual void flyStop();
	/*�ɵ�*/
	virtual void flyTo(cocos2d::Vec2 vec);
	/*�Ƿ��ڷ�*/
	virtual bool isFly();

	virtual void dead();
	virtual void ended();

	virtual void update(float ft);
};

#endif