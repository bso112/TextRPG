#include <iostream>
#include <math.h>


using namespace std;

typedef struct tagWeapon
{
	//아이템 아이디
	int id;
	char name[16];
	int attack;
	//아이템 설명. 
	char description[800];
	int price;
	//장착할 수 있는 직업
	char occupation[16];
}WEAPON;

typedef struct tagChracter
{
	char name[16];
	int attack;
	int maxHealth;
	int currHealth;
	int level;
	int maxExp;
	int currExp;
	int gold;
	WEAPON* weapon;

}CHARACTER;

typedef struct tagMonster
{
	char name[16];
	int attack;
	int maxHealth;
	int currHealth;
	int exp;
	int gold;
}MONSTER;

void PrintCharacter(const CHARACTER* const character);
CHARACTER* CreateCharacter(int selection);
void PrintMonster(const MONSTER* const monster);
MONSTER* CreateMonster(int selection);
void LevelUp(CHARACTER* characer);
void OnGetExp(CHARACTER* character);
void printWeaponInfo(const WEAPON weapon);
void printWeaponInfo(const WEAPON* weapon);
//텍스트파일에서 모든 아이템 정보를 가져와 2차원배열 포인터에 동적할당하고, 아이템의 갯수를 반환한다. 
//배열방이 1000개인 이유는 텍스트파일의 한 라인이 최대 1000개의 문자로 이루어진다고 가정했기 때문이다.
//아이템의 수를 리턴한다.
int GetWeaponInfo(char(**items)[1000]);
//텍스트파일의 모든 아이템을 생성한다. 아이템의 수를 리턴한다.
int CreateAllWeapons(WEAPON** weapons);
//아이템 아이디를 받아 하나의 아이템을 생성한다(동적할당). 모든 아이템을 가진 배열과 그 길이, 아이디를 인수로 받는다.
WEAPON* CreateWeapon(WEAPON weapons[], int length, int id);
//문자열을 int로 파싱한다.
int StringToInt(const char arr[]);


void main()
{


	//아이템 정보를 담은 일차원 배열
	WEAPON* weapons = nullptr;
	//처음에 모든 무기 만들어둠
	int weaponsCount = CreateAllWeapons(&weapons);

	//플레이어 캐릭터
	CHARACTER* character = nullptr;

	//캐릭터 생성화면
	while (true)
	{
		cout << "1.전사 2.마법사 3.도적 4.나가기" << endl;

		int iSelect_character;
		cin >> iSelect_character;

		//종료
		if (iSelect_character == 4)
		{
			if (character != nullptr)
			{
				delete character->weapon;
				delete character;
			}
			delete[] weapons;
			cout << "게임을 종료합니다." << endl;

			return;
		}

		//캐릭터는 선택시 한번 생성
		CHARACTER* character = CreateCharacter(iSelect_character);

		//캐릭터의 행동선택 화면
		while (true)
		{

			system("cls");
			PrintCharacter(character);

			cout << "================================================" << endl;

			cout << "1. 초급던전 2. 중급던전 3. 고급던전 4. 상점 5. 나가기" << endl;

			int iSelect_dungeon;
			cin >> iSelect_dungeon;

			if (iSelect_dungeon == 5)
			{
				cout << "게임을 종료합니다." << endl;
				if (character != nullptr)
				{
					delete character->weapon;
					delete character;
				}
				delete[] weapons;

				return;
			}

			//던전진입
			if (iSelect_dungeon <= 3)
			{
				//몬스터는 던전에 들어갈때 한번 생성
				MONSTER* monster = CreateMonster(iSelect_dungeon);
				//던전진입 화면
				while (true)
				{


					system("cls");
					PrintCharacter(character);
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
						system("cls");
						break;
					}
					//공격
					if (iSelect_Behavior == 1)
					{
						monster->currHealth -= character->attack;
						character->currHealth -= monster->attack;


						if (monster->currHealth <= 0 && character->currHealth <= 0)
						{
							cout << "사냥에 성공했지만 플레이어도 죽었습니다!" << endl;
							character->currExp += monster->exp;
							OnGetExp(character);
							delete monster;
							monster = nullptr;
							delete character;
							character = nullptr;
							//캐릭터 리스폰
							character = CreateCharacter(iSelect_character);
							system("pause");
							break;

						}
						else
						{
							if (monster->currHealth <= 0)
							{
								cout << "사냥에 성공했습니다!" << '\n' << monster->gold << " 골드를 얻었습니다." << endl;
								character->currExp += monster->exp;
								character->gold += monster->gold;
								OnGetExp(character);
								delete monster;
								monster = nullptr;
								system("pause");
								break;
							}
							if (character->currHealth <= 0)
							{
								cout << "플레이어 사망!" << endl;
								delete character;
								character = nullptr;
								//캐릭터 리스폰
								character = CreateCharacter(iSelect_character);
								system("pause");
								break;
							}
						}

					}
				}
			}

			//상점진입
			if (iSelect_dungeon == 4)
			{
				while (true)
				{
					system("cls");

					cout << "상점에 어서오세요!" << endl;
					cout << "잔액: " << character->gold << endl;

					cout << '\n' << "0. 나가기" << endl;

					for (int i = 0; i < weaponsCount; ++i)
					{
						printWeaponInfo(weapons[i]);
					}

					
					int itemSelect = 0;
					cin >> itemSelect;

					WEAPON* weapon = CreateWeapon(weapons, weaponsCount, itemSelect);


					if (character->gold >= weapon->price)
					{
						cout << weapon->name << "을(를) 구입하였습니다!" << endl;
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
	}

	

}

WEAPON* CreateWeapon(WEAPON weapons[], int length, int id)
{
	WEAPON* weapon = new WEAPON;
	memcpy(weapon, &(weapons[id - 1]), sizeof(WEAPON));
	return weapon;

}

int CreateAllWeapons(WEAPON** weapons)
{

	//무기에 대한 정보를 받을 이차원배열 포인터를 준비한다.
	char(*weaponInfos)[1000] = nullptr;

	//무기정보를 동적으로 할당받는다.
	int itemCount = GetWeaponInfo(&weaponInfos);

	*weapons = new WEAPON[itemCount];


	//쉼표로 끊으면서 무기 구조체에 대한 정보 셋팅
	for (int i = 0; i < itemCount; ++i)
	{
		//word의 행,열
		int col = 0, row = 0;
		//하나의 무기 구조체에 대한 정보.
		//description 항목때문에 모든 항목을 800개의 방으로 잡았다. 비효율적임. 개선 필요
		char word[6][800] = {};

		int len = strlen(weaponInfos[i]);

		//쉼표단위로 파싱하기
		for (int j = 0; j < len; ++j)
		{
			//word의 경계값을 넘어가면 무시
			if (col > 5 || row > 799)
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
		strcpy_s((*weapons)[i].name, 16, word[1]);
		(*weapons)[i].attack = StringToInt(word[2]);
		strcpy_s((*weapons)[i].description, 800, word[3]);
		(*weapons)[i].price = StringToInt(word[4]);
		strcpy_s((*weapons)[i].occupation, 16, word[5]);
	}

	delete[] weaponInfos;
	weaponInfos = nullptr;

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

int GetWeaponInfo(char(**items)[1000])
{
	//아이템 목록에서 아이템의 수
	int itemCount = 0;

	FILE* fp = nullptr;

	errno_t err = fopen_s(&fp, "../weapon.txt", "rt");
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
				*items = new char[itemCount][1000];

				//널문자로 초기화
				//for (int i = 0; i < itemCount; ++i)
				//{
				//	for (int j = 0; j < 1000; ++j)
				//	{
				//		(*items)[i][j] = '\0';
				//	}
				//}

				//널문자로 초기화
				memset(*items, '\0', (sizeof(char) * 1000) * itemCount);
				while ('\n' != c)
				{
					c = getc(fp);
				}
				//cout << "2"<< *items << endl;
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
	cout << '\n' << "==========================================" << '\n\n';
	cout << weapon.id << '. ' << weapon.name << '\n';
	cout << "공격 : " << weapon.attack << '\n';
	cout << weapon.description << '\n';
	cout << "가격 : " << weapon.price << '\n';
	cout << "직업 : " << weapon.occupation << '\n';
}

void printWeaponInfo(const WEAPON* weapon)
{
	cout << '\n' << "==========================================" << '\n\n';
	cout << weapon->id << '. ' << weapon->name << '\n';
	cout << "공격 : " << weapon->attack << '\n';
	cout << weapon->description << '\n';
	cout << "가격 : " << weapon->price << '\n';
	cout << "직업 : " << weapon->occupation << '\n';
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
	cout << "이름: " << monster->name << endl;
	cout << "공격력: " << monster->attack << endl;
	cout << "체력: " << monster->currHealth << " / " << monster->maxHealth << endl;
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


MONSTER* CreateMonster(int selection)
{
	MONSTER* monster = {};

	switch (selection)
	{
	case 1:
		monster = new MONSTER;
		strcpy_s(monster->name, "슬라임");
		monster->attack = 5;
		monster->maxHealth = 30;
		monster->currHealth = 30;
		monster->exp = 10;
		monster->gold = 10;
		break;
	case 2:
		monster = new MONSTER;
		strcpy_s(monster->name, "오우거");
		monster->attack = 15;
		monster->maxHealth = 60;
		monster->currHealth = 60;
		monster->exp = 30;
		monster->gold = 30;
		break;
	case 3:
		monster = new MONSTER;
		strcpy_s(monster->name, "골렘");
		monster->attack = 30;
		monster->maxHealth = 90;
		monster->currHealth = 90;
		monster->exp = 60;
		monster->gold = 60;
		break;
	default:
		cout << "잘못된 입력입니다." << endl;
	}

	return monster;
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
		break;
	case 2:
		character = new CHARACTER;
		strcpy_s(character->name, "마법사");
		character->attack = 15;
		character->maxHealth = 80;
		character->maxExp = 50;
		break;
	case 3:
		character = new CHARACTER;
		strcpy_s(character->name, "도적");
		character->attack = 7;
		character->maxHealth = 150;
		character->maxExp = 50;
		break;
	default:
		cout << "잘못된 입력입니다." << endl;
		return nullptr;
	}

	character->currHealth = character->maxHealth;
	character->currExp = 0;
	character->gold = 0;
	character->level = 1;
	character->weapon = {};
	strcpy_s(character->weapon->name, "미착용");

	return character;
}