#include "stdafx.h"
#include "Character.h"
#include "Parser.h"

void CCharacter::CreateCharacter(int selection)
	{
		switch (selection)
		{
		case 1:
			strcpy_s(name, "����");
			attack = 10;
			maxHealth = 200;
			maxExp = 50;
			occupation = WARRIOR;
			break;
		case 2:
			strcpy_s(name, "������");
			attack = 15;
			maxHealth = 80;
			maxExp = 50;
			occupation = WIZARD;
			break;
		case 3:
			strcpy_s(name, "����");
			attack = 7;
			maxHealth = 150;
			maxExp = 50;
			occupation = THIEF;
			break;
		default:
			cout << "�߸��� �Է��Դϴ�." << endl;
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
		cout << "����: " << name << endl;
		cout << "����: " << level << endl;
		cout << "���ݷ�: " << attack << "(+" << weapon->attack << ")" << endl;
		cout << "ü��: " << currHealth << " / " << maxHealth << endl;
		cout << "����ġ: " << currExp << " / " << maxExp << endl;
		cout << "���: " << gold << endl;
		char element[16] = "";
		CParser parser;
		parser.ElementToString(weapon->element, element);
		cout << "���: " << weapon->name << "(" << element << ")" << endl;

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
		//ĳ���� ���� �о����
		fread(character, sizeof(CCharacter), 1, fp);
		//���� ������ �̵�
		//fseek(fp, sizeof(CHARACTER), SEEK_SET);
		//�������� ��������
		fread(weapon, sizeof(CWeapon), 1, fp);
		fclose(fp);
		//ĳ���� ���� �����ϱ�
		character->weapon = weapon;
		cout << "�ε� ����!" << endl;
		system("pause");
		return character;

	}
	else
		cout << "�ε� ����! ������ ������ �� �����ϴ�." << endl;

	return nullptr;
}

void CCharacter::Save(CCharacter* character)
{
	FILE* fp;
	//���� ��Ʈ�� ����
	errno_t err = fopen_s(&fp, "../Save/save1.txt", "wb");

	if (0 == err)
	{
		//ĳ���� ���� ����
		fwrite(character, sizeof(CCharacter), 1, fp);
		//���� ������ �̵�
		//fseek(fp, sizeof(CHARACTER), SEEK_SET);
		//�������� ����
		fwrite(character->weapon, sizeof(CWeapon), 1, fp);
		fclose(fp);
		cout << "���̺꼺��!" << endl;
		system("pause");
	}
	else
		cout << "���̺� ����! ������ ������ �� �����ϴ�." << endl;
}
