#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "Bufitem.h" //�ߺ��ε�.. ���̷���? ������ �̹� ����.
#include "Potion.h"
#include <vector>

//�κ��丮�� �� �ڷ��� �߰���, Finalize�Լ����� �κ��丮 �Ҵ������Ҷ� �� �ڷ����� ���� �����ؾ���.
class CInventory
{
public:
	//���ǰ���
	vector<CPotion*> potions;
	//���Ⱑ��
	vector<CWeapon*> weapons;
	vector<CBufItem*> gems;
	CWeapon* currWeapon;
public:
	int GetInventorySize();
	

	
	
};
