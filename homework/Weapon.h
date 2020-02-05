#pragma once

#include "stdafx.h"
#include "BufItem.h"

class CWeapon
{
public:
	//아이템 아이디(1부터 시작) 0은 맨손
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	int attack;
	//아이템 설명. 
	char description[DESCRIPTION_LENGTH];
	int price;
	//직업
	OCCUPATION  occupation;
	//강화레벨
	int level = 1;
	//아이템의 속성
	ELEMENT element = NONE;
	//부착된 젬
	CBufItem* gem;
public:
	void printWeaponInfo();
	void CWeapon::EnhanceWeapon();
	




};