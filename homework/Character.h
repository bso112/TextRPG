#pragma once
#include "stdafx.h"
#include "Inventory.h"


class CCharacter
{

public:
	char name[16];
	int attack;
	int maxHealth;
	int currHealth;
	int level;
	int maxExp;
	int currExp;
	int gold;
	CInventory inventory;
	OCCUPATION  occupation;

public:

	void CreateCharacter(int selection);

	void PrintCharacter();

	void LevelUp();

	void OnGetExp();

	CCharacter* Load();

	void Save(CCharacter* character);
	

};