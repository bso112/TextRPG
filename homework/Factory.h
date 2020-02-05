#pragma once

#include "stdafx.h"
#include "Monster.h"
#include "Potion.h"
#include "Weapon.h"

class CFactory
{
public:
	CMonster* monsters = nullptr;
	int monsterCnt = 0;
	CPotion* potions = nullptr;
	int potionCnt = 0;
	CWeapon* weapons = nullptr;
	int weaponCnt = 0;
	CBufItem* bufItems = nullptr;
	int bufItemCnt = 0;

private:

	int GetInfo(char(**items)[CHAR_PER_LINE], char path[30]);

	void CreateAllWeapons();

	void CreateAllMonsters();

	void CreateAllPotions();

	void CreateAllbufItems();

public:

	void Initialize();

	void Release();


	CWeapon* CreateWeapon(int id);


	CMonster* CreateMonster(int id);


	CMonster* CreateMonster(int length, HABITAT habitat);

	CPotion* CreatePotion(int id);


	CBufItem* CreateBufItem(int id);


	CBufItem* CreateDropItem()
	{
		float chanceSum = 0;

		int length = bufItemCnt;
		//오름차순 정렬
		for (int i = 0; i < length; ++i)
		{
			chanceSum += bufItems[i].dropChance;

			for (int j = 0; j < length - 1; ++j)
			{
				if (bufItems[j].dropChance > bufItems[j + 1].dropChance)
				{
					CBufItem tmp = bufItems[j];
					bufItems[j] = bufItems[j + 1];
					bufItems[j + 1] = tmp;

				}
			}
		}

		//확률적으로 뽑은 숫자
		int randomNum = (rand() % (int)chanceSum) + 1;

		//누적확률
		float sum = 0.0f;

		int toCreate = 0;
		for (int i = 0; i < length; ++i)
		{
			sum += bufItems[i].dropChance;
			if (sum >= randomNum)
			{
				toCreate = i;
				break;
			}

		}


		CBufItem* item = new CBufItem;
		memcpy(item, &(bufItems[toCreate]), sizeof(CBufItem));
		return item;
	}



};
