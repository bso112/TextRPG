#include "stdafx.h"
#include "Monster.h"
#include "Parser.h"

void CMonster::PrintMonster() {

	CParser parser;
	if (strcmp(GFX_PATH, "") != 0)
		parser.PrintFile(GFX_PATH);
	cout << '\n';
	cout << "�̸�: " << name << endl;
	cout << "���ݷ�: " << attack << endl;
	cout << "ü��: " << currHealth << " / " << maxHealth << endl;
	char arr[16] = "";
	parser.ElementToString(element, arr);
	cout << "�Ӽ�: " << arr << endl;


}
