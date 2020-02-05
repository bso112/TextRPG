#pragma once

#include "stdafx.h"
#include "Character.h"
#include "Monster.h"

class BattleManager
{

public:
	COMBAT Battle(CCharacter* character, CMonster* monster);
	
};