#include "stdafx.h"
#include "Character.h"
#include "Parser.h"

void CCharacter::CreateCharacter(int selection)
	{
		switch (selection)
		{
		case 1:
			strcpy_s(name, "전사");
			attack = 10;
			maxHealth = 200;
			maxExp = 50;
			occupation = WARRIOR;
			break;
		case 2:
			strcpy_s(name, "마법사");
			attack = 15;
			maxHealth = 80;
			maxExp = 50;
			occupation = WIZARD;
			break;
		case 3:
			strcpy_s(name, "도적");
			attack = 7;
			maxHealth = 150;
			maxExp = 50;
			occupation = THIEF;
			break;
		default:
			cout << "잘못된 입력입니다." << endl;
			return;
		}

		currHealth = maxHealth;
		currExp = 0;
		gold = 0;
		level = 1;
		
		inventory = {};

	}
void CCharacter::PrintCharacter()
	{
		cout << "직업: " << name << endl;
		cout << "레벨: " << level << endl;
		cout << "공격력: " << attack << "(+" << weapon->attack << ")" << endl;
		cout << "체력: " << currHealth << " / " << maxHealth << endl;
		cout << "경험치: " << currExp << " / " << maxExp << endl;
		cout << "골드: " << gold << endl;
		char element[16] = "";
		CParser parser;
		parser.ElementToString(weapon->element, element);
		cout << "장비: " << weapon->name << "(" << element << ")" << endl;

	}

void CCharacter::LevelUp()
{

	float weight = level / 3.f;
	weight = weight < 1 ? weight = 1 : weight;

	level += (int)1;
	maxHealth += (int)(20 * weight);
	currHealth = maxHealth;
	attack += (int)(5 * weight);
	maxExp += (int)(20 * weight);
	currExp = 0;

}

void CCharacter::OnGetExp()
{
	if (currExp >= maxExp)
	{
		LevelUp();
	}
}

CCharacter* CCharacter::Load()
{
	CWeapon* weapon = new CWeapon;
	*weapon = {};
	CCharacter* character = new CCharacter;
	*character = {};
	FILE* fp;
	errno_t err = fopen_s(&fp, "../Save/save1.txt", "rb");
	if (0 == err)
	{
		//캐릭터 정보 읽어오기
		fread(character, sizeof(CCharacter), 1, fp);
		//파일 포인터 이동
		//fseek(fp, sizeof(CHARACTER), SEEK_SET);
		//무기정보 가져오기
		fread(weapon, sizeof(CWeapon), 1, fp);
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

void CCharacter::Save(CCharacter* character)
{
	FILE* fp;
	//파일 스트림 생성
	errno_t err = fopen_s(&fp, "../Save/save1.txt", "wb");

	if (0 == err)
	{
		//캐릭터 정보 저장
		fwrite(character, sizeof(CCharacter), 1, fp);
		//파일 포인터 이동
		//fseek(fp, sizeof(CHARACTER), SEEK_SET);
		//무기정보 저장
		fwrite(character->weapon, sizeof(CWeapon), 1, fp);
		fclose(fp);
		cout << "세이브성공!" << endl;
		system("pause");
	}
	else
		cout << "세이브 실패! 파일을 저장할 수 없습니다." << endl;
}
