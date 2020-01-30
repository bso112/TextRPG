#pragma once

#include <iostream>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <vector>

#include <crtdbg.h> // _CrtDumpMemoryLeaks() 사용하기위해
#if _DEBUG 
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__) 
#endif // 몇행에서 메모리 누수가 나는지 알려줌. 

//기본 무기 강화확률
#define BASE_ENHANCE_CHANCE 80.0f
//텍스트파일에서 데이터를 읽어올 때 한 줄의 최대 문자 수
#define CHAR_PER_LINE 1000
//텍스트파일에서 데이터를 읽어올 때 이름의 최대 문자 수
#define ITEM_NAME_LENGTH 30
//텍스트파일에서 데이터를 읽어올 때 경로의 최대 문자 수
#define GFX_PATH_LENGTH 50
//텍스트파일에서 데이터를 읽어올 때 설명의 최대 문자 수
#define DESCRIPTION_LENGTH 800

using namespace std;

//플레이어 직업
enum eOccupation { WARRIOR, WIZARD, THIEF };
//몬스터의 서식지
enum eHabitat { BIGINNER = 1, INTERMEDIATE, INTENCE, HELL };

//포션의 종류
enum ePotion {HP, MP};


typedef struct tagWeapon
{
	//아이템 아이디(1부터 시작) 0은 맨손
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	int attack;
	//아이템 설명. 
	char description[DESCRIPTION_LENGTH];
	int price;
	//직업
	eOccupation  occupation;
	//강화레벨
	int level = 1;
}WEAPON;

typedef struct tagPotion
{
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	int healAmount;
	char description[DESCRIPTION_LENGTH];
	int price;
	ePotion sort;
}POTION;

//인벤토리에 들어갈 자료형 추가시, Finalize함수에서 인벤토리 할당해제할때 그 자료형도 같이 해제해야함.
typedef struct tagInventory
{
	//포션가방
	vector<POTION*> potions;
	//무기가방
	vector<WEAPON*> weapons;

}INVENTORY;

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
	INVENTORY *inventory;
	eOccupation  occupation;

}CHARACTER;

typedef struct tagMonster
{
	//1부터 시작
	int id = 0;
	char name[ITEM_NAME_LENGTH];
	char GFX_PATH[GFX_PATH_LENGTH];
	int attack;
	int maxHealth;
	int currHealth;
	int exp;
	int gold;
	//서식지
	eHabitat habitat;
	float spawnChance;

}MONSTER;

void PrintCharacter(const CHARACTER* const character);
CHARACTER* CreateCharacter(int selection);
void PrintMonster(const MONSTER* const monster);
//해당 id의 몬스터를 스폰한다.
MONSTER* CreateMonster(MONSTER monsters[], int id);
//해당 서식지에 사는 몬스터들 중 랜덤으로 스폰한다.
MONSTER* CreateMonster(MONSTER monsters[], int length, eHabitat habitat);
void LevelUp(CHARACTER* characer);
void OnGetExp(CHARACTER* character);
void printWeaponInfo(const WEAPON weapon);
void printWeaponInfo(const WEAPON* weapon);
void printPotionInfo(const POTION potion);
//텍스트 파일을 읽고 함수 내부에서 이차원 배열에 동적으로 할당한다.(한줄 = 한 항목) 항목의 수를 반환한다.
int GetInfo(char(**items)[CHAR_PER_LINE], char path[30]);
//텍스트파일의 모든 아이템을 생성한다. 아이템의 수를 리턴한다.
int CreateAllWeapons(WEAPON** weapons);
//아이템 아이디를 받아 하나의 아이템을 생성한다(동적할당). 모든 아이템을 가진 배열과 그 길이, 아이디를 인수로 받는다.
WEAPON* CreateWeapon(WEAPON weapons[], int id);
//문자열을 int로 파싱한다.
int StringToInt(const char arr[]);
//문자열을 float으로 파싱한다.
float StringToFloat(const char arr[]);
//플레이어가 죽었을때
void OnCharacterDie(CHARACTER* character);
//게임을 종료할때 자원을 반환한다.
void FinalizeGame(CHARACTER* character, MONSTER* monsters, WEAPON* weapons, POTION* potions);
void Save(CHARACTER* character);
CHARACTER* Load();
void EnterForge(CHARACTER* character, WEAPON* weapons, int weaponsCount);
//캐릭터 리스폰 때문에 이중포인터로 받아야함. 지역변수 포인터에 대입하면 의미가 없으니까.
void EnterDungeon(CHARACTER** character, MONSTER monsters[], int monsterCnt, eHabitat habitat, int characterSelection);
void eOccupationToString(eOccupation occupation, char result[16]);
//텍스트 파일을 읽어 출력한다.
void printFile(const char path[30]);
//모든 몬스터를 텍스트파일을 참조해 만든다.
int CreateAllMonsters(MONSTER** monsters);
//모든 포션을 텍스트파일을 참조해 만든다.
int CreateAllPotions(POTION** potions);
//체력을 치유하거나 포션을 살 수 있다.
void EnterHealersHouse(POTION* potions, int potionCount, CHARACTER* character);
POTION* CreatePotion(POTION potions[], int id);
//포션을 사용하고 할당해제한다. nullptr로 바꾼다.
void UsePotion(CHARACTER* character, int potionIndex);
void ShowInventory(CHARACTER* character);
int GetInventorySize(INVENTORY inventory);
void ShowPotionBag(CHARACTER* character);
void ShowWeaponBag(CHARACTER* character);
void EnhanceWeapon(WEAPON* weapon);
void EnhanceWeaponPage(CHARACTER* character);