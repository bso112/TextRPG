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

		cout << "<������> " << endl;
		character->inventory.currWeapon->printWeaponInfo();
		cout << "\n\n";


		cout << "�κ��丮" << endl;


		cout << "0. ������ 1.���� 2.���� 3.��" << endl;

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


		cout << "<������> " << endl;
		inventory->currWeapon->printWeaponInfo();
		cout << "\n\n";


		cout << "���� �κ��丮" << "\n\n";


		int weaponCnt = inventory->weapons.size();


		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			inventory->weapons[i]->printWeaponInfo();
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ��� 999.��������" << endl;
		unsigned int selection;
		cin >> selection;

		if (0 == selection)
		{
			return;
		}
		else if (999 == selection)
		{
			//���� ������� �κ��丮�� �ֱ�
			inventory->weapons.push_back(inventory->currWeapon);
			//��������
			inventory->currWeapon = new CWeapon;
			inventory->currWeapon = {};
			strcpy_s(inventory->currWeapon->name, ITEM_NAME_LENGTH, "������");
		}
		//selection 1 2 3 4 5
		//potion    0 1 2 3 4
		//�׸� ��ȣ�� ����� �Է�������
		else if (selection <= inventory->weapons.size())
		{
			cout << inventory->weapons[selection - 1]->name << "�� �����ߴ�!" << endl;
			system("pause");


			//�÷��̾ ���⸦ ���� �־��ٸ� �κ��丮�� �ִ´�.
			if (inventory->currWeapon->id != 0)
			{
				character->attack -= inventory->currWeapon->attack;
				inventory->weapons.push_back(inventory->currWeapon);
			}
			//�Ǽ��̾����� ��ü�� �ı��Ѵ�.
			else
			{
				delete inventory->currWeapon;
				inventory->currWeapon = nullptr;
			}

			//���⸦ �����Ѵ�.
			inventory->currWeapon = inventory->weapons[selection - 1];
			character->attack += inventory->currWeapon->attack;
			//������ ����� �κ��丮���� �����Ѵ�.
			inventory->weapons.erase(inventory->weapons.begin() + (selection - 1));



		}
	}
}

void CInventoryMgr::ShowPotionBag()
{
	if (nullptr == character)
	{
		cout << "�κ��丮�� ���ʰ� �����ϴ�!" << endl;
		return;
	}

	while (true)
	{

		system("cls");

		cout << "���� �κ��丮" << "\n\n";

		int potionCnt = inventory->potions.size();
		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			inventory->potions[i]->printPotionInfo();
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ���" << endl;
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
			cout << inventory->potions[selection - 1]->name << "�� ����ߴ�!" << endl;
			system("pause");


			if (character->currHealth >= character->maxHealth)
			{
				cout << "�̹� ü���� �� ���ֽ��ϴ�.";
				return;
			}
			CPotion* potion = inventory->potions[selection - 1];
			//ü��ȸ��
			character->currHealth += potion->healAmount;
			//���� �����
			delete potion;
			//�κ��丮 ���̱�
			inventory->potions.erase(inventory->potions.begin() + selection - 1);
		}
	}
}

void CInventoryMgr::ShowGemBag()
{
	if (nullptr == character)
	{
		cout << "�κ��丮�� ���ʰ� �����ϴ�!" << endl;
		return;
	}

	while (true)
	{

		system("cls");

		cout << "�� �κ��丮" << "\n\n";

		int gemCount = inventory->gems.size();
		for (int i = 0; i < gemCount; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			inventory->gems[i]->PrintGemInfo();
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ���" << endl;
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
			//������ ���� ����ȭ��
			while (true)
			{
				system("cls");
				int weaponSize = inventory->weapons.size();
				if (0 == weaponSize)
				{
					cout << "���� ���� ������ �� ���� ���Ⱑ �����ϴ�. (�������� ����� ���� ������ �� �����ϴ�)" << endl;
					system("pause");
					break;
				}

				for (int i = 0; i < weaponSize; ++i)
				{
					cout << "<" << i + 1 << "��>" << endl;
					inventory->weapons[i]->printWeaponInfo();
					cout << "\n\n";
				}

				cout << "0. ������ �����۹�ȣ. ���" << endl;
				unsigned int weaponSelection;
				cin >> weaponSelection;

				if (0 == weaponSelection)
				{
					break;
				}
				else if (weaponSelection <= inventory->weapons.size())
				{
					//���⿡ �� �����ϱ�
					CWeapon* weapon = inventory->weapons[weaponSelection - 1];
					CBufItem* gem = inventory->gems[gemSelection - 1];
					weapon->attack += gem->attackBuf;
					weapon->element = gem->element;
					character->maxHealth += gem->maxHealthBuf;
					character->currExp += gem->expBuf;
					//���� ������ ��ü
					if (weapon->gem)
					{
						inventory->gems.push_back(weapon->gem);

					}
					//���⿡ �� ����
					weapon->gem = gem;
					//�κ��丮���� �� ����
					inventory->gems.erase(inventory->gems.begin() + gemSelection - 1);
					cout << "�� ���� �Ϸ�!" << endl;
				}
			}
		}
	}
}
