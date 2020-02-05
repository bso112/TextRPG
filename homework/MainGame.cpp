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
	//창크기
	system("mode con cols=91");

	srand(unsigned(time(NULL)));


	CParser parser;

	//캐릭터 생성화면
	while (true)
	{

		system("cls");
		//로고 출력
		parser.PrintFile("../GFX/logo.txt");

		cout << "0.나가기 1.전사 2.마법사 3.도적 4.로드" << endl;

		int characterToCreate;
		cin >> characterToCreate;

		//종료
		if (characterToCreate == 0)
		{
			Release();
			_CrtDumpMemoryLeaks(); // 메모리누수 체크
			return;
		}
		//세이브 데이터로드
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
			//캐릭터는 선택시 한번 생성
			character = new CCharacter;
			(*character).CreateCharacter(characterToCreate);


		}

		//캐릭터의 행동선택 화면
		while (true)
		{

			system("cls");
			//캐릭터 정보 출력
			character->PrintCharacter();

			cout << "================================================" << endl;

			cout << "0. 나가기 1. 초급던전 2. 중급던전 3. 고급던전 4. 대장간  5. 힐러집 6. 인벤토리 900. 세이브" << endl;

			//어디를 갈 것인가?
			int destiantion;
			cin >> destiantion;


			if (destiantion == 0)
			{
				Release();
				_CrtDumpMemoryLeaks(); // 메모리누수 체크
				return;
			}
			else if (destiantion == 900)
			{
				character->Save(character);
			}
			//던전진입
			else if (destiantion > 0 && destiantion <= 3)
			{
				EnterDungeon((HABITAT)destiantion);
			}
			//대장간 진입
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
				cout << "잘못된 입력입니다" << endl;

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

	cout << "게임을 종료합니다." << endl;
}


void CMainGame::EnterPharmacy()
{


	while (true)
	{
		system("cls");
		cout << "좋은 포션 보고가세요!" << endl;
		cout << "\n\n\n";

		int potionCnt = potionCnt;
		CPotion* potions = factory.potions;

		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			potions[i].printPotionInfo();
		}

		cout << "잔액: " << character->gold << endl;
		cout << "\n\n";
		cout << "0. 나가기" << endl;
		int itemSelect = 0;
		cin >> itemSelect;

		if (itemSelect == 0)
		{
			break;
		}
		if (itemSelect <0 || itemSelect > potionCnt)
		{
			cout << "잘못된 입력입니다" << endl;
			system("pause");

		}
		//잘못된 입력이 아니면
		//1 1
		else
		{
			if (character->gold >= potions[itemSelect - 1].price)
			{
				CPotion* potion = factory.CreatePotion(itemSelect);
				//플레이어 인벤토리에 포션넣기
				character->inventory.potions.push_back(potion);
				character->gold -= potion->price;
				cout << potion->name << "을 구입하였습니다!" << endl;
			}
			else
				cout << "돈이 부족합니다!" << endl;

			system("pause");
		}

	}

}

void CMainGame::EnterForge()
{

	while (true)
	{
		system("cls");

		cout << "최고의 무기가 모여있습니다." << endl;
		cout << "\n\n\n";

		int weaponsCount = factory.weaponCnt;
		CWeapon* weapons = factory.weapons;
		for (int i = 0; i < weaponsCount; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			weapons[i].printWeaponInfo();
		}

		cout << "잔액: " << character->gold << endl;
		cout << "\n\n";
		cout << "0. 나가기 항목번호. 구입하기 999. 강화하기" << '\n';
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
			cout << "잘못된 입력입니다" << endl;
			system("pause");

		}
		//잘못된 입력이 아니면
		else
		{
			CWeapon weaponToBuy = weapons[itemSelect - 1];
			if (character->occupation != weaponToBuy.occupation)
			{
				cout << "착용할 수 없는 클래스의 무기입니다!" << endl;
				system("pause");
				continue;

			}


			if (character->gold >= weapons[itemSelect - 1].price)
			{

				CWeapon* weapon = factory.CreateWeapon(itemSelect);
				cout << weapon->name << "을(를) 구입하였습니다!" << endl;

				////플레이어가 무기를 장착하지 않았으면 바로 장착한다.
				//if (character->weapon->id == 0)
				//{
				//	//빈껍데기 제거
				//	delete character->weapon;
				//	character->weapon = weapon;
				//	character->attack += character->weapon->attack;
				//}

				//인벤토리에 넣는다.
				character->inventory.weapons.push_back(weapon);
				character->gold -= weapon->price;
			}
			else
				cout << "돈이 부족합니다!" << endl;

			system("pause");
		}


	}
}


void CMainGame::EnterDungeon(HABITAT habitat)
{
	int monsterCnt = factory.monsterCnt;

	CMonster* monster = factory.CreateMonster(monsterCnt, habitat);
	
	COMBAT combat = Battle(character, monster);
	//도망
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
		cout << "사냥에 성공했습니다!" << '\n' << monster->gold << " 골드를 얻었습니다." << endl;
		cout << monster->exp << "만큼의 경험치를 얻었습니다!" << endl;

		//아이템 드롭. 모든 몬스터는 30프로의 확률로 아이템을 드롭한다.
		int random = rand() % 100;
		int dropChance = 30;
		if (random <= dropChance)
		{

			CBufItem* dropItem = factory.CreateDropItem();
			character->inventory.gems.push_back(dropItem);
			cout << dropItem->name << "을(를) 얻었습니다!" << endl;
		}



		delete monster;
		monster = nullptr;

		system("pause");
	}
	else if (combat == COMBAT_LOSE)
	{
		cout << "플레이어 사망!" << endl;
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

		cout << "무기 인벤토리" << "\n\n";

		cout << "<장착중> " << endl;
		cout << "※장착중인 무기는 강화가 불가합니다." << endl;
		character->inventory.currWeapon->printWeaponInfo();
		cout << "\n\n";

		int weaponCnt = character->inventory.weapons.size();
		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			character->inventory.weapons[i]->printWeaponInfo();
			cout << "강화확률: " << BASE_ENHANCE_CHANCE - (character->inventory.weapons[i]->level * 5.2f) << endl;
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
		else if (selection <= character->inventory.weapons.size())
		{
			//강화비
			int cost = character->inventory.weapons[selection - 1]->price / 5;
			//돈이 충분하면
			if (character->gold >= cost)
			{
				character->gold -= cost;
				//강화시도
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
		cout << "1. 공격 2. 도망" << endl;

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

			//상성 확인

			if (1 == result || -3 == result)
			{
				//승
				characterAttack *= 2;
			}
			else if (-1 == result || 3 == result)
			{
				//패
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