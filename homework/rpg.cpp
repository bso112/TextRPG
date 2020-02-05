
#include "TextRPG.h"


void main()
{
	//âũ��
	system("mode con cols=91");


	srand(unsigned(time(NULL)));

	CFactory factory;
	CParser parser;
	//�÷��̾� ĳ����
	CCharacter* character = nullptr;

	CShop shop;

	//ĳ���� ����ȭ��
	while (true)
	{

		system("cls");
		//�ΰ� ���
		parser.PrintFile("../GFX/logo.txt");

		cout << "0.������ 1.���� 2.������ 3.���� 4.�ε�" << endl;

		int characterToCreate;
		cin >> characterToCreate;

		character = nullptr;

		//����
		if (characterToCreate == 0)
		{
			factory.FinalizeGame(character);
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
				factory.FinalizeGame(character);
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
				EnterDungeon(character, factory, (HABITAT)destiantion, characterToCreate);
			}
			//���尣 ����
			else if (destiantion == 4)
			{
				
				shop.EnterForge(character,factory);

			}
			else if (destiantion == 5)
			{
				shop.EnterPharmacy(character, factory);
			}
			else if (destiantion == 6)
			{
				character->inventory->ShowInventory(character);
			}
			else
				cout << "�߸��� �Է��Դϴ�" << endl;


		}
	}



}







void EnterDungeon(CCharacter* character, CFactory factory, HABITAT habitat, int characterSelection)
{
	CMonster* monsters;
	int monsterCnt = factory.GetMonters(&monsters);
	CMonster* monster = factory.CreateMonster(monsterCnt, habitat);

	CBufItem* items;
	int itemCnt = factory.GetBufItems(&items);
	
	BattleManager battleMgr;

	
	COMBAT combat = battleMgr.Battle(character, monster);
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

			CBufItem* dropItem = factory.CreateDropItem(itemCnt);
			character->inventory->gems.push_back(dropItem);
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











