
#include "TextRPG.h"


void main()
{
	//창크기
	system("mode con cols=91");


	srand(unsigned(time(NULL)));

	CFactory factory;
	CParser parser;
	//플레이어 캐릭터
	CCharacter* character = nullptr;

	CShop shop;

	//캐릭터 생성화면
	while (true)
	{

		system("cls");
		//로고 출력
		parser.PrintFile("../GFX/logo.txt");

		cout << "0.나가기 1.전사 2.마법사 3.도적 4.로드" << endl;

		int characterToCreate;
		cin >> characterToCreate;

		character = nullptr;

		//종료
		if (characterToCreate == 0)
		{
			factory.FinalizeGame(character);
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
				factory.FinalizeGame(character);
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
				EnterDungeon(character, factory, (HABITAT)destiantion, characterToCreate);
			}
			//대장간 진입
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
				cout << "잘못된 입력입니다" << endl;


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

			CBufItem* dropItem = factory.CreateDropItem(itemCnt);
			character->inventory->gems.push_back(dropItem);
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











