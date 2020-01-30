#include "TextRPG.h"


void main()
{
	//âũ��
	system("mode con cols=91");

	srand(unsigned(time(NULL)));

	//������ ������ ���� ������ �迭
	WEAPON* weapons = nullptr;
	//ó���� ��� ���� ������
	int weaponsCount = CreateAllWeapons(&weapons);

	//��� ���͸� ������
	MONSTER* monsters = nullptr;
	int monsterCount = CreateAllMonsters(&monsters);

	POTION* potions = nullptr;
	int potionCount = CreateAllPotions(&potions);

	//�÷��̾� ĳ����
	CHARACTER* character = nullptr;

	//ĳ���� ����ȭ��
	while (true)
	{

		system("cls");
		//�ΰ� ���
		printFile("../GFX/logo.txt");

		cout << "0.�ε� 1.���� 2.������ 3.���� 4.������" << endl;

		int characterToCreate;
		cin >> characterToCreate;

		CHARACTER* character = nullptr;

		//����
		if (characterToCreate == 4)
		{
			FinalizeGame(character, weapons, potions);
			return;
		}
		//���̺� �����ͷε�
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
			//ĳ���ʹ� ���ý� �ѹ� ����
			character = CreateCharacter(characterToCreate);

#ifdef _DEBUG
			character->gold = 1000;
#endif
		}

		//ĳ������ �ൿ���� ȭ��
		while (true)
		{

			system("cls");
			//ĳ���� ���� ���
			PrintCharacter(character);

			cout << "================================================" << endl;

			cout << "0. ���̺� 1. �ʱ޴��� 2. �߱޴��� 3. ��޴��� 4. ���尣  5. ������ 6. �κ��丮 900. ������" << endl;

			//��� �� ���ΰ�?
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
			//��������
			else if (destiantion > 0 && destiantion <= 3)
			{
				EnterDungeon(&character, monsters, monsterCount, (eHabitat)destiantion, characterToCreate);
			}
			//���尣 ����
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
				cout << "�߸��� �Է��Դϴ�" << endl;


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
		cout << "���� �����Դϴ�." << endl;
		break;
	}


}

void EnterHealersHouse(POTION* potions, int potionCount, CHARACTER* character)
{
	while (true)
	{
		system("cls");
		cout << "���� ���� ��������!" << endl;
		cout << "�ܾ�: " << character->gold << endl;
		cout << '\n' << "0. ������" << endl;
		for (int i = 0; i < potionCount; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
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
			cout << "�߸��� �Է��Դϴ�" << endl;
			system("pause");

		}
		//�߸��� �Է��� �ƴϸ�
		//1 1
		else
		{
			if (character->gold >= potions[itemSelect - 1].price)
			{
				POTION* potion = CreatePotion(potions, itemSelect);
				//�÷��̾� �κ��丮�� ���ǳֱ�
				character->inventory->potions.push_back(potion);
				character->gold -= potion->price;
				cout << potion->name << "�� �����Ͽ����ϴ�!" << endl;
			}
			else
				cout << "���� �����մϴ�!" << endl;
			
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
		cout << "1. ���� 2. ����" << endl;

		int iSelect_Behavior;
		cin >> iSelect_Behavior;

		//����
		if (iSelect_Behavior == 2)
		{
			delete monster;
			break;
		}
		//����
		if (iSelect_Behavior == 1)
		{
			monster->currHealth -= (*character)->attack;
			(*character)->currHealth -= monster->attack;


			if (monster->currHealth <= 0 && (*character)->currHealth <= 0)
			{
				cout << "��ɿ� ���������� �÷��̾ �׾����ϴ�!" << endl;
				(*character)->currExp += monster->exp;
				OnGetExp(*character);
				delete monster;
				monster = nullptr;
				OnCharacterDie(*character);
				//ĳ���� ������
				*character = CreateCharacter(characterSelection);
				system("pause");
				break;

			}
			else
			{
				if (monster->currHealth <= 0)
				{
					cout << "��ɿ� �����߽��ϴ�!" << '\n' << monster->gold << " ��带 ������ϴ�." << endl;
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
					cout << "�÷��̾� ���!" << endl;

					OnCharacterDie(*character);
					//ĳ���� ������
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

		cout << "�ְ��� ���Ⱑ ���ֽ��ϴ�." << endl;
		cout << "�ܾ�: " << character->gold << endl;

		cout << '\n' << "0. ������" << endl;

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
			cout << "�߸��� �Է��Դϴ�" << endl;
			system("pause");

		}
		//�߸��� �Է��� �ƴϸ�
		else
		{
			WEAPON weaponToBuy = weapons[itemSelect - 1];
			if (character->occupation != weaponToBuy.occupation)
			{
				cout << "������ �� ���� Ŭ������ �����Դϴ�!" << endl;
				system("pause");
				continue;

			}


			if (character->gold >= weapons[itemSelect - 1].price)
			{
				WEAPON* weapon = CreateWeapon(weapons, itemSelect);
				cout << weapon->name << "��(��) �����Ͽ����ϴ�!" << endl;

				delete character->weapon;

				character->weapon = weapon;
				character->attack += character->weapon->attack;
				character->gold -= weapon->price;
			}
			else
				cout << "���� �����մϴ�!" << endl;

			system("pause");
		}


	}
}

void Save(CHARACTER* character)
{
	FILE* fp;
	//���� ��Ʈ�� ����
	errno_t err = fopen_s(&fp, "../Save/save1.txt", "wb");

	if (0 == err)
	{
		//ĳ���� ���� ����
		fwrite(character, sizeof(CHARACTER), 1, fp);
		//���� ������ �̵�
		//fseek(fp, sizeof(CHARACTER), SEEK_SET);
		//�������� ����
		fwrite(character->weapon, sizeof(WEAPON), 1, fp);
		fclose(fp);
		cout << "���̺꼺��!" << endl;
		system("pause");
	}
	else
		cout << "���̺� ����! ������ ������ �� �����ϴ�." << endl;
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
		//ĳ���� ���� �о����
		fread(character, sizeof(CHARACTER), 1, fp);
		//���� ������ �̵�
		//fseek(fp, sizeof(CHARACTER), SEEK_SET);
		//�������� ��������
		fread(weapon, sizeof(WEAPON), 1, fp);
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

WEAPON* CreateWeapon(WEAPON weapons[], int id)
{
	WEAPON* weapon = new WEAPON;
	memcpy(weapon, &(weapons[id - 1]), sizeof(WEAPON));
	return weapon;

}

int CreateAllWeapons(WEAPON** weapons)
{

	//���⿡ ���� ������ ���� �������迭 �����͸� �غ��Ѵ�.
	char(*weaponInfos)[CHAR_PER_LINE] = nullptr;

	//���������� �������� �Ҵ�޴´�.
	int itemCount = GetInfo(&weaponInfos, "../Data/weapon.txt");

	*weapons = new WEAPON[itemCount];


	//��ǥ�� �����鼭 ���� ����ü�� ���� ���� ����
	for (int i = 0; i < itemCount; ++i)
	{
		//word�� ��,��
		int col = 0, row = 0;
		//�ϳ��� ���� ����ü�� ���� ����.
		//description �׸񶧹��� ��� �׸��� 800���� ������ ��Ҵ�. ��ȿ������. ���� �ʿ�
		char word[7][DESCRIPTION_LENGTH] = {};

		int len = strlen(weaponInfos[i]);

		//��ǥ������ �Ľ��ϱ�
		for (int j = 0; j < len; ++j)
		{
			//word�� ��谪�� �Ѿ�� ����
			if (col > 6 || row > DESCRIPTION_LENGTH-1)
			{
				continue;
			}
			//��ǥ�� word�� ���� ���� ä���.
			if (',' == weaponInfos[i][j])
			{
				++col;
				row = 0;
			}
			//���๮�ڸ� ����������.
			else if ('\n' == weaponInfos[i][j])
			{
				break;
			}
			//�� ���� �ƴϸ� �����͸� word �� �ִ´�.
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

	//���⿡ ���� ������ ���� �������迭 �����͸� �غ��Ѵ�.
	char(*monsterInfos)[CHAR_PER_LINE] = nullptr;

	//���������� �������� �Ҵ�޴´�.
	int itemCount = GetInfo(&monsterInfos, "../Data/monster.txt");
	*monsters = new MONSTER[itemCount];


	//��ǥ�� �����鼭 ���� ����ü�� ���� ���� ����
	for (int i = 0; i < itemCount; ++i)
	{
		//word�� ��,��
		int col = 0, row = 0;
		//�ϳ��� ���� ����ü�� ���� ����.
		//description �׸񶧹��� ��� �׸��� 800���� ������ ��Ҵ�. ��ȿ������. ���� �ʿ�
		char word[10][DESCRIPTION_LENGTH] = {};

		int len = strlen(monsterInfos[i]);

		//��ǥ������ �Ľ��ϱ�
		for (int j = 0; j < len; ++j)
		{
			//word�� ��谪�� �Ѿ�� ����
			if (col > 9 || row > DESCRIPTION_LENGTH-1)
			{
				continue;
			}
			//��ǥ�� word�� ���� ���� ä���.
			if (',' == monsterInfos[i][j])
			{
				++col;
				row = 0;
			}
			//���๮�ڸ� ����������.
			else if ('\n' == monsterInfos[i][j])
			{
				break;
			}
			//�� ���� �ƴϸ� �����͸� word �� �ִ´�.
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

	//���⿡ ���� ������ ���� �������迭 �����͸� �غ��Ѵ�.
	char(*potionInfos)[CHAR_PER_LINE] = nullptr;

	//���������� �������� �Ҵ�޴´�.
	int itemCount = GetInfo(&potionInfos, "../Data/potion.txt");
	*potions = new POTION[itemCount];


	//��ǥ�� �����鼭 ���� ����ü�� ���� ���� ����
	for (int i = 0; i < itemCount; ++i)
	{
		//word�� ��,��
		int col = 0, row = 0;
		//�ϳ��� ���� ����ü�� ���� ����.
		//description �׸񶧹��� ��� �׸��� 800���� ������ ��Ҵ�. ��ȿ������. ���� �ʿ�
		char word[7][800] = {};

		int len = strlen(potionInfos[i]);

		//��ǥ������ �Ľ��ϱ�
		for (int j = 0; j < len; ++j)
		{
			//word�� ��谪�� �Ѿ�� ����
			if (col > 6 || row > 799)
			{
				continue;
			}
			//��ǥ�� word�� ���� ���� ä���.
			if (',' == potionInfos[i][j])
			{
				++col;
				row = 0;
			}
			//���๮�ڸ� ����������.
			else if ('\n' == potionInfos[i][j])
			{
				break;
			}
			//�� ���� �ƴϸ� �����͸� word �� �ִ´�.
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
	//���ڿ�->���� �Ľ�
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
	// 10�� 0���� 1 
	//      1���� 10 ...

	return result;
}

float StringToFloat(const char arr[])
{
	//���ڿ�->���� �Ľ�
	float result = 0.0f;
	int totalLen = strlen(arr);

	//�Ҽ��� �̻��� ����
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
	//������ ��Ͽ��� �������� ��
	int itemCount = 0;

	FILE* fp = nullptr;

	errno_t err = fopen_s(&fp, path, "rt");
	if (0 == err)
	{
		//������ �ε���
		int col = 0;
		int row = 0;
		int c = 0;
		//������ �о �ǳ�?
		bool infoStart = false;


		//������ ���������� ���ڸ� �޾ƿ�
		while (EOF != c)
		{

			//���ڸ� �ϳ��ϳ� ������
			c = getc(fp);

			if (EOF == c)
				continue;
			//�ּ� ����
			if ('*' == c)
			{
				//�����Ҷ����� �д´�.
				while ('\n' != c)
				{
					c = getc(fp);
				}
				//���� ���� �������� c�� ������ '\n'�̴� ��Ƽ��
				continue;
			}

			//ù���̸� �� ������ ���� �޾ƿ���, �����Ҷ����� ����
			if (col == 0 && !infoStart)
			{
				itemCount = c - '0';
				//������ ������ ������ �迭 ��������
				*items = new char[itemCount][CHAR_PER_LINE];

				//�ι��ڷ� �ʱ�ȭ
				memset(*items, '\0', (sizeof(char) * CHAR_PER_LINE) * itemCount);
				while ('\n' != c)
				{
					c = getc(fp);
				}
				infoStart = true;
				continue;
			}

			//���� ������ ���� �о���� ����
			//�����ҽ� �ε��� �ʱ�ȭ. ��ǥ������ �Ľ��Ҷ� ������ ���� �˸��� ���� ���๮�ڵ� �ִ´�.
			if ('\n' == c)
			{
				(*items)[col][row] = c;
				++col;
				row = 0;
			}
			//�ƴϸ� ���� ������Ű�� �޾ƿ� ���� �ֱ�. 
			else
			{
				(*items)[col][row] = c;
				++row;
			}

		}


		fclose(fp);

	}
	else
		cout << "���� ���� ����!" << endl;



	return itemCount;

}

void printWeaponInfo(const WEAPON weapon)
{
	cout << '\n' << "==========================================" << endl;
	printFile(weapon.GFX_PATH);
	cout << '\n';
	cout << weapon.id << ". " << weapon.name << '\n';
	cout << "���� : " << weapon.attack << '\n';
	cout << weapon.description << '\n';
	cout << "���� : " << weapon.price << '\n';
	char occupation[16] = "";
	eOccupationToString(weapon.occupation, occupation);
	cout << "���� : " << occupation << '\n';
}

void printWeaponInfo(const WEAPON* weapon)
{
	cout << '\n' << "==========================================" << endl;
	cout << weapon->id << '. ' << weapon->name << '\n';
	printFile(weapon->GFX_PATH);
	cout << '\n';
	cout << "���� : " << weapon->attack << '\n';
	cout << weapon->description << '\n';
	cout << "���� : " << weapon->price << '\n';
	cout << "���� : " << weapon->occupation << '\n';
}

void printPotionInfo(const POTION potion)
{
	cout << "==========================================" << endl;
	printFile(potion.GFX_PATH);
	cout << '\n';
	cout << potion.name << '\n';
	cout << "ȸ���� : " << potion.healAmount << '\n';
	cout << potion.description << '\n';
	cout << "���� : " << potion.price << '\n';
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
		cout << "�̸�: " << monster->name << endl;
		cout << "���ݷ�: " << monster->attack << endl;
		cout << "ü��: " << monster->currHealth << " / " << monster->maxHealth << endl;

	}

}

void PrintCharacter(const CHARACTER* const character)
{
	cout << "����: " << character->name << endl;
	cout << "����: " << character->level << endl;
	cout << "���ݷ�: " << character->attack << "(+" << character->weapon->attack << ")" << endl;
	cout << "ü��: " << character->currHealth << " / " << character->maxHealth << endl;
	cout << "����ġ: " << character->currExp << " / " << character->maxExp << endl;
	cout << "���: " << character->gold << endl;
	cout << "���: " << character->weapon->name << endl;

}


MONSTER* CreateMonster(MONSTER monsters[], int id)
{
	MONSTER* monster = new MONSTER;
	memcpy(monster, &(monsters[id - 1]), sizeof(MONSTER));
	return monster;

}

MONSTER* CreateMonster(MONSTER monsters[], int length, eHabitat habitat)
{

	//���� �������� ��� ���͵��� id. �ִ� length(��� ������ ��)��ŭ �ִ�.
	int* family = new int[length];
	float* spawnChance = new float[length];
	*family = {};
	*spawnChance = {};

	float chanceSum = 0;
	//family�� �ε������� +1�� family�� ����
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


	//�������� ����
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


	// Ȯ���� ��Ÿ����

	//Ȯ�������� ���� ����
	int randomNum = (rand() % (int)chanceSum) + 1;
	//����Ȯ��
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
	//// family[0] family[1] 0 ~ index-1�� �������� �������� ���� ���̵�
	//int randomIndex = rand() % index;
	////�������� �� ������ ���̵�
	//int id = family[randomIndex];

	int idToSpawn = family[familyIndex];
	cout << "����Ȯ��: " << (spawnChance[familyIndex] / chanceSum) * 100 << endl;
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
		strcpy_s(character->name, "����");
		character->attack = 10;
		character->maxHealth = 200;
		character->maxExp = 50;
		character->occupation = WARRIOR;
		break;
	case 2:
		character = new CHARACTER;
		strcpy_s(character->name, "������");
		character->attack = 15;
		character->maxHealth = 80;
		character->maxExp = 50;
		character->occupation = WIZARD;
		break;
	case 3:
		character = new CHARACTER;
		strcpy_s(character->name, "����");
		character->attack = 7;
		character->maxHealth = 150;
		character->maxExp = 50;
		character->occupation = THIEF;
		break;
	default:
		cout << "�߸��� �Է��Դϴ�." << endl;
		return nullptr;
	}

	character->currHealth = character->maxHealth;
	character->currExp = 0;
	character->gold = 0;
	character->level = 1;
	//������ �󲮵��� ���� �ֱ�
	character->weapon = new WEAPON;
	*(character->weapon) = {};
	strcpy_s(character->weapon->name, "������");
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
		cout << "������ ���� �����ϴ�." << endl;

}

//������ ����ϰ� �Ҵ������Ѵ�. nullptr�� �ٲ۴�.
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

			cout << "�κ��丮�� ������ϴ�!" << endl;
			system("pause");
			return;
		}
		//�κ��丮�� �������� ������
		else
		{
			cout << "�κ��丮" << endl;


			cout << "0. ������ 1.���� 2.����" << endl;

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
				cout << "�̱���" << endl;
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

		cout << "���� �κ��丮" << "\n\n";

		int potionCnt = character->inventory->potions.size();
		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			printPotionInfo(*(character->inventory->potions[i]));
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ���" << endl;
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
			cout << character->inventory->potions[selection - 1]->name << "�� ����ߴ�!" << endl;
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
	cout << "������ �����մϴ�." << endl;
}
int GetInventorySize(INVENTORY inventory)
{
	int size = inventory.potions.size();
	return size;
}
