#pragma once
#include "stdafx.h"

class CBufItem
{
public:
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	//���� �׸�
	int attackBuf;
	int maxHealthBuf;
	int levelBuf;
	int expBuf;
	//�������� �Ӽ�
	ELEMENT element;
	//�Ҹ� �������ΰ�?
	bool isConsumable;
	char description[DESCRIPTION_LENGTH];
	//��� Ȯ��
	float dropChance;
	//����
	int price;
public:
	CBufItem();
	~CBufItem();
	void PrintGemInfo() const;
};
