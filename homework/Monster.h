#pragma once
#include "stdafx.h"

class CMonster
{
public:
	//1���� ����
	int id = 0;
	char name[ITEM_NAME_LENGTH];
	char GFX_PATH[GFX_PATH_LENGTH];
	int attack;
	int maxHealth;
	int currHealth;
	int exp;
	int gold;
	//������
	HABITAT habitat;
	float spawnChance;
	ELEMENT element = NONE;

public:
	void PrintMonster();
	
};
