#pragma once
#include "stdafx.h"

class CBufItem
{
public:
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	//버프 항목
	int attackBuf;
	int maxHealthBuf;
	int levelBuf;
	int expBuf;
	//아이템의 속성
	ELEMENT element;
	//소모성 아이템인가?
	bool isConsumable;
	char description[DESCRIPTION_LENGTH];
	//드롭 확률
	float dropChance;
	//가격
	int price;
public:
	CBufItem();
	~CBufItem();
	void PrintGemInfo() const;
};
