#pragma once

#include <iostream>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <vector>

//�ؽ�Ʈ���Ͽ��� �����͸� �о�� �� �� ���� �ִ� ���� ��
#define CHAR_PER_LINE 1000
//�ؽ�Ʈ���Ͽ��� �����͸� �о�� �� �̸��� �ִ� ���� ��
#define ITEM_NAME_LENGTH 30
//�ؽ�Ʈ���Ͽ��� �����͸� �о�� �� ����� �ִ� ���� ��
#define GFX_PATH_LENGTH 50
//�ؽ�Ʈ���Ͽ��� �����͸� �о�� �� ������ �ִ� ���� ��
#define DESCRIPTION_LENGTH 800

using namespace std;

//�÷��̾� ����
enum eOccupation { WARRIOR, WIZARD, THIEF };
//������ ������
enum eHabitat { BIGINNER = 1, INTERMEDIATE, INTENCE, HELL };

//������ ����
enum ePotion {HP, MP};


typedef struct tagWeapon
{
	//������ ���̵�(1���� ����)
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	int attack;
	//������ ����. 
	char description[DESCRIPTION_LENGTH];
	int price;
	//����
	eOccupation  occupation;
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

typedef struct tagInventory
{
	//���ǰ���
	vector<POTION*> potions;
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
	//1���� ����
	int id = 0;
	char name[ITEM_NAME_LENGTH];
	char GFX_PATH[GFX_PATH_LENGTH];
	int attack;
	int maxHealth;
	int currHealth;
	int exp;
	int gold;
	//������
	eHabitat habitat;
	float spawnChance;

}MONSTER;

void PrintCharacter(const CHARACTER* const character);
CHARACTER* CreateCharacter(int selection);
void PrintMonster(const MONSTER* const monster);
//�ش� id�� ���͸� �����Ѵ�.
MONSTER* CreateMonster(MONSTER monsters[], int id);
//�ش� �������� ��� ���͵� �� �������� �����Ѵ�.
MONSTER* CreateMonster(MONSTER monsters[], int length, eHabitat habitat);
void LevelUp(CHARACTER* characer);
void OnGetExp(CHARACTER* character);
void printWeaponInfo(const WEAPON weapon);
void printWeaponInfo(const WEAPON* weapon);
void printPotionInfo(const POTION potion);
//�ؽ�Ʈ ������ �а� �Լ� ���ο��� ������ �迭�� �������� �Ҵ��Ѵ�.(���� = �� �׸�) �׸��� ���� ��ȯ�Ѵ�.
int GetInfo(char(**items)[CHAR_PER_LINE], char path[30]);
//�ؽ�Ʈ������ ��� �������� �����Ѵ�. �������� ���� �����Ѵ�.
int CreateAllWeapons(WEAPON** weapons);
//������ ���̵� �޾� �ϳ��� �������� �����Ѵ�(�����Ҵ�). ��� �������� ���� �迭�� �� ����, ���̵� �μ��� �޴´�.
WEAPON* CreateWeapon(WEAPON weapons[], int id);
//���ڿ��� int�� �Ľ��Ѵ�.
int StringToInt(const char arr[]);
//���ڿ��� float���� �Ľ��Ѵ�.
float StringToFloat(const char arr[]);
//�÷��̾ �׾�����
void OnCharacterDie(CHARACTER* character);
//������ �����Ҷ� �ڿ��� ��ȯ�Ѵ�.
void FinalizeGame(CHARACTER* character, WEAPON* weapons, POTION* potions);
void Save(CHARACTER* character);
CHARACTER* Load();
void EnterForge(CHARACTER* character, WEAPON* weapons, int weaponsCount);
//ĳ���� ������ ������ ���������ͷ� �޾ƾ���. �������� �����Ϳ� �����ϸ� �ǹ̰� �����ϱ�.
void EnterDungeon(CHARACTER** character, MONSTER monsters[], int monsterCnt, eHabitat habitat, int characterSelection);
void eOccupationToString(eOccupation occupation, char result[16]);
//�ؽ�Ʈ ������ �о� ����Ѵ�.
void printFile(const char path[30]);
//��� ���͸� �ؽ�Ʈ������ ������ �����.
int CreateAllMonsters(MONSTER** monsters);
//��� ������ �ؽ�Ʈ������ ������ �����.
int CreateAllPotions(POTION** potions);
//ü���� ġ���ϰų� ������ �� �� �ִ�.
void EnterHealersHouse(POTION* potions, int potionCount, CHARACTER* character);
POTION* CreatePotion(POTION potions[], int id);
//������ ����ϰ� �Ҵ������Ѵ�. nullptr�� �ٲ۴�.
void UsePotion(CHARACTER* character, int potionIndex);
void ShowInventory(CHARACTER* character);
int GetInventorySize(INVENTORY inventory);
void ShowPotionBag(CHARACTER* character);
void ShowWeaponBag(CHARACTER* character);