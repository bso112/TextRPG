#include "stdafx.h"
#include "InventoryMgr.h"

void CInventoryMgr::Initialize(CCharacter* _character)
{
	character = _character;
	inventory = &character->inventory;
}

void CInventoryMgr::Process()
{
	ShowInventory();
}

void CInventoryMgr::Release()
{
	character = nullptr;
	inventory = nullptr;
}

void CInventoryMgr::ShowInventory()
{
	while (true)
	{
		system("cls");

		cout << "<장착중> " << endl;
		character->inventory.currWeapon->printWeaponInfo();
		cout << "\n\n";


		cout << "인벤토리" << endl;


		cout << "0. 나가기 1.포션 2.무기 3.젬" << endl;

		int whatBag = 0;
		cin >> whatBag;

		switch (whatBag)
		{
		case 0:
			return;
			break;
		case 1:
			ShowPotionBag();
			break;
		case 2:
			ShowWeaponBag();
			break;
		case 3:
			ShowGemBag();
			break;
		default:
			break;
		}



	}
}

void CInventoryMgr::ShowWeaponBag()
{
	while (true)
	{

		system("cls");


		cout << "<장착중> " << endl;
		inventory->currWeapon->printWeaponInfo();
		cout << "\n\n";


		cout << "무기 인벤토리" << "\n\n";


		int weaponCnt = inventory->weapons.size();


		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			inventory->weapons[i]->printWeaponInfo();
			cout << "\n\n";
		}


		cout << "0. 나가기 아이템번호. 사용 999.장착해제" << endl;
		unsigned int selection;
		cin >> selection;

		if (0 == selection)
		{
			return;
		}
		else if (999 == selection)
		{
			//현재 착용장비 인벤토리에 넣기
			inventory->weapons.push_back(inventory->currWeapon);
			//장착해제
			inventory->currWeapon = new CWeapon;
			inventory->currWeapon = {};
			strcpy_s(inventory->currWeapon->name, ITEM_NAME_LENGTH, "미착용");
		}
		//selection 1 2 3 4 5
		//potion    0 1 2 3 4
		//항목 번호를 제대로 입력했으면
		else if (selection <= inventory->weapons.size())
		{
			cout << inventory->weapons[selection - 1]->name << "을 장착했다!" << endl;
			system("pause");


			//플레이어가 무기를 끼고 있었다면 인벤토리에 넣는다.
			if (inventory->currWeapon->id != 0)
			{
				character->attack -= inventory->currWeapon->attack;
				inventory->weapons.push_back(inventory->currWeapon);
			}
			//맨손이었으면 빈객체를 파괴한다.
			else
			{
				delete inventory->currWeapon;
				inventory->currWeapon = nullptr;
			}

			//무기를 장착한다.
			inventory->currWeapon = inventory->weapons[selection - 1];
			character->attack += inventory->currWeapon->attack;
			//장착한 무기는 인벤토리에서 삭제한다.
			inventory->weapons.erase(inventory->weapons.begin() + (selection - 1));



		}
	}
}

void CInventoryMgr::ShowPotionBag()
{
	if (nullptr == character)
	{
		cout << "인벤토리의 오너가 없습니다!" << endl;
		return;
	}

	while (true)
	{

		system("cls");

		cout << "포션 인벤토리" << "\n\n";

		int potionCnt = inventory->potions.size();
		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			inventory->potions[i]->printPotionInfo();
			cout << "\n\n";
		}


		cout << "0. 나가기 아이템번호. 사용" << endl;
		unsigned int selection;
		cin >> selection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == selection)
		{
			return;
		}
		else if (selection <= inventory->potions.size())
		{
			cout << inventory->potions[selection - 1]->name << "을 사용했다!" << endl;
			system("pause");


			if (character->currHealth >= character->maxHealth)
			{
				cout << "이미 체력이 꽉 차있습니다.";
				return;
			}
			CPotion* potion = inventory->potions[selection - 1];
			//체력회복
			character->currHealth += potion->healAmount;
			//포션 지우기
			delete potion;
			//인벤토리 줄이기
			inventory->potions.erase(inventory->potions.begin() + selection - 1);
		}
	}
}

void CInventoryMgr::ShowGemBag()
{
	if (nullptr == character)
	{
		cout << "인벤토리의 오너가 없습니다!" << endl;
		return;
	}

	while (true)
	{

		system("cls");

		cout << "젬 인벤토리" << "\n\n";

		int gemCount = inventory->gems.size();
		for (int i = 0; i < gemCount; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			inventory->gems[i]->PrintGemInfo();
			cout << "\n\n";
		}


		cout << "0. 나가기 아이템번호. 사용" << endl;
		unsigned int gemSelection;
		cin >> gemSelection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == gemSelection)
		{
			return;
		}
		else if (gemSelection <= inventory->gems.size())
		{
			//조합할 무기 선택화면
			while (true)
			{
				system("cls");
				int weaponSize = inventory->weapons.size();
				if (0 == weaponSize)
				{
					cout << "현재 잼을 부착할 수 없는 무기가 없습니다. (착용중인 무기는 젬을 부착할 수 없습니다)" << endl;
					system("pause");
					break;
				}

				for (int i = 0; i < weaponSize; ++i)
				{
					cout << "<" << i + 1 << "번>" << endl;
					inventory->weapons[i]->printWeaponInfo();
					cout << "\n\n";
				}

				cout << "0. 나가기 아이템번호. 사용" << endl;
				unsigned int weaponSelection;
				cin >> weaponSelection;

				if (0 == weaponSelection)
				{
					break;
				}
				else if (weaponSelection <= inventory->weapons.size())
				{
					//무기에 젬 조합하기
					CWeapon* weapon = inventory->weapons[weaponSelection - 1];
					CBufItem* gem = inventory->gems[gemSelection - 1];
					weapon->attack += gem->attackBuf;
					weapon->element = gem->element;
					character->maxHealth += gem->maxHealthBuf;
					character->currExp += gem->expBuf;
					//젬이 있으면 교체
					if (weapon->gem)
					{
						inventory->gems.push_back(weapon->gem);

					}
					//무기에 젬 부착
					weapon->gem = gem;
					//인벤토리에서 젬 삭제
					inventory->gems.erase(inventory->gems.begin() + gemSelection - 1);
					cout << "젬 부착 완료!" << endl;
				}
			}
		}
	}
}
