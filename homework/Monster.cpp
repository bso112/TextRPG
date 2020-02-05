#include "stdafx.h"
#include "Monster.h"
#include "Parser.h"

void CMonster::PrintMonster() {

	CParser parser;
	if (strcmp(GFX_PATH, "") != 0)
		parser.PrintFile(GFX_PATH);
	cout << '\n';
	cout << "이름: " << name << endl;
	cout << "공격력: " << attack << endl;
	cout << "체력: " << currHealth << " / " << maxHealth << endl;
	char arr[16] = "";
	parser.ElementToString(element, arr);
	cout << "속성: " << arr << endl;


}
