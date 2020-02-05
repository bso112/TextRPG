#include "stdafx.h"
#include "Weapon.h"
#include "Parser.h"

void CWeapon::printWeaponInfo()
{
	if (0 == id)
	{
		cout << "�Ǽ�" << endl;
		return;
	}

	cout << "\n\n";
	CParser parser;
	parser.PrintFile(GFX_PATH);
	cout << '\n';
	cout << name << '\n';
	cout << "����: " << attack << '\n';
	cout << description << '\n';
	cout << "����: " << price << '\n';
	char arr[16] = "";
	parser.OccupationToString(occupation, arr);
	cout << "����: " << occupation << '\n';
	char arr2[16] = "";
	parser.ElementToString(element, arr2);
	cout << "�Ӽ�: " << element << endl;
	cout << "��: " << gem->name << endl;
	cout << '\n' << "==========================================================================================" << endl;
}


void CWeapon::EnhanceWeapon()
{
	//0~99������ �Ǽ� ����.
	float random = (rand() / (float)RAND_MAX) * 99.f;

	//���� 1�϶� �⺻ Ȯ��
	float chance = BASE_ENHANCE_CHANCE;

	//�������� 5.2�踸ŭ Ȯ�� �϶�
	chance -= level * 5.2f;




	if (chance >= random)
	{
		system("cls");
		cout << "��ȭ�� �����߽��ϴ�!" << endl;
		cout << "<��ȭ ��>" << endl;
		printWeaponInfo();
		float weight = level / 3.f;
		weight = weight < 1 ? weight = 1 : weight;
		level += 1;
		attack += int(6 * weight);
		price += int(30 * weight);
		cout << "<��ȭ ��>" << endl;
		printWeaponInfo();
		system("pause");
	}
	else
	{
		cout << "��ȭ ����!" << endl;
		system("pause");
	}



}