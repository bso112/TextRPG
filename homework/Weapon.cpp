#include "stdafx.h"
#include "Weapon.h"
#include "Parser.h"

void CWeapon::printWeaponInfo()
{
	if (0 == id)
	{
		cout << "맨손" << endl;
		return;
	}

	cout << "\n\n";
	CParser parser;
	parser.PrintFile(GFX_PATH);
	cout << '\n';
	cout << name << '\n';
	cout << "공격: " << attack << '\n';
	cout << description << '\n';
	cout << "가격: " << price << '\n';
	char arr[16] = "";
	parser.OccupationToString(occupation, arr);
	cout << "직업: " << occupation << '\n';
	char arr2[16] = "";
	parser.ElementToString(element, arr2);
	cout << "속성: " << element << endl;
	cout << "젬: " << gem->name << endl;
	cout << '\n' << "==========================================================================================" << endl;
}


void CWeapon::EnhanceWeapon()
{
	//0~99까지의 실수 난수.
	float random = (rand() / (float)RAND_MAX) * 99.f;

	//레벨 1일때 기본 확률
	float chance = BASE_ENHANCE_CHANCE;

	//레벨이의 5.2배만큼 확률 하락
	chance -= level * 5.2f;




	if (chance >= random)
	{
		system("cls");
		cout << "강화에 성공했습니다!" << endl;
		cout << "<강화 전>" << endl;
		printWeaponInfo();
		float weight = level / 3.f;
		weight = weight < 1 ? weight = 1 : weight;
		level += 1;
		attack += int(6 * weight);
		price += int(30 * weight);
		cout << "<강화 후>" << endl;
		printWeaponInfo();
		system("pause");
	}
	else
	{
		cout << "강화 실패!" << endl;
		system("pause");
	}



}