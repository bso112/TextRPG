#include "stdafx.h"
#include "Shop.h"

void CShop::EnhanceWeapon(CWeapon* weapon)
{
	//0~99까지의 실수 난수.
	float random = (rand() / (float)RAND_MAX) * 99.f;

	//레벨 1일때 기본 확률
	float chance = BASE_ENHANCE_CHANCE;

	//레벨이의 5.2배만큼 확률 하락
	chance -= weapon->level * 5.2f;




	if (chance >= random)
	{
		system("cls");
		cout << "강화에 성공했습니다!" << endl;
		cout << "<강화 전>" << endl;
		weapon->printWeaponInfo();
		float weight = weapon->level / 3.f;
		weight = weight < 1 ? weight = 1 : weight;
		weapon->level += 1;
		weapon->attack += int(6 * weight);
		weapon->price += int(30 * weight);
		cout << "<강화 후>" << endl;
		weapon->printWeaponInfo();
		system("pause");
	}
	else
	{
		cout << "강화 실패!" << endl;
		system("pause");
	}



}

void CShop::EnhanceWeaponPage(CCharacter* character)
{
	while (true)
	{

		system("cls");

		cout << "무기 인벤토리" << "\n\n";

		cout << "<장착중> " << endl;
		cout << "※장착중인 무기는 강화가 불가합니다." << endl;
		character->weapon->printWeaponInfo();
		cout << "\n\n";

		int weaponCnt = character->inventory->weapons.size();
		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			character->inventory->weapons[i]->printWeaponInfo();
			cout << "강화확률: " << BASE_ENHANCE_CHANCE - (character->inventory->weapons[i]->level * 5.2f) << endl;
			cout << "\n\n";
		}


		cout << "0. 나가기 아이템번호. 강화하기" << endl;
		unsigned int selection;
		cin >> selection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == selection)
		{
			return;
		}
		//항목 번호를 제대로 입력했으면
		else if (selection <= character->inventory->weapons.size())
		{
			//강화비
			int cost = character->inventory->weapons[selection - 1]->price / 5;
			//돈이 충분하면
			if (character->gold >= cost)
			{
				character->gold -= cost;
				//강화시도
				EnhanceWeapon(character->inventory->weapons[selection - 1]);
			}
		}
	}
}


