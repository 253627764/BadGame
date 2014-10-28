#ifndef _CONFIG_H_
#define _CONFIG_H_

#define TYPE_BRICK   1		/*ש��*/

#define TYPE_HERO    2		/*Ӣ��-��*/
#define TYPE_MONSTER 4		/*����-��*/
#define TYPE_ANIMAL	 8		/*����-������*/

#define TYPE_PRIZE   16		/*ս��Ʒ*/
#define TYPE_COIN	 32		/*���*/
#define TYPE_WEAPON  64		/*�ӵ�������*/
#define TYPE_ARTICLE	 128	/*�ɽ���������*/

/*
#define TYPE_ANIMAL	 256
#define TYPE_ANIMAL	 512
#define TYPE_ANIMAL	 1024
#define TYPE_ANIMAL	 2048
#define TYPE_ANIMAL	 4096
#define TYPE_ANIMAL	 8192
#define TYPE_ANIMAL	 16384
*/
#define TYPE_NOTHING	 32768

/*����*/
enum DIR
{
	DIR_LEFT,
	DIR_RIGHT
};

enum MOVE
{
	MOVE_STOP,
	MOVE_LEFT,
	MOVE_RIGHT,
};

#endif

