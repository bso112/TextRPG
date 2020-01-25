#include <iostream>
#include <math.h>


using namespace std;

typedef struct tagWeapon
{
	//������ ���̵�
	int id;
	char name[16];
	int attack;
	//������ ����. 
	char description[800];
	int price;
	//������ �� �ִ� ����
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
	WEAPON weapon;

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
void printWeaponInfo(const WEAPON wepon);
//�ؽ�Ʈ���Ͽ��� ��� ������ ������ ������ 2�����迭 �����Ϳ� �����Ҵ��ϰ�, �������� ������ ��ȯ�Ѵ�. 
//�迭���� 1000���� ������ �ؽ�Ʈ������ �� ������ �ִ� 1000���� ���ڷ� �̷�����ٰ� �����߱� �����̴�.
//�������� ���� �����Ѵ�.
int GetWeaponInfo(char(**items)[1000]);
//�ؽ�Ʈ������ ��� �������� �����Ѵ�. �������� ���� �����Ѵ�.
int CreateAllWeapons(WEAPON** weapons);
//������ ���̵� �޾� �ϳ��� �������� �����Ѵ�.
WEAPON* CreateWeapon(int id);
//���ڿ��� int�� �Ľ��Ѵ�.
int StringToInt(const char arr[]);

void main()
{

	WEAPON* weapons = nullptr;
	int weaponsCount = CreateAllWeapons(&weapons);
	
	cout << "�������� ��: " << weaponsCount << endl;

	delete[] weapons;
	weapons = nullptr;
	exit(0);
	//ĳ���� ����ȭ��
	while (true)
	{
		cout << "1.���� 2.������ 3.���� 4.������" << endl;

		int iSelect_character;
		cin >> iSelect_character;

		//����
		if (iSelect_character == 4)
		{
			cout << "������ �����մϴ�." << endl;
			return;
		}

		//ĳ���ʹ� ���ý� �ѹ� ����
		CHARACTER* character = CreateCharacter(iSelect_character);

		//ĳ������ �ൿ���� ȭ��
		while (true)
		{

			system("cls");
			PrintCharacter(character);

			cout << "================================================" << endl;

			cout << "1. �ʱ޴��� 2. �߱޴��� 3. ��޴��� 4. ���� 5. ������" << endl;

			int iSelect_dungeon;
			cin >> iSelect_dungeon;

			if (iSelect_dungeon == 5)
			{
				cout << "������ �����մϴ�." << endl;
				return;
			}

			//��������
			if (iSelect_dungeon <= 3)
			{
				//���ʹ� ������ ���� �ѹ� ����
				MONSTER* monster = CreateMonster(iSelect_dungeon);
				//�������� ȭ��
				while (true)
				{


					system("cls");
					PrintCharacter(character);
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
						system("cls");
						break;
					}
					//����
					if (iSelect_Behavior == 1)
					{
						monster->currHealth -= character->attack;
						character->currHealth -= monster->attack;


						if (monster->currHealth <= 0 && character->currHealth <= 0)
						{
							cout << "��ɿ� ���������� �÷��̾ �׾����ϴ�!" << endl;
							character->currExp += monster->exp;
							OnGetExp(character);
							delete monster;
							monster = nullptr;
							delete character;
							character = nullptr;
							//ĳ���� ������
							character = CreateCharacter(iSelect_character);
							system("pause");
							break;

						}
						else
						{
							if (monster->currHealth <= 0)
							{
								cout << "��ɿ� �����߽��ϴ�!" << '\n' << monster->gold << " ��带 ������ϴ�." << endl;
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
								cout << "�÷��̾� ���!" << endl;
								delete character;
								character = nullptr;
								//ĳ���� ������
								character = CreateCharacter(iSelect_character);
								system("pause");
								break;
							}
						}

					}
				}
			}

			//��������
			if (iSelect_dungeon == 4)
			{
				while (true)
				{
					system("cls");

					cout << "������ �������!" << endl;
					cout << "�ܾ�: " << character->gold << endl;






					WEAPON sword;
					strcpy_s(sword.name, "ö��");
					sword.attack = 3;
					strcpy_s(sword.description, "����� ���̴�. ���� ���̴�");
					sword.price = 100;

					WEAPON staff;
					strcpy_s(staff.name, "����������");
					staff.attack = 3;
					strcpy_s(staff.description, "�߽� �����簡 ������ �� �� �ִ� �����̴�.");
					staff.price = 100;

					WEAPON suriken;
					strcpy_s(suriken.name, "������");
					suriken.attack = 3;
					strcpy_s(suriken.description, "���� �������� �������̴�. ������ �ܴ��ϴ�.");
					suriken.price = 100;

					cout << '\n' << "4. ������" << endl;
					cout << '\n' << "==========================================" << '\n' << endl;
					cout << "1. ö��" << endl;
					printWeaponInfo(sword);
					cout << '\n' << "==========================================" << '\n' << endl;
					cout << "2. ����������" << endl;
					printWeaponInfo(staff);
					cout << '\n' << "==========================================" << '\n' << endl;
					cout << "3. ������" << endl;
					printWeaponInfo(suriken);

					int itemSelect;
					cin >> itemSelect;

					if (itemSelect == 4)
						break;

					WEAPON choosen;

					switch (itemSelect)
					{
					case 1:
						choosen = sword;
						break;
					case 2:
						choosen = staff;
						break;
					case 3:
						choosen = suriken;
						break;
					default:
						cout << "�߸��� �����Դϴ�." << endl;
					}

					if (character->gold >= choosen.price)
					{
						cout << choosen.name << "��(��) �����Ͽ����ϴ�!" << endl;
						character->weapon = choosen;
						character->attack += character->weapon.attack;
						character->gold -= choosen.price;
					}
					else
						cout << "���� �����մϴ�!" << endl;

					system("pause");
				}
			}


		}
	}

}

int CreateAllWeapons(WEAPON** weapons)
{

	//���⿡ ���� ������ ���� �������迭 �����͸� �غ��Ѵ�.
	char(*weaponInfos)[1000] = nullptr;

	//���������� �������� �Ҵ�޴´�.
	int itemCount = GetWeaponInfo(&weaponInfos);

	//for (int i = 0; i < itemCount; ++i)
	//{
	//	cout << weaponInfos[i] << endl;
	//}

	//cout << "������ ��: " << itemCount << endl;

	*weapons = new WEAPON[itemCount];


	//��ǥ�� �����鼭 ���� ����ü�� ���� ���� ����
	for (int i = 0; i < itemCount; ++i)
	{
		//word�� ��,��
		int col = 0, row = 0;
		//�ϳ��� ���� ����ü�� ���� ����.
		//description �׸񶧹��� ��� �׸��� 800���� ������ ��Ҵ�. ��ȿ������. ���� �ʿ�
		char word[6][800] = {};

		int len = strlen(weaponInfos[i]);

		//��ǥ������ �Ľ��ϱ�
		for (int j = 0; j < len; ++j)
		{	
			//word�� ��谪�� �Ѿ�� ����
			if (col > 5 || row > 799)
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
		strcpy_s((*weapons)[i].name, 16, word[1]);
		(*weapons)[i].attack = StringToInt(word[2]);
		strcpy_s((*weapons)[i].description, 800, word[3]);
		(*weapons)[i].price = StringToInt(word[4]);
		strcpy_s((*weapons)[i].occupation, 16, word[5]);
		printWeaponInfo((*weapons)[i]);

	}

	delete[] weaponInfos;
	weaponInfos = nullptr;
	
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

int GetWeaponInfo(char(**items)[1000])
{
	//������ ��Ͽ��� �������� ��
	int itemCount = 0;

	FILE* fp = nullptr;

	errno_t err = fopen_s(&fp, "../weapon.txt", "rt");
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
				*items = new char[itemCount][1000];

				//�ι��ڷ� �ʱ�ȭ
				//for (int i = 0; i < itemCount; ++i)
				//{
				//	for (int j = 0; j < 1000; ++j)
				//	{
				//		(*items)[i][j] = '\0';
				//	}
				//}

				//�ι��ڷ� �ʱ�ȭ
				memset(*items, '\0', (sizeof(char) * 1000) * itemCount);
				while ('\n' != c)
				{
					c = getc(fp);
				}
				//cout << "2"<< *items << endl;
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

void printWeaponInfo(const WEAPON wepon)
{
	cout << "�̸� : " << wepon.name << endl;
	cout << "���� : " << wepon.attack << endl;
	cout << wepon.description << endl;
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
	cout << "�̸�: " << monster->name << endl;
	cout << "���ݷ�: " << monster->attack << endl;
	cout << "ü��: " << monster->currHealth << " / " << monster->maxHealth << endl;
}

void PrintCharacter(const CHARACTER* const character)
{
	cout << "����: " << character->name << endl;
	cout << "����: " << character->level << endl;
	cout << "���ݷ�: " << character->attack << "(+" << character->weapon.attack << ")" << endl;
	cout << "ü��: " << character->currHealth << " / " << character->maxHealth << endl;
	cout << "����ġ: " << character->currExp << " / " << character->maxExp << endl;
	cout << "���: " << character->gold << endl;
	cout << "���: " << character->weapon.name << endl;

}


MONSTER* CreateMonster(int selection)
{
	MONSTER* monster = {};

	switch (selection)
	{
	case 1:
		monster = new MONSTER;
		strcpy_s(monster->name, "������");
		monster->attack = 5;
		monster->maxHealth = 30;
		monster->currHealth = 30;
		monster->exp = 10;
		monster->gold = 10;
		break;
	case 2:
		monster = new MONSTER;
		strcpy_s(monster->name, "�����");
		monster->attack = 15;
		monster->maxHealth = 60;
		monster->currHealth = 60;
		monster->exp = 30;
		monster->gold = 30;
		break;
	case 3:
		monster = new MONSTER;
		strcpy_s(monster->name, "��");
		monster->attack = 30;
		monster->maxHealth = 90;
		monster->currHealth = 90;
		monster->exp = 60;
		monster->gold = 60;
		break;
	default:
		cout << "�߸��� �Է��Դϴ�." << endl;
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
		strcpy_s(character->name, "����");
		character->attack = 10;
		character->maxHealth = 200;
		character->maxExp = 50;
		break;
	case 2:
		character = new CHARACTER;
		strcpy_s(character->name, "������");
		character->attack = 15;
		character->maxHealth = 80;
		character->maxExp = 50;
		break;
	case 3:
		character = new CHARACTER;
		strcpy_s(character->name, "����");
		character->attack = 7;
		character->maxHealth = 150;
		character->maxExp = 50;
		break;
	default:
		cout << "�߸��� �Է��Դϴ�." << endl;
		return nullptr;
	}

	character->currHealth = character->maxHealth;
	character->currExp = 0;
	character->gold = 0;
	character->level = 1;
	character->weapon = {};
	strcpy_s(character->weapon.name, "������");

	return character;
}