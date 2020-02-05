#pragma once
#include "Character.h"
#include "Inventory.h"

class CInventoryMgr
{
private:
	CCharacter* character;
	CInventory* inventory;
public:
	void Initialize(CCharacter* _character);
	void Process();
	void Release();
private:
	void ShowInventory();
	void ShowWeaponBag();
	void ShowPotionBag();
	void ShowGemBag();
		
};