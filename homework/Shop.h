#pragma once
#include "stdafx.h"
#include "Factory.cpp"


class CShop
{

public:

	void EnhanceWeapon(CWeapon* weapon);

	void EnhanceWeaponPage(CCharacter* character);


	void EnterPharmacy(CCharacter* character, CFactory factory);

	void EnterForge(CCharacter* character, CFactory factory);



};