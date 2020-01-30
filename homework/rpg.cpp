#include "TextRPG.h"


void main()
{
	//창크기
	system("mode con cols=91");

	srand(unsigned(time(NULL)));

	//아이템 정보를 담은 일차원 배열
	WEAPON* weapons = nullptr;
	//처음에 모든 무기 만들어둠
	int weaponsCount = CreateAllWeapons(&weapons);

	//모든 몬스터를 만들어둠
	MONSTER* monsters = nullptr;
	int monsterCount = CreateAllMonsters(&monsters);

	POTION* potions = nullptr;
	int potionCount = CreateAllPotions(&potions);

	//플레이어 캐릭터
	CHARACTER* character = nullptr;

	//캐릭터 생성화면
	while (true)
	{

		system("cls");
		//로고 출력
		printFile("../GFX/logo.txt");

		cout << "0.로드 1.전사 2.마법사 3.도적 4.나가기" << endl;

		int characterToCreate;
		cin >> characterToCreate;

		CHARACTER* character = nullptr;

		//종료
		if (characterToCreate == 4)
		{
			FinalizeGame(character, weapons, potions);
			return;
		}
		//세이브 데이터로드
		if (characterToCreate == 0)
		{
			character = Load();
			if (character == nullptr)
			{
				system("pause");
				continue;
			}
		}
		else
		{
			//캐릭터는 선택시 한번 생성
			character = CreateCharacter(characterToCreate);

#ifdef _DEBUG
			character->gold = 1000;
#endif
		}

		//캐릭터의 행동선택 화면
		while (true)
		{

			system("cls");
			//캐릭터 정보 출력
			PrintCharacter(character);

			cout << "================================================" << endl;

			cout << "0. 세이브 1. 초급던전 2. 중급던전 3. 고급던전 4. 대장간  5. 힐러집 6. 인벤토리 900. 나가기" << endl;

			//어디를 갈 것인가?
			int destiantion;
			cin >> destiantion;


			if (destiantion == 0)
			{
				Save(character);
			}
			else if (destiantion == 900)
			{
				FinalizeGame(character, weapons, potions);

				return;
			}
			//던전진입
			else if (destiantion > 0 && destiantion <= 3)
			{
				EnterDungeon(&character, monsters, monsterCount, (eHabitat)destiantion, characterToCreate);
			}
			//대장간 진입
			else if (destiantion == 4)
			{
				EnterForge(character, weapons, weaponsCount);

			}
			else if (destiantion == 5)
			{
				EnterHealersHouse(potions, potionCount, character);
			}
			else if (destiantion == 6)
			{
				ShowInventory(character);
			}
			else
				cout << "잘못된 입력입니다" << endl;


		}
	}



}


void eOccupationToString(eOccupation occupation, char result[16])
{
	switch (occupation)
	{
	case WARRIOR:
		strcpy_s(result, 16, "warrior");
		break;
	case WIZARD:
		strcpy_s(result, 16, "wizard");
		break;
	case THIEF:
		strcpy_s(result, 16, "thief");
		break;
	default:
		cout << "없는 직업입니다." << endl;
		break;
	}


}

void EnterHealersHouse(POTION* potions, int potionCount, CHARACTER* character)
{
	while (true)
	{
		system("cls");
		cout << "좋은 포션 보고가세요!" << endl;
		cout << "잔액: " << character->gold << endl;
		cout << '\n' << "0. 나가기" << endl;
		for (int i = 0; i < potionCount; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			printPotionInfo(potions[i]);
			cout << "\n\n";
		}

		int itemSelect = 0;
		cin >> itemSelect;

		if (itemSelect == 0)
		{
			break;
		}
		if (itemSelect <0 || itemSelect > potionCount)
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
				POTION* potion = CreatePotion(potions, itemSelect);
				//플레이어 인벤토리에 포션넣기
				character->inventory->potions.push_back(potion);
				character->gold -= potion->price;
				cout << potion->name << "을 구입하였습니다!" << endl;
			}
			else
				cout << "돈이 부족합니다!" << endl;
			
			system("pause");
		}

	}

}

void EnterDungeon(CHARACTER** character, MONSTER monsters[], int monsterCnt, eHabitat habitat, int characterSelection)
{
	MONSTER* monster = CreateMonster(monsters, monsterCnt, habitat);

	while (true)
	{

		system("cls");
		PrintCharacter(*character);
		cout << "================================================" << endl;
		PrintMonster(monster);
		cout << "================================================" << endl;
		cout << "1. 공격 2. 도망" << endl;

		int iSelect_Behavior;
		cin >> iSelect_Behavior;

		//도망
		if (iSelect_Behavior == 2)
		{
			delete monster;
			break;
		}
		//공격
		if (iSelect_Behavior == 1)
		{
			monster->currHealth -= (*character)->attack;
			(*character)->currHealth -= monster->attack;


			if (monster->currHealth <= 0 && (*character)->currHealth <= 0)
			{
				cout << "사냥에 성공했지만 플레이어도 죽었습니다!" << endl;
				(*character)->currExp += monster->exp;
				OnGetExp(*character);
				delete monster;
				monster = nullptr;
				OnCharacterDie(*character);
				//캐릭터 리스폰
				*character = CreateCharacter(characterSelection);
				system("pause");
				break;

			}
			else
			{
				if (monster->currHealth <= 0)
				{
					cout << "사냥에 성공했습니다!" << '\n' << monster->gold << " 골드를 얻었습니다." << endl;
					(*character)->currExp += monster->exp;
					(*character)->gold += monster->gold;
					OnGetExp(*character);

					delete monster;
					monster = nullptr;

					system("pause");
					break;
				}
				if ((*character)->currHealth <= 0)
				{
					cout << "플레이어 사망!" << endl;

					OnCharacterDie(*character);
					//캐릭터 리스폰
					*character = CreateCharacter(characterSelection);
					system("pause");
					break;
				}
			}

		}
	}
}
void EnterForge(CHARACTER* character, WEAPON* weapons, int weaponsCount)
{
	while (true)
	{
		system("cls");

		cout << "최고의 무기가 모여있습니다." << endl;
		cout << "잔액: " << character->gold << endl;

		cout << '\n' << "0. 나가기" << endl;

		for (int i = 0; i < weaponsCount; ++i)
		{
			printWeaponInfo(weapons[i]);
		}


		int itemSelect = 0;
		cin >> itemSelect;

		if (itemSelect == 0)
		{
			break;
		}
		if (itemSelect <0 || itemSelect > weaponsCount)
		{
			cout << "잘못된 입력입니다" << endl;
			system("pause");

		}
		//잘못된 입력이 아니면
		else
		{
			WEAPON weaponToBuy = weapons[itemSelect - 1];
			if (character->occupation != weaponToBuy.occupation)
			{
				cout << "착용할 수 없는 클래스의 무기입니다!" << endl;
				system("pause");
				continue;

			}


			if (character->gold >= weapons[itemSelect - 1].price)
			{
				WEAPON* weapon = CreateWeapon(weapons, itemSelect);
				cout << weapon->name << "을(를) 구입하였습니다!" << endl;

				delete character->weapon;

				character->weapon = weapon;
				character->attack += character->weapon->attack;
				character->gold -= weapon->price;
			}
			else
				cout << "돈이 부족합니다!" << endl;

			system("pause");
		}


	}
}

void Save(CHARACTER* character)
{
	FILE* fp;
	//파일 스트림 생성
	errno_t err = fopen_s(&fp, "../Save/save1.txt", "wb");

	if (0 == err)
	{
		//캐릭터 정보 저장
		fwrite(character, sizeof(CHARACTER), 1, fp);
		//파일 포인터 이동
		//fseek(fp, sizeof(CHARACTER), SEEK_SET);
		//무기정보 저장
		fwrite(character->weapon, sizeof(WEAPON), 1, fp);
		fclose(fp);
		cout << "세이브성공!" << endl;
		system("pause");
	}
	else
		cout << "세이브 실패! 파일을 저장할 수 없습니다." << endl;
}

CHARACTER* Load()
{
	WEAPON* weapon = new WEAPON;
	*weapon = {};
	CHARACTER* character = new CHARACTER;
	*character = {};
	FILE* fp;
	errno_t err = fopen_s(&fp, "../Save/save1.txt", "rb");
	if (0 == err)
	{
		//캐릭터 정보 읽어오기
		fread(character, sizeof(CHARACTER), 1, fp);
		//파일 포인터 이동
		//fseek(fp, sizeof(CHARACTER), SEEK_SET);
		//무기정보 가져오기
		fread(weapon, sizeof(WEAPON), 1, fp);
		fclose(fp);
		//캐릭터 무기 설정하기
		character->weapon = weapon;
		cout << "로드 성공!" << endl;
		system("pause");
		return character;

	}
	else
		cout << "로드 실패! 파일을 가져올 수 없습니다." << endl;

	return nullptr;
}

WEAPON* CreateWeapon(WEAPON weapons[], int id)
{
	WEAPON* weapon = new WEAPON;
	memcpy(weapon, &(weapons[id - 1]), sizeof(WEAPON));
	return weapon;

}

int CreateAllWeapons(WEAPON** weapons)
{

	//무기에 대한 정보를 받을 이차원배열 포인터를 준비한다.
	char(*weaponInfos)[CHAR_PER_LINE] = nullptr;

	//무기정보를 동적으로 할당받는다.
	int itemCount = GetInfo(&weaponInfos, "../Data/weapon.txt");

	*weapons = new WEAPON[itemCount];


	//쉼표로 끊으면서 무기 구조체에 대한 정보 셋팅
	for (int i = 0; i < itemCount; ++i)
	{
		//word의 행,열
		int col = 0, row = 0;
		//하나의 무기 구조체에 대한 정보.
		//description 항목때문에 모든 항목을 800개의 방으로 잡았다. 비효율적임. 개선 필요
		char word[7][DESCRIPTION_LENGTH] = {};

		int len = strlen(weaponInfos[i]);

		//쉼표단위로 파싱하기
		for (int j = 0; j < len; ++j)
		{
			//word의 경계값을 넘어가면 무시
			if (col > 6 || row > DESCRIPTION_LENGTH-1)
			{
				continue;
			}
			//쉼표면 word의 다음 행을 채운다.
			if (',' == weaponInfos[i][j])
			{
				++col;
				row = 0;
			}
			//개행문자면 빠져나간다.
			else if ('\n' == weaponInfos[i][j])
			{
				break;
			}
			//이 모든게 아니면 데이터를 word 에 넣는다.
			else
			{
				word[col][row] = weaponInfos[i][j];
				++row;
			}
		}

		(*weapons)[i].id = StringToInt(word[0]);
		strcpy_s((*weapons)[i].GFX_PATH, GFX_PATH_LENGTH, word[1]);
		strcpy_s((*weapons)[i].name, 16, word[2]);
		(*weapons)[i].attack = StringToInt(word[3]);
		strcpy_s((*weapons)[i].description, DESCRIPTION_LENGTH, word[4]);
		(*weapons)[i].price = StringToInt(word[5]);
		(*weapons)[i].occupation = (eOccupation)StringToInt(word[6]);
	}

	delete[] weaponInfos;
	weaponInfos = nullptr;

	return itemCount;
}

int CreateAllMonsters(MONSTER** monsters)
{

	//무기에 대한 정보를 받을 이차원배열 포인터를 준비한다.
	char(*monsterInfos)[CHAR_PER_LINE] = nullptr;

	//무기정보를 동적으로 할당받는다.
	int itemCount = GetInfo(&monsterInfos, "../Data/monster.txt");
	*monsters = new MONSTER[itemCount];


	//쉼표로 끊으면서 무기 구조체에 대한 정보 셋팅
	for (int i = 0; i < itemCount; ++i)
	{
		//word의 행,열
		int col = 0, row = 0;
		//하나의 무기 구조체에 대한 정보.
		//description 항목때문에 모든 항목을 800개의 방으로 잡았다. 비효율적임. 개선 필요
		char word[10][DESCRIPTION_LENGTH] = {};

		int len = strlen(monsterInfos[i]);

		//쉼표단위로 파싱하기
		for (int j = 0; j < len; ++j)
		{
			//word의 경계값을 넘어가면 무시
			if (col > 9 || row > DESCRIPTION_LENGTH-1)
			{
				continue;
			}
			//쉼표면 word의 다음 행을 채운다.
			if (',' == monsterInfos[i][j])
			{
				++col;
				row = 0;
			}
			//개행문자면 빠져나간다.
			else if ('\n' == monsterInfos[i][j])
			{
				break;
			}
			//이 모든게 아니면 데이터를 word 에 넣는다.
			else
			{
				word[col][row] = monsterInfos[i][j];
				++row;
			}
		}

		(*monsters)[i].id = StringToInt(word[0]);
		strcpy_s((*monsters)[i].name, ITEM_NAME_LENGTH, word[1]);
		strcpy_s((*monsters)[i].GFX_PATH, GFX_PATH_LENGTH, word[2]);
		(*monsters)[i].attack = StringToInt(word[3]);
		(*monsters)[i].maxHealth = StringToInt(word[4]);
		(*monsters)[i].currHealth = StringToInt(word[5]);
		(*monsters)[i].exp = StringToInt(word[6]);
		(*monsters)[i].gold = StringToInt(word[7]);
		(*monsters)[i].habitat = (eHabitat)StringToInt(word[8]);
		(*monsters)[i].spawnChance = StringToFloat(word[9]);
		//PrintMonster(*(monsters)[i]);

	}

	delete[] monsterInfos;
	monsterInfos = nullptr;

	return itemCount;
}

int CreateAllPotions(POTION** potions)
{

	//무기에 대한 정보를 받을 이차원배열 포인터를 준비한다.
	char(*potionInfos)[CHAR_PER_LINE] = nullptr;

	//무기정보를 동적으로 할당받는다.
	int itemCount = GetInfo(&potionInfos, "../Data/potion.txt");
	*potions = new POTION[itemCount];


	//쉼표로 끊으면서 무기 구조체에 대한 정보 셋팅
	for (int i = 0; i < itemCount; ++i)
	{
		//word의 행,열
		int col = 0, row = 0;
		//하나의 무기 구조체에 대한 정보.
		//description 항목때문에 모든 항목을 800개의 방으로 잡았다. 비효율적임. 개선 필요
		char word[7][800] = {};

		int len = strlen(potionInfos[i]);

		//쉼표단위로 파싱하기
		for (int j = 0; j < len; ++j)
		{
			//word의 경계값을 넘어가면 무시
			if (col > 6 || row > 799)
			{
				continue;
			}
			//쉼표면 word의 다음 행을 채운다.
			if (',' == potionInfos[i][j])
			{
				++col;
				row = 0;
			}
			//개행문자면 빠져나간다.
			else if ('\n' == potionInfos[i][j])
			{
				break;
			}
			//이 모든게 아니면 데이터를 word 에 넣는다.
			else
			{
				word[col][row] = potionInfos[i][j];
				++row;
			}
		}

		(*potions)[i].id = StringToInt(word[0]);
		strcpy_s((*potions)[i].GFX_PATH, GFX_PATH_LENGTH, word[1]);
		strcpy_s((*potions)[i].name, ITEM_NAME_LENGTH, word[2]);
		(*potions)[i].healAmount = StringToInt(word[3]);
		strcpy_s((*potions)[i].description, DESCRIPTION_LENGTH, word[4]);
		(*potions)[i].price = StringToInt(word[5]);
		(*potions)[i].sort = (ePotion)StringToInt(word[6]);

	}

	delete[] potionInfos;
	potionInfos = nullptr;

	return itemCount;
}

int StringToInt(const char arr[])
{
	//문자열->숫자 파싱
	int result = 0;
	int len = strlen(arr);

	for (int i = 0; i < len; ++i)
	{
		int tmp = arr[i] - '0';
		result += (int)(tmp * (pow((double)10, (double)len - i - 1)));
	}

	// 1  1 
	// 2  10
	// 3  100
	// 10의 0승은 1 
	//      1승은 10 ...

	return result;
}

float StringToFloat(const char arr[])
{
	//문자열->숫자 파싱
	float result = 0.0f;
	int totalLen = strlen(arr);

	//소수점 이상의 길이
	int overZeroLen = 0;

	for (int i = 0; i < totalLen; ++i)
	{
		if ('.' == arr[i])
		{
			break;
		}
		else
			++overZeroLen;
	}

	int below = -1;
	for (int i = 0; i < totalLen; ++i)
	{
		if (arr[i] == '.')
		{
			continue;
		}
		if (i < overZeroLen)
		{
			int tmp = arr[i] - '0';
			result += (int)(tmp * (pow((double)10, (double)overZeroLen - i - 1)));
		}
		else
		{
			int tmp = arr[i] - '0';
			result += (float)(tmp * pow((double)10, (double)below));
			--below;
		}

	}


	return result;
}

int GetInfo(char(**items)[CHAR_PER_LINE], char path[30])
{
	//아이템 목록에서 아이템의 수
	int itemCount = 0;

	FILE* fp = nullptr;

	errno_t err = fopen_s(&fp, path, "rt");
	if (0 == err)
	{
		//아이템 인덱스
		int col = 0;
		int row = 0;
		int c = 0;
		//정보를 읽어도 되나?
		bool infoStart = false;


		//파일이 끝날때까지 문자를 받아옴
		while (EOF != c)
		{

			//문자를 하나하나 가져옴
			c = getc(fp);

			if (EOF == c)
				continue;
			//주석 무시
			if ('*' == c)
			{
				//개행할때까지 읽는다.
				while ('\n' != c)
				{
					c = getc(fp);
				}
				//이제 다음 줄이지만 c는 여전히 '\n'이니 컨티뉴
				continue;
			}

			//첫행이면 총 아이템 수를 받아오고, 개행할때까지 무시
			if (col == 0 && !infoStart)
			{
				itemCount = c - '0';
				//아이템 정보를 저장할 배열 동적생성
				*items = new char[itemCount][CHAR_PER_LINE];

				//널문자로 초기화
				memset(*items, '\0', (sizeof(char) * CHAR_PER_LINE) * itemCount);
				while ('\n' != c)
				{
					c = getc(fp);
				}
				infoStart = true;
				continue;
			}

			//이제 아이템 정보 읽어오기 시작
			//개행할시 인덱스 초기화. 쉼표단위로 파싱할때 문장의 끝을 알리기 위해 개행문자도 넣는다.
			if ('\n' == c)
			{
				(*items)[col][row] = c;
				++col;
				row = 0;
			}
			//아니면 열을 증가시키며 받아온 문자 넣기. 
			else
			{
				(*items)[col][row] = c;
				++row;
			}

		}


		fclose(fp);

	}
	else
		cout << "파일 개방 실패!" << endl;



	return itemCount;

}

void printWeaponInfo(const WEAPON weapon)
{
	cout << '\n' << "==========================================" << endl;
	printFile(weapon.GFX_PATH);
	cout << '\n';
	cout << weapon.id << ". " << weapon.name << '\n';
	cout << "공격 : " << weapon.attack << '\n';
	cout << weapon.description << '\n';
	cout << "가격 : " << weapon.price << '\n';
	char occupation[16] = "";
	eOccupationToString(weapon.occupation, occupation);
	cout << "직업 : " << occupation << '\n';
}

void printWeaponInfo(const WEAPON* weapon)
{
	cout << '\n' << "==========================================" << endl;
	cout << weapon->id << '. ' << weapon->name << '\n';
	printFile(weapon->GFX_PATH);
	cout << '\n';
	cout << "공격 : " << weapon->attack << '\n';
	cout << weapon->description << '\n';
	cout << "가격 : " << weapon->price << '\n';
	cout << "직업 : " << weapon->occupation << '\n';
}

void printPotionInfo(const POTION potion)
{
	cout << "==========================================" << endl;
	printFile(potion.GFX_PATH);
	cout << '\n';
	cout << potion.name << '\n';
	cout << "회복량 : " << potion.healAmount << '\n';
	cout << potion.description << '\n';
	cout << "가격 : " << potion.price << '\n';
}

void OnGetExp(CHARACTER* character)
{
	if (character->currExp >= character->maxExp)
	{
		LevelUp(character);
	}
}

void LevelUp(CHARACTER* character)
{
	int weight = character->level / 3;
	weight = weight < 1 ? weight = 1 : weight;

	character->level += 1;
	character->maxHealth += 20 * weight;
	character->currHealth = character->maxHealth;
	character->attack += 5 * weight;
	character->maxExp += 20 * weight;
	character->currExp = 0;

}

void PrintMonster(const MONSTER* const monster)
{
	if (monster != nullptr)
	{
		if (strcmp(monster->GFX_PATH, "") != 0)
			printFile(monster->GFX_PATH);
		cout << '\n';
		cout << "이름: " << monster->name << endl;
		cout << "공격력: " << monster->attack << endl;
		cout << "체력: " << monster->currHealth << " / " << monster->maxHealth << endl;

	}

}

void PrintCharacter(const CHARACTER* const character)
{
	cout << "직업: " << character->name << endl;
	cout << "레벨: " << character->level << endl;
	cout << "공격력: " << character->attack << "(+" << character->weapon->attack << ")" << endl;
	cout << "체력: " << character->currHealth << " / " << character->maxHealth << endl;
	cout << "경험치: " << character->currExp << " / " << character->maxExp << endl;
	cout << "골드: " << character->gold << endl;
	cout << "장비: " << character->weapon->name << endl;

}


MONSTER* CreateMonster(MONSTER monsters[], int id)
{
	MONSTER* monster = new MONSTER;
	memcpy(monster, &(monsters[id - 1]), sizeof(MONSTER));
	return monster;

}

MONSTER* CreateMonster(MONSTER monsters[], int length, eHabitat habitat)
{

	//같은 서식지에 사는 몬스터들의 id. 최대 length(모든 몬스터의 수)만큼 있다.
	int* family = new int[length];
	float* spawnChance = new float[length];
	*family = {};
	*spawnChance = {};

	float chanceSum = 0;
	//family의 인덱스이자 +1은 family의 길이
	int index = 0;
	for (int i = 0; i < length; ++i)
	{
		if (monsters[i].habitat == habitat)
		{
			family[index] = monsters[i].id;
			spawnChance[index] = monsters[i].spawnChance;
			chanceSum += spawnChance[index];
			++index;
		}
	}


	//오름차순 정렬
	for (int i = 0; i < index; ++i)
	{
		for (int j = 0; j < index - 1 - i; ++j)
		{
			if (spawnChance[j] > spawnChance[j + 1])
			{
				float tmp = spawnChance[j + 1];
				spawnChance[j + 1] = spawnChance[j];
				spawnChance[j] = tmp;
				int tmp2 = family[j + 1];
				family[j + 1] = family[j];
				family[j] = tmp2;
			}
		}
	}


	// 확률로 나타나기

	//확률적으로 뽑은 숫자
	int randomNum = (rand() % (int)chanceSum) + 1;
	//누적확률
	float sum = 0.0f;
	int familyIndex = 0;
	for (int i = 0; i < index; ++i)
	{
		sum += spawnChance[i];
		if (sum >= randomNum)
		{
			familyIndex = i;
			break;
		}

	}

	//// index = 2
	//// 0 1 2 3
	//// 1 3
	//// family[0] family[1] 0 ~ index-1의 범위에서 랜덤으로 뽑은 아이디
	//int randomIndex = rand() % index;
	////랜덤으로 고른 몬스터의 아이디
	//int id = family[randomIndex];

	int idToSpawn = family[familyIndex];
	cout << "출현확률: " << (spawnChance[familyIndex] / chanceSum) * 100 << endl;
	system("pause");
	delete[] family;

	return CreateMonster(monsters, idToSpawn);

}

POTION* CreatePotion(POTION potions[], int id)
{
	POTION* potion = new POTION;
	memcpy(potion, &(potions[id - 1]), sizeof(POTION));
	return potion;

}



CHARACTER* CreateCharacter(int selection)
{
	CHARACTER* character;


	switch (selection)
	{
	case 1:
		character = new CHARACTER;
		strcpy_s(character->name, "전사");
		character->attack = 10;
		character->maxHealth = 200;
		character->maxExp = 50;
		character->occupation = WARRIOR;
		break;
	case 2:
		character = new CHARACTER;
		strcpy_s(character->name, "마법사");
		character->attack = 15;
		character->maxHealth = 80;
		character->maxExp = 50;
		character->occupation = WIZARD;
		break;
	case 3:
		character = new CHARACTER;
		strcpy_s(character->name, "도적");
		character->attack = 7;
		character->maxHealth = 150;
		character->maxExp = 50;
		character->occupation = THIEF;
		break;
	default:
		cout << "잘못된 입력입니다." << endl;
		return nullptr;
	}

	character->currHealth = character->maxHealth;
	character->currExp = 0;
	character->gold = 0;
	character->level = 1;
	//무기의 빈껍데기 만들어서 넣기
	character->weapon = new WEAPON;
	*(character->weapon) = {};
	strcpy_s(character->weapon->name, "미착용");
	character->inventory = new INVENTORY;
	*(character->inventory) = {};


	return character;
}

void printFile(const char path[30])
{
	FILE* fp;
	errno_t err = fopen_s(&fp, path, "rt");

	if (0 == err)
	{
		char ch = 0;
		while (true)
		{
			int cnt = fread(&ch, sizeof(char), 1, fp);
			if (1 > cnt)
				break;
			cout << ch;

		}
		fclose(fp);
		cout << '\n';
	}
	else
		cout << "파일을 열수 없습니다." << endl;

}

//포션을 사용하고 할당해제한다. nullptr로 바꾼다.
void UsePotion(CHARACTER* character, int potionIndex)
{
	POTION* potion = character->inventory->potions[potionIndex];
	character->currHealth += potion->healAmount;
	delete potion;
	character->inventory->potions.erase(character->inventory->potions.begin()+potionIndex);
}

void ShowInventory(CHARACTER* character)
{
	while (true)
	{
		system("cls");


		if (0 == GetInventorySize(*(character->inventory)))
		{

			cout << "인벤토리가 비었습니다!" << endl;
			system("pause");
			return;
		}
		//인벤토리에 아이템이 있으면
		else
		{
			cout << "인벤토리" << endl;


			cout << "0. 나가기 1.포션 2.무기" << endl;

			int whatBag = 0;
			cin >> whatBag;

			switch (whatBag)
			{
			case 0:
				return;
				break;
			case 1:
				ShowPotionBag(character);
			case 2:
				cout << "미구현" << endl;
			default:
				break;
			}


		}
	}

	
	
} 

void ShowPotionBag(CHARACTER* character)
{
	while (true)
	{	

		system("cls");

		cout << "포션 인벤토리" << "\n\n";

		int potionCnt = character->inventory->potions.size();
		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			printPotionInfo(*(character->inventory->potions[i]));
			cout << "\n\n";
		}


		cout << "0. 나가기 아이템번호. 사용" << endl;
		int selection;
		cin >> selection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == selection)
		{
			return;
		}
		else if (selection <= character->inventory->potions.size())
		{
			cout << character->inventory->potions[selection - 1]->name << "을 사용했다!" << endl;
			system("pause");
			UsePotion(character, selection-1);
		}
	}
}

void OnCharacterDie(CHARACTER* character)
{
	if (character != nullptr)
	{
		delete character->weapon;
		int potionSize = character->inventory->potions.size();
		for (int i = 0; i < potionSize; ++i)
		{
			delete character->inventory->potions[i];
		}
		delete character->inventory;
		delete character;
	}

}

void FinalizeGame(CHARACTER* character, WEAPON* weapons, POTION* potions)
{
	if (character != nullptr)
	{
		delete character->weapon;
		
		int potionSize = character->inventory->potions.size();
		for (int i = 0; i < potionSize; ++i)
		{
			delete character->inventory->potions[i];
		}
		delete character->inventory;
		delete character;
	}
	if (weapons != nullptr)
	{
		delete[] weapons;
	}
	if (potions != nullptr)
	{
		delete[] potions;
	}
	cout << "게임을 종료합니다." << endl;
}
int GetInventorySize(INVENTORY inventory)
{
	int size = inventory.potions.size();
	return size;
}
