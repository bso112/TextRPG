#pragma once

#include "stdafx.h"
#include "BufItem.h"

class CWeapon
{
public:
	//������ ���̵�(1���� ����) 0�� �Ǽ�
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	int attack;
	//������ ����. 
	char description[DESCRIPTION_LENGTH];
	int price;
	//����
	OCCUPATION  occupation;
	//��ȭ����
	int level = 1;
	//�������� �Ӽ�
	ELEMENT element = NONE;
	//������ ��
	CBufItem* gem;
public:
	void printWeaponInfo();
	void CWeapon::EnhanceWeapon();
	




};