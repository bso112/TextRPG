#include "stdafx.h"
#include "MainGame.h"
#include <time.h>


void CMainGame::Initalize()
{
	character = nullptr;
	factory.Initialize();
	inventoryMgr.Initialize(character);

}

void CMainGame::Progress()
{
	//âũ��
	system("mode con cols=91");

	srand(unsigned(time(NULL)));


	CParser parser;

	//ĳ���� ����ȭ��
	while (true)
	{

		system("cls");
		//�ΰ� ���
		parser.PrintFile("../GFX/logo.txt");

		cout << "0.������ 1.���� 2.������ 3.���� 4.�ε�" << endl;

		int characterToCreate;
		cin >> characterToCreate;

		//����
		if (characterToCreate == 0)
		{
			Release();
			_CrtDumpMemoryLeaks(); // �޸𸮴��� üũ
			return;
		}
		//���̺� �����ͷε�
		if (characterToCreate == 4)
		{
			character = character->Load();
			if (character == nullptr)
			{
				system("pause");
				continue;
			}
		}
		else
		{
			//ĳ���ʹ� ���ý� �ѹ� ����
			character = new CCharacter;
			(*character).CreateCharacter(characterToCreate);


		}

		//ĳ������ �ൿ���� ȭ��
		while (true)
		{

			system("cls");
			//ĳ���� ���� ���
			character->PrintCharacter();

			cout << "================================================" << endl;

			cout << "0. ������ 1. �ʱ޴��� 2. �߱޴��� 3. ��޴��� 4. ���尣  5. ������ 6. �κ��丮 900. ���̺�" << endl;

			//��� �� ���ΰ�?
			int destiantion;
			cin >> destiantion;


			if (destiantion == 0)
			{
				Release();
				_CrtDumpMemoryLeaks(); // �޸𸮴��� üũ
				return;
			}
			else if (destiantion == 900)
			{
				character->Save(character);
			}
			//��������
			else if (destiantion > 0 && destiantion <= 3)
			{
				EnterDungeon((HABITAT)destiantion);
			}
			//���尣 ����
			else if (destiantion == 4)
			{

				EnterForge();

			}
			else if (destiantion == 5)
			{
				EnterPharmacy();
			}
			else if (destiantion == 6)
			{
				inventoryMgr.Process();
			}
			else
				cout << "�߸��� �Է��Դϴ�" << endl;

		}
	}
}

void CMainGame::Release()
{
	if (character != nullptr)
	{
		delete character->inventory.currWeapon;
		int potionSize = character->inventory.potions.size();
		for (int i = 0; i < potionSize; ++i)
		{
			delete character->inventory.potions[i];
		}
		int weaponSize = character->inventory.weapons.size();
		for (int i = 0; i < weaponSize; ++i)
		{
			delete character->inventory.weapons[i];
		}
		int bufItemSize = character->inventory.gems.size();
		for (int i = 0; i < bufItemSize; ++i)
		{
			delete character->inventory.gems[i];
		}
		delete character;
	}

	factory.Release();
	inventoryMgr.Release();

	cout << "������ �����մϴ�." << endl;
}


void CMainGame::EnterPharmacy()
{


	while (true)
	{
		system("cls");
		cout << "���� ���� ��������!" << endl;
		cout << "\n\n\n";

		int potionCnt = potionCnt;
		CPotion* potions = factory.potions;

		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			potions[i].printPotionInfo();
		}

		cout << "�ܾ�: " << character->gold << endl;
		cout << "\n\n";
		cout << "0. ������" << endl;
		int itemSelect = 0;
		cin >> itemSelect;

		if (itemSelect == 0)
		{
			break;
		}
		if (itemSelect <0 || itemSelect > potionCnt)
		{
			cout << "�߸��� �Է��Դϴ�" << endl;
			system("pause");

		}
		//�߸��� �Է��� �ƴϸ�
		//1 1
		else
		{
			if (character->gold >= potions[itemSelect - 1].price)
			{
				CPotion* potion = factory.CreatePotion(itemSelect);
				//�÷��̾� �κ��丮�� ���ǳֱ�
				character->inventory.potions.push_back(potion);
				character->gold -= potion->price;
				cout << potion->name << "�� �����Ͽ����ϴ�!" << endl;
			}
			else
				cout << "���� �����մϴ�!" << endl;

			system("pause");
		}

	}

}

void CMainGame::EnterForge()
{

	while (true)
	{
		system("cls");

		cout << "�ְ��� ���Ⱑ ���ֽ��ϴ�." << endl;
		cout << "\n\n\n";

		int weaponsCount = factory.weaponCnt;
		CWeapon* weapons = factory.weapons;
		for (int i = 0; i < weaponsCount; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			weapons[i].printWeaponInfo();
		}

		cout << "�ܾ�: " << character->gold << endl;
		cout << "\n\n";
		cout << "0. ������ �׸��ȣ. �����ϱ� 999. ��ȭ�ϱ�" << '\n';
		int itemSelect = 0;
		cin >> itemSelect;

		if (0 == itemSelect)
		{
			break;
		}
		else if (999 == itemSelect)
		{
			EnhanceWeaponPage();

		}
		else if (itemSelect <0 || itemSelect > weaponsCount)
		{
			cout << "�߸��� �Է��Դϴ�" << endl;
			system("pause");

		}
		//�߸��� �Է��� �ƴϸ�
		else
		{
			CWeapon weaponToBuy = weapons[itemSelect - 1];
			if (character->occupation != weaponToBuy.occupation)
			{
				cout << "������ �� ���� Ŭ������ �����Դϴ�!" << endl;
				system("pause");
				continue;

			}


			if (character->gold >= weapons[itemSelect - 1].price)
			{

				CWeapon* weapon = factory.CreateWeapon(itemSelect);
				cout << weapon->name << "��(��) �����Ͽ����ϴ�!" << endl;

				////�÷��̾ ���⸦ �������� �ʾ����� �ٷ� �����Ѵ�.
				//if (character->weapon->id == 0)
				//{
				//	//�󲮵��� ����
				//	delete character->weapon;
				//	character->weapon = weapon;
				//	character->attack += character->weapon->attack;
				//}

				//�κ��丮�� �ִ´�.
				character->inventory.weapons.push_back(weapon);
				character->gold -= weapon->price;
			}
			else
				cout << "���� �����մϴ�!" << endl;

			system("pause");
		}


	}
}


void CMainGame::EnterDungeon(HABITAT habitat)
{
	int monsterCnt = factory.monsterCnt;

	CMonster* monster = factory.CreateMonster(monsterCnt, habitat);
	
	COMBAT combat = Battle(character, monster);
	//����
	if (COMBAR_RUN == combat)
	{
		character->currExp -= monster->exp;
		character->gold -= monster->gold;
		character->currExp = character->currExp < 0 ? 0 : character->currExp;
		character->gold = character->gold < 0 ? 0 : character->gold;
		delete monster;
	}
	else if (COMBAT_WIN == combat)
	{

		character->currExp += monster->exp;
		character->gold += monster->gold;
		character->OnGetExp();
		cout << "��ɿ� �����߽��ϴ�!" << '\n' << monster->gold << " ��带 ������ϴ�." << endl;
		cout << monster->exp << "��ŭ�� ����ġ�� ������ϴ�!" << endl;

		//������ ���. ��� ���ʹ� 30������ Ȯ���� �������� ����Ѵ�.
		int random = rand() % 100;
		int dropChance = 30;
		if (random <= dropChance)
		{

			CBufItem* dropItem = factory.CreateDropItem();
			character->inventory.gems.push_back(dropItem);
			cout << dropItem->name << "��(��) ������ϴ�!" << endl;
		}



		delete monster;
		monster = nullptr;

		system("pause");
	}
	else if (combat == COMBAT_LOSE)
	{
		cout << "�÷��̾� ���!" << endl;
		character->currHealth = character->maxHealth;
		character->currExp >>= 1;
		character->gold >>= 1;
		character->currHealth = character->currHealth < 0 ? 0 : character->currHealth;
		character->currExp = character->currExp < 0 ? 0 : character->currExp;
		character->gold = character->gold < 0 ? 0 : character->gold;


		system("pause");
	}

}

void CMainGame::EnhanceWeaponPage()
{
	while (true)
	{

		system("cls");

		cout << "���� �κ��丮" << "\n\n";

		cout << "<������> " << endl;
		cout << "���������� ����� ��ȭ�� �Ұ��մϴ�." << endl;
		character->inventory.currWeapon->printWeaponInfo();
		cout << "\n\n";

		int weaponCnt = character->inventory.weapons.size();
		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			character->inventory.weapons[i]->printWeaponInfo();
			cout << "��ȭȮ��: " << BASE_ENHANCE_CHANCE - (character->inventory.weapons[i]->level * 5.2f) << endl;
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ��ȭ�ϱ�" << endl;
		unsigned int selection;
		cin >> selection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == selection)
		{
			return;
		}
		//�׸� ��ȣ�� ����� �Է�������
		else if (selection <= character->inventory.weapons.size())
		{
			//��ȭ��
			int cost = character->inventory.weapons[selection - 1]->price / 5;
			//���� ����ϸ�
			if (character->gold >= cost)
			{
				character->gold -= cost;
				//��ȭ�õ�
				character->inventory.weapons[selection - 1]->EnhanceWeapon();
			}
		}
	}
}




COMBAT CMainGame::Battle(CCharacter* character, CMonster* monster)
{
	while (true)
	{
		system("cls");
		character->PrintCharacter();
		cout << "================================================" << endl;

		monster->PrintMonster();

		cout << "================================================" << endl;
		cout << "1. ���� 2. ����" << endl;

		int iSelect_Behavior;
		cin >> iSelect_Behavior;

		if (2 == iSelect_Behavior)
		{
			return COMBAR_RUN;
		}

		ELEMENT element = character->inventory.currWeapon->element;

		int characterAttack = character->attack;
		int monsterAttack = monster->attack;

		if (NONE != element)
		{
			int result = element - monster->element;

			//�� Ȯ��

			if (1 == result || -3 == result)
			{
				//��
				characterAttack *= 2;
			}
			else if (-1 == result || 3 == result)
			{
				//��
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