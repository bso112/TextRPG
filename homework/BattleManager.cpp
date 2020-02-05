#include "BattleManager.h"


COMBAT BattleManager::Battle(CCharacter* character, CMonster* monster)
{
	while (true)
	{
		system("cls");
		character->PrintCharacter();
		cout << "================================================" << endl;

		monster->PrintMonster();

		cout << "================================================" << endl;
		cout << "1. °ø°Ý 2. µµ¸Á" << endl;

		int iSelect_Behavior;
		cin >> iSelect_Behavior;

		if (2 == iSelect_Behavior)
		{
			return COMBAR_RUN;
		}

		ELEMENT element = character->weapon->element;

		int characterAttack = character->attack;
		int monsterAttack = monster->attack;

		if (NONE != element)
		{
			int result = element - monster->element;

			//»ó¼º È®ÀÎ

			if (1 == result || -3 == result)
			{
				//½Â
				characterAttack *= 2;
			}
			else if (-1 == result || 3 == result)
			{
				//ÆÐ
				monsterAttack *= 2;
			}
		}

		monster->currHealth -= characterAttack;
		character->currHealth -= monsterAttack;

		if (monster->currHealth <= 0)
		{
			return COMBAT_WIN;
		}
		if (character->currHealth <= 0)
		{
			return COMBAT_LOSE;
		}
	}

}


	