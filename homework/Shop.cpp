#include "stdafx.h"
#include "Shop.h"

void CShop::EnhanceWeapon(CWeapon* weapon)
{
	//0~99������ �Ǽ� ����.
	float random = (rand() / (float)RAND_MAX) * 99.f;

	//���� 1�϶� �⺻ Ȯ��
	float chance = BASE_ENHANCE_CHANCE;

	//�������� 5.2�踸ŭ Ȯ�� �϶�
	chance -= weapon->level * 5.2f;




	if (chance >= random)
	{
		system("cls");
		cout << "��ȭ�� �����߽��ϴ�!" << endl;
		cout << "<��ȭ ��>" << endl;
		weapon->printWeaponInfo();
		float weight = weapon->level / 3.f;
		weight = weight < 1 ? weight = 1 : weight;
		weapon->level += 1;
		weapon->attack += int(6 * weight);
		weapon->price += int(30 * weight);
		cout << "<��ȭ ��>" << endl;
		weapon->printWeaponInfo();
		system("pause");
	}
	else
	{
		cout << "��ȭ ����!" << endl;
		system("pause");
	}



}

void CShop::EnhanceWeaponPage(CCharacter* character)
{
	while (true)
	{

		system("cls");

		cout << "���� �κ��丮" << "\n\n";

		cout << "<������> " << endl;
		cout << "���������� ����� ��ȭ�� �Ұ��մϴ�." << endl;
		character->weapon->printWeaponInfo();
		cout << "\n\n";

		int weaponCnt = character->inventory->weapons.size();
		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			character->inventory->weapons[i]->printWeaponInfo();
			cout << "��ȭȮ��: " << BASE_ENHANCE_CHANCE - (character->inventory->weapons[i]->level * 5.2f) << endl;
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ��ȭ�ϱ�" << endl;
		unsigned int selection;
		cin >> selection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == selection)
		{
			return;
		}
		//�׸� ��ȣ�� ����� �Է�������
		else if (selection <= character->inventory->weapons.size())
		{
			//��ȭ��
			int cost = character->inventory->weapons[selection - 1]->price / 5;
			//���� ����ϸ�
			if (character->gold >= cost)
			{
				character->gold -= cost;
				//��ȭ�õ�
				EnhanceWeapon(character->inventory->weapons[selection - 1]);
			}
		}
	}
}


