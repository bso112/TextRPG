#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "Bufitem.h" //중복인데.. 꼬이려나? 웨폰에 이미 있음.
#include "Potion.h"
#include <vector>

//인벤토리에 들어갈 자료형 추가시, Finalize함수에서 인벤토리 할당해제할때 그 자료형도 같이 해제해야함.
class CInventory
{
public:
	//포션가방
	vector<CPotion*> potions;
	//무기가방
	vector<CWeapon*> weapons;
	vector<CBufItem*> gems;
	CWeapon* currWeapon;
public:
	int GetInventorySize();
	

	
	
};
