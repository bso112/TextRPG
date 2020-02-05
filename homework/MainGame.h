#pragma once
#include "Character.h"
#include "Factory.h"
#include "InventoryMgr.h"

class CMainGame
{
private:
	void EnterForge();
	void EnterPharmacy();
	void EnterDungeon(HABITAT habitat);
	void EnhanceWeaponPage();
	COMBAT Battle(CCharacter* character, CMonster* monster);
public:
	void Initalize();
	void Progress();
	void Release();
private:
	CCharacter* character;
	CFactory factory;
	CInventoryMgr inventoryMgr;

};